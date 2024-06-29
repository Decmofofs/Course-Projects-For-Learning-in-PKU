#ifndef HYDRAULICEROSION_H
#define HYDRAULICEROSION_H

#include <QObject>
#include <QThread>

class posibilities {
public:
    static int front;
    static int side;
    static int decrease;
    static unsigned speedDecrease;
    static unsigned speedSpread;
    static int erodeFront;
    static int erodeSide;
    static int erodeDown;
};

class constvalue{
public:
    static int direction4[9][2];
    static const int height, width;
};

bool HydraulicErosion2D(int seed, int T);

class HydraulicErosionCal: public QObject{
    Q_OBJECT

public:
    const int & seed;
    const int & T;
    HydraulicErosionCal(const int & _seed, const int & _T,QObject * parent = NULL);

signals:
    void ToDo();

public slots:
    void work();
};
#endif // HYDRAULICEROSION_H
