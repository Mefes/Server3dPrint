#include "threadclient.h"

ThreadClient::ThreadClient(qintptr socketID, QObject *parent):QThread(parent)
{
    socketDescriptor = socketID;
}

void ThreadClient::run()
{
    tcpSocket = new QTcpSocket();
    if(!tcpSocket->setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket->error());
        return;
    }
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    exec();

}


void ThreadClient::readyRead()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    while(tcpSocket->bytesAvailable()) {
        in.startTransaction();
        QByteArray byteData;
        in >> byteData;
        if(in.commitTransaction() == false) return;
        //        QVariant var = uncompressData(byteData);
        //        if(var.isValid() && var.canConvert<Data>()) {
        //            //             Data data = var.value<Data>();
        //            emit read(var.value<Data>(),socketDescriptor);
        //        }
    }
}

bool ThreadClient::write(const QString &msg)
{
    QByteArray byteData;
    short typeData =1;
    QDataStream out(&byteData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << typeData;
    out << msg.toUtf8();
    tcpSocket->write(byteData);
    return tcpSocket->waitForBytesWritten(-1);
}

void ThreadClient::write( QFile &file)
{
//    if (!file.open(QIODevice::ReadOnly))
//    {
//        qDebug() << "Error open file ";
//        return;
//    }
    const qint64 chunkSize = 1024 * 64;
    qDebug() << "Send big file...";
    short typeData =0;
    int pos = 0;
    qint64 fileSize = file.size();
    qDebug() << "Start sending file:" << file.fileName() << "[" << fileSize << "]";
    //    QDataStream out;
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion( QDataStream::Qt_DefaultCompiledVersion );
    out << typeData;
    out << fileSize;
    qDebug() << "Filesize :" << fileSize;
    if( tcpSocket->write( (const char*)&fileSize, sizeof( fileSize ) ) != sizeof( fileSize ) )
    {
        qDebug() << "Error write filesize";
        return;
    }
    while( pos < fileSize )
    {
        int blockSize = qMin( chunkSize, fileSize - pos );
        QByteArray buf= file.read( blockSize );
        if( buf.size() != blockSize )
        {
            qDebug() << "Error read file.";
            return;
        }
        int writed = tcpSocket->write( buf );
        if( writed == -1 )
        {
            qDebug() << "Error write data";
            return;
        }
        qDebug() << "Write size:" << writed;
        pos += blockSize;
        QCoreApplication::processEvents();
    }
}

