#ifndef CNCDB_H
#define CNCDB_H

#include <QObject>

class CNCDB : public QObject
{
    Q_OBJECT
public:
    explicit CNCDB(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CNCDB_H