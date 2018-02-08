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
    in.setVersion(QDataStream::Qt_5_5);
    if (!blockSize)
    {
        // data to read available
        if (tcpSocket->bytesAvailable()<(int)sizeof(quint16))
        {
            return;
        }
        in >> blockSize;
    }
    if (tcpSocket->bytesAvailable() < blockSize)
    {
        return;
    }
    QByteArray data,nextByte;
    // read ...
    in >> nextByte;
    data = nextByte;
    emit read(data);
    data.clear();
    nextByte.clear();
}

bool ThreadClient::write(QByteArray data)
{
    QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_5);
        out << (quint64)0; // Space for size of data
        out << data; // Actual data
        out.device()->seek(0);
        out << (quint64)(data.size() - sizeof(quint64));
    tcpSocket->write(data);
    return tcpSocket->waitForBytesWritten(-1);
}

