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
    connect(threadClient,SIGNAL(read(QByteArray)),this,SLOT(readFromSocket(QByteArray)));
    connect(this,SIGNAL(write(QByteArray)),threadClient,SLOT(write(QByteArray)));
    threadClient->start();
    clientsMachine[socketDescriptor]= threadClient;
    updateCNCList(clientsMachine);
}

bool Server::readFromSocket(QByteArray data)
{
    if (!data.isEmpty())
    {
        return false;
    }
    return true;
}

bool Server::writeToSocket()
{

}
