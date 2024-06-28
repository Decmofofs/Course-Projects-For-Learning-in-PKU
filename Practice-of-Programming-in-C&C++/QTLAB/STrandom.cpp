#include "STrandom.h"


static unsigned seed = 0;
static bool resetAllowed = true;
static unsigned mover = 0;
static void getrand() {
    unsigned mover2 = mover * mover;
    unsigned mover3 = mover * mover2;
    unsigned movern1 = mover ? 0xffffffff / mover : 1;
    mover = mover3 * 167 + mover2 * 18772553 + mover * 9096384 + movern1 * 17247 + 1;
}

void STrandom::resetSeed(unsigned _seed) {
    if (resetAllowed) {
        seed = _seed;
        resetAllowed = false;
    }
    else {
        throw "Solid Random ERROR : CANNOT reset the seed when having NOT received the liberty of seed.";
    }
}
void STrandom::release() {
    if (!resetAllowed) {
        resetAllowed = true;
    }
    //else { throw "Solid Random ERROR : NOT allowed to release the liberty when HAVING the liberty of seed."; }
}

unsigned STrandom::getSTrand(int _x, int _y) {
    mover = seed;
    unsigned x = _x, y = _y;
    getrand();
    for (int i = 0; i < 32; ++i) {
        //Debug_LOG(mover);
        unsigned j = (1u << i);
        if (j > x && j > y) break;
        bool px = x & j, py = y & j;
        if ((px && !py) || (!px && py)) {
            getrand();
            mover *= (i >> 1) + y + x + 1;
        }
        else if (px && py) {
            getrand();
            mover *= i + x + x + y + 1;
        }
        else {
            mover = mover * (x + y + y + 1) + 328189;
        }
    }
    return mover;
}
