#ifndef THREADCLIENT_H
#define THREADCLIENT_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDataStream>
#include <QCoreApplication>
#include <QFile>
//#include "data.h"
class ThreadClient : public QThread
{
    Q_OBJECT
public:
    ThreadClient(qintptr socketID, QObject *parent);
    void run() override;
private:
    QTcpSocket *tcpSocket;
    qintptr socketDescriptor;
public slots:
    void readyRead();
    bool write(const QString &msg);
    void write(QFile &file);
signals:
    void error(QTcpSocket::SocketError socketError);
//    void read(Data data,qintptr socketID);

};

#endif // THREADCLIENT_H
