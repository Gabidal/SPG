#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>

#include "Object.h"

using namespace std;

class World {
public:
	vector<Object*> Tile_Buffer;
	vector<Object*> Entity_Buffer;
	vector<Object*> Particle_Buffer;

};

#endif