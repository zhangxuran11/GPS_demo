#include "gpsdevice.h"
#include<QStringList>
#include <QDebug>

#include "qextserialport/src/qextserialport.h"



static void QextSerialPort_init(QextSerialPort *port)
{
    port->setDtr();
    port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_OFF);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    port->setTimeout(300);

}
GPSDevice::GPSDevice(const QString& portName, QObject* parent):
    QObject(parent)
{
    GPS_serial= new QextSerialPort(portName,QextSerialPort::EventDriven);
    QextSerialPort_init(GPS_serial);
    if (GPS_serial->open(QIODevice::ReadWrite) == true) {
        qDebug()<<"listening for data on "<<GPS_serial->portName();
    }
    else {
        qDebug()<<"device failed to open: "<<GPS_serial->errorString();
    }
    GPS_serial->setTimeout(500);
    connect(GPS_serial,SIGNAL(readyRead()),this,SLOT(onReadyRead()),Qt::DirectConnection);
}
void GPSDevice::onReadyRead()
{
    static QString str;
    str.append(GPS_serial->readAll());
//    qDebug()<<"recv "<<str;
    QRegExp rx("[ADEN]\\*[0-9A-F]{1,2}");
    int start = str.indexOf("$GPRMC");
    if(start == -1)
    {
        //qDebug("hasn't head \n");
        return;
    }
    int pos = rx.indexIn(str,start);
    if(pos == -1)
    {
        //qDebug("hasn't tail \n");
        return;
    }
    if(rx.matchedLength() < 4)
        return;
    //qDebug("find head and tail \n");
    int end = pos + rx.matchedLength() - 1;
//    qDebug()<<str;
//    qDebug()<<"start : "<<start<<"  tail : "<<end<<"\n"<<str.mid(start,end - start + 1);
    gprmc.load(str.mid(start,end - start + 1));
    str.remove(0,end+1);
    emit readyRead();


}
const GPRMC& GPSDevice::getOneRPRMC()
{
    return gprmc;
}
GPSDevice::~GPSDevice()
{
    delete GPS_serial;
}
