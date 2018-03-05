#ifndef CNCDB_H
#define CNCDB_H

#include <QtSql>
#include <QObject>

class CNCDB : public QObject
{
    Q_OBJECT
public:
    explicit CNCDB(QObject *parent = nullptr);

signals:

public slots:
    QString execQuery(QString str);

};

#endif // CNCDB_H
