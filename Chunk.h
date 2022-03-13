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
    vector<Object*> Tiles;
    vector<Object*> Entities;
    vector<Object*> Particles;

    Tile* Get_Tile(int x, int y);
};

#endif