#ifndef COLOR_EXTENSION_H
#define COLOR_EXTENSION_H

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

class color_extension
{
public:

    class cStrictCopy {
    public:
        BGRpixel operator () (double height) const;
    };

    class cToBlue {
    public:
        BGRpixel operator () (double height) const;
    };
    class cToGreen {
    public:
        BGRpixel operator () (double height) const;
    };
    class cToRed {
    public:
        BGRpixel operator () (double height) const;
    };

    class cSimpleRandom {
    private:
        static unsigned seed;
        static void srand(unsigned s = 0);
        static unsigned rand();
        static unsigned getRandom(unsigned n = 256);
    public:
        cSimpleRandom ();
        cSimpleRandom (unsigned s);
        BGRpixel operator () (double height) const;
    };

    static BGRpixel simpleColorInfo[5];
    static double simpleHeightInfo[4];

    class cHypsographicMap {
    private:
        static unsigned diff;
        static double* heightInfo;
        static BGRpixel* colorInfo;
    public:
        cHypsographicMap ();
        cHypsographicMap (unsigned ClrCount, double* CutterHeights, BGRpixel* Colors);
        BGRpixel operator () (double height) const;
    };

    class cLinearBoost {
    private:
        static double _ratio;
        static double _bias;
    public:
        cLinearBoost ();
        cLinearBoost (double ratio, double bias);
        BGRpixel operator () (double height) const;
    };

};

#endif // COLOR_EXTENSION_H
