#include "gprmc.h"
#include<QStringList>
#include<cmath>
#include <QDebug>
GPRMC::GPRMC(const QString& bytes)
{
    load(bytes);

}
void GPRMC::clear()
{
    _isValid = false;
    state = ' ';
    speed = 0;
    latitude = 0;
    longitude = 0;
    dateTime.setTime(QTime::fromString("000000.000","hhmmss.sss"));
    dateTime.setDate(QDate::fromString("010101","DDMMYY"));
}
void GPRMC::load(const QString& bytes)
{
    clear();
    QStringList strList = bytes.trimmed().split(QChar(','));
    quint8 refXor = (quint8)strList[12].split(QChar('*'))[1].toUInt(0,16);
    dateTime.setTime(QTime::fromString(strList[1],"hhmmss.sss"));
    dateTime.setDate(QDate::fromString(strList[9],"DDMMYY"));
    if(refXor != checkXor(bytes.toUtf8()))
    {
        qDebug("Xor error \n");

        return;
    }
//    qDebug("refXor %x,checkXor %x\n",refXor,checkXor(bytes.toUtf8()));
    _isValid = true;

    state = strList[2].toUtf8().data()[0];
    latitude = strList[3].toDouble();    //北负南正
    if(strList[4] == "N")
        latitude *= -1;

    longitude = strList[5].toDouble();   //西负东正
    if(strList[6] == "W")
        longitude *= -1;

    latitude = (int)latitude/100 + fmod(latitude,100)/60;
    longitude = (int)longitude/100 + fmod(longitude,100)/60;

//    latitude += 22.5060938;
//    longitude += -15.1757683;
    speed = strList[7].toDouble()*1.852;
}
quint8 GPRMC::checkXor(QByteArray origin)
{
    quint8 xorSum = 0;
    char *off = origin.data();
    while(*(++off)!= '*')
        xorSum ^= *off;
    return xorSum;
}

void  GPRMC::print()const
{
    qDebug()<<"isValid  :"<<isValid();
    qDebug()<<"state    :"<<state;
    qDebug("latitude :%.7f longitude :%.7f",latitude,longitude);
    qDebug("speed :%.7f",speed);
    qDebug()<<"date time : "<<dateTime.toString();
//    qDebug("latitude :%.5f longitude :%.5f",fmod(latitude,100),fmod(longitude,100));
//    qDebug("latitude :%d longitude :%d",abs((int)latitude/100*100),abs((int)longitude/100*100));
//    qDebug("latitude :%.7f longitude :%.7f",(int)latitude/100 + fmod(latitude,100)/60,(int)longitude/100 + fmod(longitude,100)/60);
}
