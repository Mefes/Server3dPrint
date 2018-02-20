#ifndef DATA_H
#define DATA_H
#include <QDataStream>
#include <QFile>
class Data
{
    friend QDataStream &operator << (QDataStream &stream,const Data &data);
    friend QDataStream &operator >> (QDataStream &stream, Data &data);

public:
    Data(){}
    virtual ~Data() {}
    QString msg() const {return _msg;}
    void setMsg(const QString &msg) {_msg = msg;}
    QImage gFile() const {return _gFile;}
    void setGFile(const QFile &gFile) {_gFile = gFile;}
private:
    QString _msg;
    QFile _gFile;
};
Q_DECLARE_METATYPE(Data)
#endif // DATA_H
