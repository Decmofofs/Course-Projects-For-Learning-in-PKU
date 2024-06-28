#include "MidPoint.h"
#include <random>
#include "objwriter.h"
#include "STrandom.h"
#include "setcolor.h"
#include "color.x"
#include <QDebug>
#include "HeightGraphOperator.cpp"
#include <algorithm>
double randomDisplacement(double range, int seed) {
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution(-range, range);
    return distribution(generator);
}


void RecursiveGraphProcess(heightGraph & grid,unsigned x1,unsigned y1,unsigned x2,unsigned y2,double range,unsigned seed,unsigned height_limit){
    int int_seed = (int)(seed);
    unsigned midX = x1+(x2-x1)/2;
    unsigned midY = y1+(y2-y1)/2;
    if((x2-x1)<=1 && (y2-y1)<=1) 
        return;
    //Calculate midpoint values
    grid[midX][midY] = (grid[x1][y1] + grid[x2][y2] + grid[x1][y2] + grid[x2][y1]) / 4.0 + randomDisplacement(range, int_seed);
    grid[x1][midY] = std::max((grid[x1][y1] + grid[x1][y2]) / 2.0 + randomDisplacement(range, int_seed),(double)height_limit);
    grid[x2][midY] = std::max((grid[x2][y1] + grid[x2][y2]) / 2.0 + randomDisplacement(range, int_seed),(double)height_limit);
    grid[midX][y1] = std::max((grid[x1][y1] + grid[x2][y1]) / 2.0 + randomDisplacement(range, int_seed),(double)height_limit);
    grid[midX][y2] = std::max((grid[x1][y2] + grid[x2][y2]) / 2.0 + randomDisplacement(range, int_seed),(double)(height_limit));

    // Recurse on 4 sub-squares
    RecursiveGraphProcess(grid, x1, y1, midX, midY, range / 1.2, int_seed,height_limit);
    RecursiveGraphProcess(grid, midX, y1, x2, midY, range / 1.2, int_seed,height_limit);
    RecursiveGraphProcess(grid, x1, midY, midX, y2, range / 1.2, int_seed,height_limit);
    RecursiveGraphProcess(grid, midX, midY, x2, y2, range / 1.2, int_seed,height_limit);  
}
bool MidPoint2D(unsigned lup,unsigned ldown,unsigned rup,unsigned rdown,unsigned height, unsigned width, unsigned seed,double range,unsigned height_limit){
    int int_seed = (int)(seed);
    STrandom::release();
    STrandom::resetSeed(seed);
    heightGraph grid(Vector2(height+1,width+1));
    grid[0][0]=lup;
    grid[height][0]=ldown;
    grid[0][width]=rup;
    grid[height][width]=rdown;
    RecursiveGraphProcess(grid,0,0,height,width,range,seed,height_limit);
    
    grid.addNoise(seed%(114514191));

    objWriter::CubeMesh(grid,Vector2(0,0),"MidPointMesh");
    bmp_reader::write("./MidPointGraph.bmp",&grid,color_extension::cHypsographicMap(6, SetColor::heights, SetColor::colors));
    
    return true;
}




MidPointCal::MidPointCal(const unsigned & _lup,const unsigned & _ldown,const unsigned & _rup,const unsigned & _rdown,const unsigned & _height, const unsigned & _width, const unsigned & _seed, const double & _range,QObject * parent):
    QObject(parent),
    height(_height),width(_width),seed(_seed),range(_range),lup(_lup),ldown(_ldown),rup(_rup),rdown(_rdown){
    
    QObject::connect(this, &MidPointCal::ToDo, this, &MidPointCal::work);
}

void MidPointCal::work(){
    MidPoint2D(lup,ldown,rup,rdown,width,height,seed,range);
}
