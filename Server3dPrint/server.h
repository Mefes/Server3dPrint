#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QByteArray>
#include "threadclient.h"
class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(int port, QObject *parent = nullptr);
    ~Server();
private:
    QHash <int,ThreadClient *> clientsMachine;
public slots:
    bool writeToSocket(QByteArray data, short type);
    bool readFromSocket(QByteArray data, short type);
signals:
    bool write(QByteArray data,short type);
    void updateCNCList(QHash <int,ThreadClient *> clientsMachine);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // SERVER_H
