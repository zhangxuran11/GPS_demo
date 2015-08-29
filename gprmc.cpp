#include "gprmc.h"
#include<QStringList>
#include <QDebug>

GPRMC::GPRMC(QString bytes)
{
    isValid = false;
    state = ' ';
    latitude = 0;
    longitude = 0;
    QStringList strList = bytes.trimmed().split(QChar(','));
    quint8 refXor = (quint8)strList[12].split(QChar('*'))[1].toUInt(0,16);
    dateTime.setTime(QTime::fromString(strList[1],"hhmmss.sss"));
    dateTime.setDate(QDate::fromString(strList[9],"DDMMYY"));
    if(refXor != checkXor(bytes.toUtf8()))
    {
        qDebug("Xor error \n");

        return;
    }
    qDebug("refXor %x,checkXor %x\n",refXor,checkXor(bytes.toUtf8()));
    isValid = true;

    state = strList[2].toUtf8().data()[0];
    latitude = strList[3].toDouble();    //北正南负
    if(strList[4] == "S")
        latitude *= -1;

    longitude = strList[5].toDouble();   //西正东负
    if(strList[6] == "E")
        longitude *= -1;

}
quint8 GPRMC::checkXor(QByteArray origin)
{
    quint8 xorSum = 0;
    char *off = origin.data();
    while(*(++off)!= '*')
        xorSum ^= *off;
    return xorSum;
}

void  GPRMC::print()
{
    qDebug()<<"isValid  :"<<isValid;
    qDebug()<<"state    :"<<state;
    qDebug("latitude :%.5f longitude :%.5f",latitude,longitude);
}
