#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QByteArray>
#include "threadclient.h"
class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(int port, QObject *parent);
    ~Server();
private:
    QHash <int,QThreadClient *> clientsMachine;
public slots:
    bool writeToSocket();
signals:
    bool write(QByteArray data);
    void updateCNCList(QHash <int,ThreadClient *> clientsMachine);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    bool readFromSocket(QByteArray data);

};

#endif // SERVER_H
