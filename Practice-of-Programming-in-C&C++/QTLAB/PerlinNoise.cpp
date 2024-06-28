#include "PerLinNoise.h"
#include <cmath>
#include "HeightGraphOperator.cpp"
#include "STrandom.h"
#include "setcolor.h"
#include "color_extension.h"
#include "objwriter.h"
#include <QDebug>

// Interpolate Functions
double LinearInterpolate(double a, double b, double x) {
    return a * (1 - x) + b * x;
}

double CosineInterpolate(double a, double b, double x) {
    double ft = x * 3.1415927;
    double f = (1 - cos(ft)) * 0.5;
    return a * (1 - f) + b * f;
}

bool PerLinNoise2D(unsigned height, unsigned width, unsigned precision, unsigned seed, unsigned height_limit, interpolateFunc useFunction) {
    qDebug() << "start succ";
    STrandom::release();
    STrandom::resetSeed(seed);
    heightGraph grid(Vector2(height * precision + 1, width * precision + 1));
    // Implement PerLin Noise 2D calculation here
    
    for (unsigned i = 0; i <= height; ++i) {
        for (unsigned j = 0; j <= width; ++j) {
            grid[i * precision][j * precision] = (double)(STrandom::getSTrand(i, j) % height_limit);
        }
    }

    qDebug() << "apply succ";

    // 纵线上的噪声插值
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j <= width; ++j) {
            for (unsigned p = 1; p < precision; ++p) {
                double a = grid[i * precision][j * precision];
                double b = grid[(i + 1) * precision][j * precision];
                double x = (double)p / precision;
                grid[i * precision + p][j * precision] = CosineInterpolate(a, b, x);
            }
        }
    }

    // 横线上的噪声插值
    for (unsigned i = 0; i <= height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            for (unsigned p = 1; p < precision; ++p) {
                double a = grid[i * precision][j * precision];
                double b = grid[i * precision][(j + 1) * precision];
                double x = (double)p / precision;
                grid[i * precision][j * precision + p] = CosineInterpolate(a, b, x);
            }
        }
    }

    qDebug() << "column succ";

    // 网格内的噪声插值
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            for (unsigned p = 1; p < precision; ++p) {
                for (unsigned q = 1; q < precision; ++q) {
                    // if (i == height || j == width) continue;
                    double a = grid[i * precision][j * precision + q];
                    double b = grid[i * precision + p][j * precision];
                    double x = (double)q / precision;
                    grid[i * precision + p][j * precision + q] = CosineInterpolate(a, b, x);
                }
            }
        }
    }
    
    qDebug() << "cal succ";
    objWriter::CubeMesh(grid,Vector2(0,0),"perlinnoisemesh");
    qDebug() << "mesh succ";
    bmp_reader::write("./PerlinNoiseGraph.bmp",&grid,color_extension::cHypsographicMap(6, SetColor::heights, SetColor::colors));
    qDebug() << "bmp succ";
    return true;
}

PerLinNoiseCal::PerLinNoiseCal(const unsigned& _height, const unsigned& _width, const unsigned& _precision, const unsigned& _seed, QObject* parent)
    : QObject(parent), height(_height), width(_width), precision(_precision), seed(_seed) {
    QObject::connect(this,&PerLinNoiseCal::ToDo,this,&PerLinNoiseCal::work);
}

void PerLinNoiseCal::work() {
    // Implement work function to calculate PerLin Noise
    PerLinNoise2D(width,height,precision,seed);
}
