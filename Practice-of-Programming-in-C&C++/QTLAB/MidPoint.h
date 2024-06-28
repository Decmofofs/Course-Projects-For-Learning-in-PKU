#ifndef MIDPOINT_H
#define MIDPOINT_H

#include <QObject>
#include <QThread>

bool MidPoint2D(unsigned lup,unsigned ldown,unsigned rup,unsigned rdown,unsigned height, unsigned width, unsigned seed,double range = 40,unsigned height_limit=255);

class MidPointCal: public QObject {
    Q_OBJECT

public:
    const unsigned & height;
    const unsigned & width;
    const unsigned & seed;
    const double & range;
    const unsigned & lup;
    const unsigned & ldown;
    const unsigned & rup;
    const unsigned & rdown;
    MidPointCal(const unsigned & _lup,const unsigned & _ldown,const unsigned & _rup,const unsigned & _rdown,const unsigned & _height, const unsigned & _width, const unsigned & _seed, const double & _range,QObject * parent = nullptr);

signals:
    void ToDo();

public slots:
    void work();
};

#endif // MIDPOINT_H