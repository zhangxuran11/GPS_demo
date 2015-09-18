#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include"gpsdevice.h"
=======
class QextSerialPort;
>>>>>>> ed961022250e4e04d98f61b50b1f73f8936d3482
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
<<<<<<< HEAD
    GPSDevice* gpsDevice;
=======
    QextSerialPort *GPS_serial;
>>>>>>> ed961022250e4e04d98f61b50b1f73f8936d3482
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
public slots:
<<<<<<< HEAD
    void fun();

=======
    void onReadyRead();
>>>>>>> ed961022250e4e04d98f61b50b1f73f8936d3482
};

#endif // MAINWINDOW_H
