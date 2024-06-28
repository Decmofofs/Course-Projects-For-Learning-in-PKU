#ifndef OBJWRITER_H
#define OBJWRITER_H


#include "heightgraph.h"
#include <string>


struct vertice {
public:
    double x, y, z;
    vertice() { x = y = z = 0; }
    vertice(double x, double y, double z) :x(x), y(y), z(z) {  }
    vertice(const Vector2& position, double height) :x(position.x), y(height), z(position.y) {  }
    vertice(const vertice& v) :x(v.x), y(v.y), z(v.z) {  }
#ifdef _IOSTREAM_
    friend std::ostream& operator << (std::ostream& os, const vertice& v) {
        os << "v " << v.x << ' ' << v.y << ' ' << v.z;
        return os;
    }
#endif
#ifdef _FSTREAM_
    friend std::ofstream& operator << (std::ofstream& fout, const vertice& v) {
        fout << "v " << v.x << ' ' << v.y << ' ' << v.z;
        return fout;
    }
#endif
};

class objWriter {
private:
    static void getMesh(const std::string& file);

public:
    static unsigned SMOOTH;
    static unsigned CUBE;

    objWriter();
    static void SmoothMesh(heightGraph& graph, const Vector2& start_position = Vector2(0, 0), const std::string& file = "test");
    static void CubeMesh(heightGraph& graph, const Vector2& start_position = Vector2(0, 0), const std::string& file = "test");
    static void Edge(heightGraph& graph, unsigned shape = SMOOTH, const Vector2& start_position = Vector2(0, 0), const std::string& file = "edge");
};


#endif // OBJWRITER_H
