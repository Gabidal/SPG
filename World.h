#ifndef _WORLD_H_
#define _WORLD_H_

#include <map>
#include <string>

using namespace std;

extern int CHUNK_AMOUNT_SQRT;

class Chunk;
class Object;
class Chunk_Coordinates {
public:
	int X;
	int Y;

	Chunk_Coordinates(int x, int y) {
		X = x;
		Y = y;
	}
};

class Node_Coordinates {
public:
	double X;
	double Y;

	Node_Coordinates(double x, double y) {
		X = x;
		Y = y;
	}
};

class World {
public:
	map<string, Chunk*> Chunks;

	Chunk* Get_Chunk(Chunk_Coordinates cc);

	Chunk* Get_Chunk(Node_Coordinates cc);

	Object* Get_Object(float x, float y);

	void Add_Object(Object* object);

	string Get_Chunk_Key(float x, float y);
};

#endif