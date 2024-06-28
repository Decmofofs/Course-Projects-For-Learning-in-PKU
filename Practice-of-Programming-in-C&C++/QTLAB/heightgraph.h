#ifndef HEIGHTGRAPH_H
#define HEIGHTGRAPH_H

#include "height_reader.h"

class heightGraph {

public:

    Vector2 size;
    double* pixels;

    heightGraph(const Vector2& size, double** grid = NULL);
    heightGraph(const heightGraph& graph);
    ~heightGraph();

    heightGraph& operator = (const heightGraph& graph);
    double* operator [] (int index);

    // "file" must be a height graph
    bool read(const char* file);
    bool write(const char* file);

    void addNoise(const unsigned seed);

};

#endif // HEIGHTGRAPH_H
