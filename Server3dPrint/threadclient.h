#ifndef THREADCLIENT_H
#define THREADCLIENT_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

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
    void write(QByteArray data);
    void disconnected();
signals:
    void error(QTcpSocket::SocketError socketError);
    void read(QByteArray data);

};

#endif // THREADCLIENT_H
