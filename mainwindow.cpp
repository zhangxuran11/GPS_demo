#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"gpsdevice.h"

#include "qextserialport/src/qextserialport.h"

#include"gprmc.h"

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


