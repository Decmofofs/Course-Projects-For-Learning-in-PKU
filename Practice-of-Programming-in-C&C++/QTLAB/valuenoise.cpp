#include "valuenoise.h"
#include "objwriter.h"
#include "HeightGraphOperator.cpp"
#include "STrandom.h"
#include "setcolor.h"
#include "color_extension.h"
#include <QDebug>

/*
static BGRpixel dst_pixel[10] = {
    {12,180,55},{15,255,180},{50,200,200},{100,160,40},{170,175,255},{168,130,152},{255,160,144},{123,90,233},{200,233,40},{234,160,15}
};
static double dst_height[9] = {
    25,50,75,100,125,150,175,200,225
};
*/

double C1Polynomial(double x) {
    double x2 = x * x;
    double x3 = x2 * x;
    return 3 * x2 - 2 * x3;
}
double C2Polynomial(double x) {
    double x2 = x * x;
    double x3 = x2 * x;
    double x4 = x2 * x2;
    double x5 = x2 * x3;
    return 6 * x5 - 15 * x4 + 10 * x3;
}

bool ValueNoise2D(unsigned height, unsigned width, unsigned precision, unsigned seed, unsigned height_limit, smoothFunc useFunction) {
    STrandom::release();
    STrandom::resetSeed(seed);
    heightGraph grid(Vector2(height * precision + 1, width * precision + 1));

    for (unsigned i = 0; i <= height; ++i) {
        for (unsigned j = 0; j <= width; ++j) {
            grid[i * precision][j * precision] = (double)(STrandom::getSTrand(i, j) % height_limit);
        }
    }

    // 先算纵线上的Noise
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j <= width; ++j) {
            for (unsigned x = 1; x < precision; ++x) {
                double lx = useFunction((double)x / (double)precision);
                grid[i * precision + x][j * precision] =
                    grid[i * precision][j * precision] * (1 - lx) + grid[(i + 1) * precision][j * precision] * lx;
            }
        }
    }
    // 再算网格Noise
    for (unsigned i = 0; i <= height * precision; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            for (unsigned y = 1; y < precision; ++y) {
                double ly = useFunction((double)y / (double)precision);
                grid[i][j * precision + y] =
                    grid[i][j * precision] * (1 - ly) + grid[i][(j + 1) * precision] * ly;
            }
        }
    }

    grid.addNoise(2300012991);

    objWriter::CubeMesh(grid, Vector2(0,0), "valuenoisemesh");
    // grid.write("D:/ValueNoise.hgt");
    bmp_reader::write("./ValueNoiseGraph.bmp", &grid, color_extension::cHypsographicMap(6, SetColor::heights, SetColor::colors));
    // bmp_reader::write("./ValueNoiseGraph.bmp", &grid, cSimpleCopy());

    return true;
}

ValueNoiseCal::ValueNoiseCal(const unsigned& _height, const unsigned& _width, const unsigned& _precision, const unsigned& _seed, QObject* parent):
    QObject(parent),
    height(_height), width(_width), precision(_precision), seed(_seed) {

    QObject::connect(this, &ValueNoiseCal::ToDo, this, &ValueNoiseCal::work);
}

void ValueNoiseCal::work(){
    ValueNoise2D(width, height, precision, seed);
}
