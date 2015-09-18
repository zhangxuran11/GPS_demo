#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"gpsdevice.h"

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
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gpsDevice = new GPSDevice("/dev/ttyUSB1");
    connect(gpsDevice,SIGNAL(readyRead()),this,SLOT(fun()));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete GPS_serial;
}
void MainWindow::fun()
{
    gpsDevice->getOneRPRMC().print();
}


