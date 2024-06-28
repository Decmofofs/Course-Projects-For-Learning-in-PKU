#ifndef STRANDOM_H
#define STRANDOM_H


namespace STrandom {

void resetSeed(unsigned _seed);
void release();
unsigned getSTrand(int _x, int _y);

}


#endif // STRANDOM_H
