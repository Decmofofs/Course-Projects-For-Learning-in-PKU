#include "PerLinNoise.h"
#include <cmath>
#include "HeightGraphOperator.cpp"
#include "STrandom.h"
#include "setcolor.h"
#include "color_extension.h"
#include "objwriter.h"
#include "picturewidget.h"
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
    heightGraph gridx(Vector2(height * precision + 1, width * precision + 1));
    // Implement PerLin Noise 2D calculation here
    
    for (unsigned i = 0; i <= height; ++i) {
        for (unsigned j = 0; j <= width; ++j) {
            gridx[i * precision][j * precision] = (double)(STrandom::getSTrand(i, j) % height_limit) / height_limit;
        }
    }

    qDebug() << "apply succ";

    // 纵线上的噪声插值
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j <= width; ++j) {
            for (unsigned p = 1; p < precision; ++p) {
                double a = gridx[i * precision][j * precision];
                double b = gridx[(i + 1) * precision][j * precision];
                double x = (double)p / precision;
                gridx[i * precision + p][j * precision] = CosineInterpolate(a, b, x);
            }
        }
    }

    // 横线上的噪声插值
    for (unsigned i = 0; i <= height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            for (unsigned p = 1; p < precision; ++p) {
                double a = gridx[i * precision][j * precision];
                double b = gridx[i * precision][(j + 1) * precision];
                double x = (double)p / precision;
                gridx[i * precision][j * precision + p] = CosineInterpolate(a, b, x);
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
                    double a = gridx[i * precision][j * precision + q];
                    double b = gridx[i * precision + p][j * precision];
                    double x = (double)q / precision;
                    gridx[i * precision + p][j * precision + q] = CosineInterpolate(a, b, x);
                }
            }
        }
    }

    heightGraph gridy(Vector2(height * precision + 1, width * precision + 1));
    // Implement PerLin Noise 2D calculation here

    for (unsigned i = 0; i <= height; ++i) {
        for (unsigned j = 0; j <= width; ++j) {
            gridy[i * precision][j * precision] = (double)(STrandom::getSTrand(i + 199283, j + 173664) % height_limit) / height_limit;
        }
    }

    qDebug() << "apply succ";

    // 纵线上的噪声插值
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j <= width; ++j) {
            for (unsigned p = 1; p < precision; ++p) {
                double a = gridy[i * precision][j * precision];
                double b = gridy[(i + 1) * precision][j * precision];
                double x = (double)p / precision;
                gridy[i * precision + p][j * precision] = CosineInterpolate(a, b, x);
            }
        }
    }

    // 横线上的噪声插值
    for (unsigned i = 0; i <= height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            for (unsigned p = 1; p < precision; ++p) {
                double a = gridy[i * precision][j * precision];
                double b = gridy[i * precision][(j + 1) * precision];
                double x = (double)p / precision;
                gridy[i * precision][j * precision + p] = CosineInterpolate(a, b, x);
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
                    double a = gridy[i * precision][j * precision + q];
                    double b = gridy[i * precision + p][j * precision];
                    double x = (double)q / precision;
                    gridy[i * precision + p][j * precision + q] = CosineInterpolate(a, b, x);
                }
            }
        }
    }

    heightGraph ng(Vector2(height * precision + 1, width * precision + 1));
    ng[0][0] = 127;
    for (unsigned i = 1; i <= height * precision; ++i) {
        for (unsigned j = 0; j <= width * precision; ++j) {
            ng[i][j] = ng[i-1][j] + gridx[i][j] - 0.5;
        }
    }
    for (unsigned j = 1; j <= width * precision; ++j) {
        for ( unsigned i = 0; i <= height * precision; ++i) {
            ng[i][j] = ng[i][j-1] + gridy[i][j] - 0.5;
        }
    }

    /*
    double minNG = 0, maxNG = 0;
    for (unsigned i = 0; i <= height * precision ; ++i) {
        for (unsigned j = 0; j <= height * precision; ++j) {
            if (minNG > ng[i][j]) minNG = ng[i][j];
            if (maxNG < ng[i][j]) maxNG = ng[i][j];
        }
    }
    for (unsigned i = 0; i <= height * precision ; ++i) {
        for (unsigned j = 0; j <= height * precision; ++j) {
            ng[i][j] = int((height_limit + 1) * (ng[i][j] - minNG + 1e-3) / (maxNG - minNG + 1e-3));
            // qDebug() << ng[i][j];
        }
    }*/

    if (PictureWidget::MeshStyle == 0) objWriter::CubeMesh(ng, Vector2(0,0), "perlinnoisemesh");
    else objWriter::SmoothMesh(ng, Vector2(0,0), "perlinnoisemesh");
    if (PictureWidget::PrinterStyle == 0) bmp_reader::write("./PerlinNoiseGraph.bmp", &ng, color_extension::cHypsographicMap(6, SetColor::heights, SetColor::colors));
    else bmp_reader::write("./PerlinNoiseGraph.bmp", &ng, cSimpleCopy());

    // objWriter::CubeMesh(ng,Vector2(0,0),"perlinnoisemesh");
    // bmp_reader::write("./PerlinNoiseGraph.bmp",&ng,color_extension::cHypsographicMap(6, SetColor::heights, SetColor::colors));
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
