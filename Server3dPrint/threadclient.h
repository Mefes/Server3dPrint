#ifndef THREADCLIENT_H
#define THREADCLIENT_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDataStream>
#include "data.h"
class ThreadClient : public QThread
{
    Q_OBJECT
public:
    ThreadClient(qintptr socketID, QObject *parent);
    void run() override;
private:
    QTcpSocket *tcpSocket;
    qintptr socketDescriptor;
    int blockSize{0};
    QByteArray compressData(const QVariant &var);
    QVariant uncompressData(const QByteArray &data);
public slots:
    void readyRead();
    bool write(const QVariant &var);
signals:
    void error(QTcpSocket::SocketError socketError);
    void read(QByteArray data,short typeData);

};

#endif // THREADCLIENT_H
