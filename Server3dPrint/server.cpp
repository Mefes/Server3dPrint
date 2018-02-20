#include "server.h"

Server::Server(int port,QObject *parent):QTcpServer(parent)
{
    if (!listen(QHostAddress::Any,port)) {
        close();
    };
}

Server::~Server()
{
    if (isListening())
    {
        close();
    }
}

Server::incomingConnection(qintptr socketDescriptor)
{
    ThreadClient *threadClient  = new ThreadClient(socketDescriptor,this);
    connect(threadClient,SIGNAL(finished()),threadClient,SLOT(deleteLater()));
    connect(threadClient,SIGNAL(read(QByteArray,short)),this,SLOT(readFromSocket(QByteArray,short)));
    connect(this,SIGNAL(write(QByteArray)),threadClient,SLOT(write(QByteArray)));
    threadClient->start();
    clientsMachine[socketDescriptor]= threadClient;
    updateCNCList(clientsMachine);
}

bool Server::readFromSocket(QByteArray data,short type)
{
    if (!data.isEmpty())
    {
        switch (type) {
        case 0:
            QString msg = QString(data).toUtf8().constData();
            break;
        case 1:

            break;
        default:
            break;
        }
        return false;
    }
    return true;
}

bool Server::writeToSocket(QByteArray data,short type)
{
emit write(data,type);
}
