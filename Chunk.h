#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <vector>

#include "Object.h"
#include "Tile.h"
#include "Vector.h"

extern int CHUNK_SIZE;

using namespace std;

class Chunk{
public:
    vector<Object*> Objects;

    Tile* Get_Object(int x, int y);
};

#endif