#include "threadclient.h"

ThreadClient::QThreadClient(qintptr socketID, QObject *parent):QThread(parent)
{
socketDescriptor = socketID;
}

void ThreadClient::run()
{

}

void ThreadClient::readyRead()
{

}

void ThreadClient::write(QByteArray data)
{

}

void ThreadClient::disconnected()
{

}
