#ifndef VALUENOISE_H
#define VALUENOISE_H

#include <QObject>
#include <QThread>

typedef double(*smoothFunc)(double);

// Smooth Function （提供2个）
double C1Polynomial(double x);
double C2Polynomial(double x);

bool ValueNoise2D(unsigned height, unsigned width, unsigned precision, unsigned seed, unsigned height_limit = 255, smoothFunc useFunction = C2Polynomial);

class ValueNoiseCal : public QObject {
    Q_OBJECT

public:
    const unsigned& height;
    const unsigned& width;
    const unsigned& precision;
    const unsigned& seed;
    ValueNoiseCal(const unsigned& _height, const unsigned& _width, const unsigned& _precision, const unsigned& seed, QObject* parent = nullptr);

signals:
    void ToDo();

public slots:
    void work();
};


#endif // VALUENOISE_H
