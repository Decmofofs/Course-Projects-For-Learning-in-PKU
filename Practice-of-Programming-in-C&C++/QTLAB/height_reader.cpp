#include "height_reader.h"

height_reader::height_reader(){  }
Vector2 height_reader::open(const char * file){
    fin.open(file, std::ios::in | std::ios::binary);
    if (!fin.is_open()) return Vector2();
    fin.read((char*)&size, sizeof(size));
    return size;
}
void height_reader::close(){
    fin.close();
}
void height_reader::read(char* _Str, std::streamsize _Count) {
    fin.read(_Str, _Count);
}
height_reader& height_reader::operator >> (double& H){
    fin.read((char*)&H, sizeof(H));
    return *this;
}

height_writer::height_writer(const Vector2& v): size(v) {  }
bool height_writer::open(const char * file){
    fout.open(file, std::ios::out | std::ios::binary);
    if (!fout.is_open()) return false;
    if (size.x <= 0 || size.y <= 0) return false;
    fout.write((char*)&size, sizeof(size));
    return true;
}
void height_writer::close(){
    fout.close();
}
void height_writer::resize(Vector2 v) {
    size = v;
}
void height_writer::write(char* _Str, std::streamsize _Count) {
    fout.write(_Str, _Count);
}
height_writer& height_writer::operator << (double& H){
    fout.write((char*)&H, sizeof(H));
    return *this;
}
