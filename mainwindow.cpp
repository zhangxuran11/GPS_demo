#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"


#include"gpsdevice.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    gpsDevice = new GPSDevice("/dev/ttyUSB0");
    connect(gpsDevice,SIGNAL(readyRead()),this,SLOT(fun()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::fun()
{
    gpsDevice->getOneRPRMC().print();
}

