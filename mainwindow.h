#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QextSerialPort;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QextSerialPort *GPS_serial;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
public slots:
    void onReadyRead();
};

#endif // MAINWINDOW_H
