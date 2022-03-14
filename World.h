#ifndef _WORLD_H_
#define _WORLD_H_

#include <map>
#include <string>

using namespace std;

extern int CHUNK_SIZE;
extern int CHUNK_AMOUNT_SQRT;

class Chunk;
class Object;

class World {
public:
	map<string, Chunk*> Chunks;

	Chunk* Get_Chunk(int x, int y);

	Object* Get_Object(int x, int y);

	void Add_Object(Object* object);

	string Get_Chunk_Key(int x, int y);
};

#endif