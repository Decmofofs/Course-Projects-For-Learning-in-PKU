#include "color_extension.h"

BGRpixel color_extension::cStrictCopy::operator () (double height) const {
    int _h = (int)height;
    return { BYTE(_h >> 16 & 0xff), BYTE(_h >> 8 & 0xff), BYTE(_h & 0xff) };
}

BGRpixel color_extension::cToBlue::operator () (double height) const {
    return { BYTE(height), BYTE(0), BYTE(0) };
}
BGRpixel color_extension::cToGreen::operator () (double height) const {
    return { BYTE(0), BYTE(height), BYTE(0) };
}
BGRpixel color_extension::cToRed::operator () (double height) const {
    return { BYTE(0), BYTE(0), BYTE(height) };
}

void color_extension::cSimpleRandom::srand(unsigned s) { seed = s; }
unsigned color_extension::cSimpleRandom::rand() {
    seed = seed * 71923 + seed / 652 + 1591;
    return seed;
}
unsigned color_extension::cSimpleRandom::getRandom(unsigned n) {
    if (n == 0) return 0;
    return rand() % n;
}
color_extension::cSimpleRandom::cSimpleRandom () { seed = 0; }
color_extension::cSimpleRandom::cSimpleRandom (unsigned s) { seed = s; }
BGRpixel color_extension::cSimpleRandom::operator () (double height) const {
    return { (BYTE)getRandom(height), (BYTE)getRandom(height), (BYTE)getRandom(height) };
}
unsigned color_extension::cSimpleRandom::seed = 0;

BGRpixel color_extension::simpleColorInfo[5] = {
    {180, 255, 180}, {50, 120, 50}, {40, 120, 120}, {20, 80, 160}, {180, 180, 255}
};
double color_extension::simpleHeightInfo[4] = {
    50, 100, 150, 200
};

color_extension::cHypsographicMap::cHypsographicMap () {  }
color_extension::cHypsographicMap::cHypsographicMap (unsigned ClrCount, double* CutterHeights, BGRpixel* Colors) {
    diff = ClrCount; heightInfo = CutterHeights; colorInfo = Colors;
}
BGRpixel color_extension::cHypsographicMap::operator () (double height) const {
    for (unsigned i = 0; i < diff - 1; ++i)
        if (height < heightInfo[i]) return colorInfo[i];
    return colorInfo[diff - 1];
}

unsigned color_extension::cHypsographicMap::diff = 5;
double* color_extension::cHypsographicMap::heightInfo = simpleHeightInfo;
BGRpixel*color_extension:: cHypsographicMap::colorInfo = simpleColorInfo;

color_extension::cLinearBoost::cLinearBoost () {  }
color_extension::cLinearBoost::cLinearBoost (double ratio, double bias) {
    _ratio = ratio; _bias = bias;
}
BGRpixel color_extension::cLinearBoost::operator () (double height) const {
    return BGRpixel { BYTE(height * _ratio + _bias), BYTE(height * _ratio + _bias), BYTE(height * _ratio + _bias) };
}
double color_extension::cLinearBoost::_ratio = 1;
double color_extension::cLinearBoost::_bias = 0;
