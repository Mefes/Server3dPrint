#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QByteArray>
#include <QFile>
#include "threadclient.h"
//#include "data.h"
class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(int port, QObject *parent = 0);
    ~Server();
private:
    QHash <int,ThreadClient *> clientsMachine;
public slots:
    bool writeToSocket(QFile &file, qintptr socketDescriptor);
    bool writeToSocket(QString msg,qintptr socketDescriptor);
    bool readFromSocket(QVariant data, qintptr socketDescriptor);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    void updateCNCList(QHash <int,ThreadClient *> clientsMachine);
    void msgFromSocket(QString msg,qintptr socketDescriptor);
//    void fileFromSocket(QFile file,qintptr socketDescriptor);
};

#endif // SERVER_H
