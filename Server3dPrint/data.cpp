#include "data.h"
qRegisterMetaType<Data>("Data");
qRegisterMetaTypeStreamOperators<Data>("Data");

QDataStream &Data::operator <<(QDataStream &stream, const Data &data)
{
    return stream << data._msg << data._gFile;

}

QDataStream &Data::operator >>(QDataStream &stream, Data &data)
{
    stream >> data._msg >> data._gFile;
      return stream;
}
