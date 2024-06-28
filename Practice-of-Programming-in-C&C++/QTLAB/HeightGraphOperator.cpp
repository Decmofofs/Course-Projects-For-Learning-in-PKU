#ifndef HEIGHT_GRAPH_OPERATOR
#define HEIGHT_GRAPH_OPERATOR

#include "heightgraph.h"
#pragma pack(1)

#ifndef BGR_PIXEL
#define BGR_PIXEL
typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef long                LONG;
typedef struct tagIMAGEINFO {
    BYTE BLUE;
    BYTE GREEN;
    BYTE RED;
} BGRpixel;
#endif

typedef struct tagBITMAPFILEHEADER
{
    WORD bfType; // 位图文件的类型，必须为“BM”
    DWORD bfSize; // 位图文件的大小，以字节为单位
    WORD bfReserved1; // 位图文件保留字，必须为 0
    WORD bfReserved2; // 位图文件保留字，必须为 0
    DWORD bfOffBits; // 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
} BITMAPFILEHEADER; // 该结构占据 14 个字节。

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize; // 本结构所占用字节数
    LONG biWidth; // 位图的宽度，以像素为单位
    LONG biHeight; // 位图的高度，以像素为单位
    WORD biPlanes; // 目标设备的平面数不清，必须为 1
    WORD biBitCount; // 每个像素所需的位数，必须是 1(双色), 4(16 色)，8(256 色)或 24(真彩色)之一
    DWORD biCompression; // 位图压缩类型，必须是 0(不压缩),1(BI_RLE8 压缩类型)或 2(BI_RLE4压缩类型)之一
    DWORD biSizeImage; // 位图的大小，以字节为单位
    LONG biXPelsPerMeter; // 位图水平分辨率，每米像素数
    LONG biYPelsPerMeter; // 位图垂直分辨率，每米像素数
    DWORD biClrUsed;// 位图实际使用的颜色表中的颜色数
    DWORD biClrImportant;// 位图显示过程中重要的颜色数
} BITMAPINFOHEADER; // 该结构占据 40 个字节。


class cSimpleCopy {
public:
    BGRpixel operator () (double height) const {
        return { BYTE(height), BYTE(height), BYTE(height) };
    }
};

class cSimpleMean {
public:
    BGRpixel operator () (double height) const {
        return { BYTE(height / 3), BYTE(height / 3), BYTE(height / 3) };
    }
};
class hSimpleMean {
public:
    double operator () (BGRpixel pixel) const {
        return (double)(pixel.BLUE + pixel.GREEN + pixel.RED) / 3;
    }
};

namespace bmp_reader {

    template <class HeightFunc = hSimpleMean>
    void read(const char* file, heightGraph* _graph_ptr, const HeightFunc& func = HeightFunc()) {
        BITMAPFILEHEADER fileHeader;
        BITMAPINFOHEADER infoHeader;
        std::ifstream fin(file, std::ios::in | std::ios::binary);
        fin.read((char*)&fileHeader, sizeof(fileHeader));
        fin.read((char*)&infoHeader, sizeof(infoHeader));
        LONG height = infoHeader.biHeight;
        LONG width = infoHeader.biWidth;
        BGRpixel bmpImage;
        BYTE EMPTY;
        LONG widthTail = width * 3 % 4;
        if (widthTail) widthTail = 4 - widthTail;

        _graph_ptr->size = Vector2(width, height);
        _graph_ptr->pixels = new double[width * height];

        for (LONG i = 0; i < height; i++) {
            for (LONG j = 0; j < width; j++) {
                fin.read((char*)&bmpImage, sizeof(bmpImage));
                _graph_ptr->pixels[i + j * height] = func(bmpImage);
            }
            for (int k = 0; k < widthTail; k++) {
                fin.read((char*)&EMPTY, sizeof(BYTE));
            }
        }

        fin.close();
        return;
    }

    template <class ColorFunc = cSimpleMean>
    void write(const char* file, heightGraph* _graph_ptr, const ColorFunc& func = ColorFunc()) {

        int height = (int)_graph_ptr->size.y;
        int width = (int)_graph_ptr->size.x;

        LONG widthTail = width * 3 % 4;
        if (widthTail) widthTail = 4 - widthTail;
        LONG bmpSize = (LONG)width * (LONG)height * 3 + widthTail * (LONG)height;
        BITMAPFILEHEADER fileHeader;
        BITMAPINFOHEADER infoHeader;
        std::ofstream fout(file, std::ios::out | std::ios::binary);
        fout.seekp(0, std::ios::beg);

        fileHeader.bfType = (WORD)19778;
        fileHeader.bfSize = (DWORD)bmpSize + 54;
        fileHeader.bfReserved1 = (WORD)0;
        fileHeader.bfReserved2 = (WORD)0;
        fileHeader.bfOffBits = (DWORD)54;

        infoHeader.biSize = (DWORD)40;
        infoHeader.biWidth = (LONG)_graph_ptr->size.x;
        infoHeader.biHeight = (LONG)_graph_ptr->size.y;
        infoHeader.biPlanes = (WORD)1;
        infoHeader.biBitCount = (WORD)24;
        infoHeader.biCompression = (DWORD)0;
        infoHeader.biSizeImage = (DWORD)bmpSize;
        infoHeader.biXPelsPerMeter = (LONG)0;
        infoHeader.biYPelsPerMeter = (LONG)0;
        infoHeader.biClrUsed = (DWORD)0;
        infoHeader.biClrImportant = (DWORD)0;

        fout.write((char*)&fileHeader, sizeof(fileHeader));
        fout.write((char*)&infoHeader, sizeof(infoHeader));

        const BYTE ZERO = 0x00;
        for (LONG i = 0; i < height; i++) {
            for (LONG j = 0; j < width; j++) {
                BGRpixel bmpImage = func(_graph_ptr->pixels[i + j * height]);
                fout.write((char*)&bmpImage, sizeof(bmpImage));
            }
            for (int k = 0; k < widthTail; k++) {
                fout.write((char*)&ZERO, sizeof(BYTE));
            }
        }

        fout.close();
        return;
    }

}

#pragma pack()

#endif // HEIGHT_GRAPH_OPERATOR
