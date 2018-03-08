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

void Server::incomingConnection(qintptr socketDescriptor)
{
    ThreadClient *threadClient  = new ThreadClient(socketDescriptor,this);
    connect(threadClient,SIGNAL(finished()),threadClient,SLOT(deleteLater()));
    connect(threadClient,SIGNAL(read(QVariant,qintptr)),this,SLOT(readFromSocket(QVariant,qintptr)));
    threadClient->start();
    clientsMachine[socketDescriptor]= threadClient;
    updateCNCList(clientsMachine);
}

bool Server::readFromSocket(QVariant data, qintptr socketDescriptor)
{

}

bool Server::writeToSocket(QFile &file, qintptr socketDescriptor)
{
clientsMachine[socketDescriptor]->write(file);
}

bool Server::writeToSocket(QString msg, qintptr socketDescriptor)
{
//    clientsMachine[socketDescriptor]->write(QVariant::fromValue<QString>(msg));
}
