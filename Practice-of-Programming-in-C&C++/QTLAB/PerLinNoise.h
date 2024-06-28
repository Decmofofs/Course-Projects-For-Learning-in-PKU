#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <QObject>
#include <QThread>

typedef double(*interpolateFunc)(double, double, double);

// Interpolate Function
double LinearInterpolate(double a, double b, double x);
double CosineInterpolate(double a, double b, double x);

bool PerLinNoise2D(unsigned height, unsigned width, unsigned precision, unsigned seed, unsigned height_limit = 255, interpolateFunc useFunction = CosineInterpolate);

class PerLinNoiseCal : public QObject {
    Q_OBJECT

public:
    const unsigned& height;
    const unsigned& width;
    const unsigned& precision;
    const unsigned& seed;
    PerLinNoiseCal(const unsigned& _height, const unsigned& _width, const unsigned& _precision, const unsigned& _seed, QObject* parent = nullptr);

signals:
    void ToDo();

public slots:
    void work();
};
#endif 