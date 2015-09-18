#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"gpsdevice.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    GPSDevice* gpsDevice;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
public slots:
    void fun();

};

#endif // MAINWINDOW_H
