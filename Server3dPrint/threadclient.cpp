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

QByteArray ThreadClient::compressData(const QVariant &var)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    stream << var;
    return qCompress(data, 9);
}

QVariant ThreadClient::uncompressData(const QByteArray &data)
{
    QByteArray raw_data = qUncompress(data);
    if(raw_data.isEmpty()) return QVariant();
    QDataStream stream(raw_data);
    stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    QVariant var;
    stream >> var;
    return var;
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

         QVariant var = uncompressData(byteData);

         if(var.isValid() && var.canConvert<Data>()) {
             Data data = var.value<Data>();
         }
     }

//    emit read(data,typeData);

}

bool ThreadClient::write(const QVariant &var)
{
    QByteArray byteData;
    QDataStream out(&byteData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << compressData(var);
    tcpSocket->write(byteData);
    return tcpSocket->waitForBytesWritten(-1);
}

