#ifndef HEIGHT_READER_H
#define HEIGHT_READER_H

#include <fstream>
#include "math_expand.h"


class height_reader {

private:

    Vector2 size;
    std::ifstream fin;

public:
    height_reader();

    // "file" must be a height graph
    Vector2 open(const char * file);
    void close();
    void read(char* _Str, std::streamsize _Count);

    height_reader& operator >> (double& H);


};

class height_writer {

    Vector2 size;
    std::ofstream fout;

public:
    height_writer(const Vector2& v);

    bool open(const char * file);
    void close();
    void resize(Vector2 v = Vector2(0, 0));
    void write(char* _Str, std::streamsize _Count);

    height_writer& operator << (double& H);

};

#endif // HEIGHT_READER_H
