#ifndef GPRMC_H
#define GPRMC_H
#include<QDateTime>
#include<QString>
class GPRMC
{
    bool _isValid;
    quint8 checkXor(QByteArray origin);
public:
    bool isValid()const{return _isValid;}
    QDateTime dateTime;
    char state;
    qreal latitude;
    qreal longitude;


    GPRMC(){}
    GPRMC(const QString& bytes);
    void clear();
    void load(const QString& bytes);
    void print()const;
};

#endif // GPRMC_H
