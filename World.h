#ifndef _WORLD_H_
#define _WORLD_H_

#include <map>
#include <string>

using namespace std;

extern int CHUNK_SIZE;

class Chunk;
class Tile;

class World {
public:
	map<string, Chunk*> Chunks;

	Chunk* Get_Chunk(int x, int y);

	Tile* Get_Tile(int x, int y);

	void Add_Tile(Tile* tile);

	string Get_Chunk_Key(int x, int y);
};

#endif