#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD


#include"gpsdevice.h"

=======
#include "qextserialport/src/qextserialport.h"

#include"gprmc.h"
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
>>>>>>> ed961022250e4e04d98f61b50b1f73f8936d3482
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
<<<<<<< HEAD

    ui->setupUi(this);
    gpsDevice = new GPSDevice("/dev/ttyUSB0");
    connect(gpsDevice,SIGNAL(readyRead()),this,SLOT(fun()));
=======
    ui->setupUi(this);
    GPS_serial= new QextSerialPort("/dev/ttyUSB1",QextSerialPort::EventDriven);
    QextSerialPort_init(GPS_serial);
    if (GPS_serial->open(QIODevice::ReadWrite) == true) {
        qDebug()<<"listening for data on "<<GPS_serial->portName();
    }
    else {
        qDebug()<<"device failed to open: "<<GPS_serial->errorString();
    }
    GPS_serial->setTimeout(500);
    connect(GPS_serial,SIGNAL(readyRead()),this,SLOT(onReadyRead()),Qt::DirectConnection);
>>>>>>> ed961022250e4e04d98f61b50b1f73f8936d3482
}

MainWindow::~MainWindow()
{
    delete ui;
<<<<<<< HEAD
}
void MainWindow::fun()
{
    gpsDevice->getOneRPRMC().print();
}

=======
    delete GPS_serial;
}

void MainWindow::onReadyRead()
{
    static QString str;
    str.append(GPS_serial->readAll());
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
    qDebug()<<str;
    qDebug()<<"start : "<<start<<"  tail : "<<end<<"\n"<<str.mid(start,end - start + 1);
    GPRMC gprm(str.mid(start,end - start + 1));
    str.remove(0,end+1);
    gprm.print();


}
>>>>>>> ed961022250e4e04d98f61b50b1f73f8936d3482
