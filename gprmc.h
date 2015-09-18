#ifndef GPRMC_H
#define GPRMC_H
#include<QString>
#include<QDateTime>
class GPRMC
{
    quint8 checkXor(QByteArray origin);
public:
    bool isValid;
    QDateTime dateTime;
    char state;
    qreal latitude;
    qreal longitude;
    GPRMC(QString bytes);
    void print();
};

#endif // GPRMC_H
