#include "heightgraph.h"
#include "STrandom.h"

heightGraph::heightGraph(const Vector2& size, double** grid) :size(size) {
    if (grid && bool(size)) {
        int length = (int)size.x * (int)size.y;
        pixels = new double[length];
        for(int index = 0; index < length; ++index) {
            pixels[index] = grid[index / (int)size.x][index % (int)size.x];
        }
    }
    else if(bool(size)) {
        int length = (int)size.x * (int)size.y;
        pixels = new double[length];
    }
    else {
        pixels = NULL;
    }
}
heightGraph::heightGraph(const heightGraph& graph) {
    size = graph.size;
    int length = (int)size.x * (int)size.y;
    pixels = new double[length];
    for (int index = 0; index < length; ++index) {
        pixels[index] = graph.pixels[index];
    }
}
heightGraph::~heightGraph() { if (pixels) delete[] pixels; }

heightGraph& heightGraph::operator = (const heightGraph& graph) {
    if (this == &graph) return *this;
    size = graph.size;
    if (pixels) delete[] pixels;
    int length = (int)size.x * (int)size.y;
    pixels = new double[length];
    for (int i = 0; i < length; ++i) {
        pixels[i] = graph.pixels[i];
    }
    return *this;
}
double* heightGraph::operator [] (int index) {
    return &(pixels[index * (int)size.y]);
}

bool heightGraph::read(const char* file) {
    height_reader HR;
    size = HR.open(file);
    if (!size) {
        HR.close();
        return false;
    }
    if (pixels) delete[] pixels;
    int length = (int)size.x * (int)size.y;
    pixels = new double[length];
    HR.read((char*)pixels, sizeof(double) * length);
    HR.close();
    return true;
}
bool heightGraph::write(const char* file) {
    if (!pixels) return false;
    height_writer HW(size);
    if (!HW.open(file)) {
        HW.close();
        return false;
    }
    int length = (int)size.x * (int)size.y;
    HW.write((char*)pixels, sizeof(double) * length);
    HW.close();
    return true;
}

void heightGraph::addNoise(const unsigned seed) {
    STrandom::release();
    STrandom::resetSeed(seed);
    int x = (int)size.x;
    int y = (int)size.y;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            (*this)[i][j] += (STrandom::getSTrand(i,j) & 1) / 3.0;
        }
    }
}
