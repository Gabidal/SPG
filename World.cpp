#include "World.h"
#include "Chunk.h"
#include "Object.h"

Chunk* World::Get_Chunk(Chunk_Coordinates cc)
{
	string key = to_string((int)cc.X) + "," + to_string((int)cc.Y);
	if (Chunks.find(key) != Chunks.end()) {
		return Chunks[key];
	}
	return nullptr;
}

Chunk* World::Get_Chunk(Node_Coordinates nc)
{	
	string key = Get_Chunk_Key(nc.X, nc.Y);
	if (Chunks.find(key) != Chunks.end()) {
		return Chunks[key];
	}
	return nullptr;
}

Object* World::Get_Object(float x, float y) {
	//Get the chunk that the tile is in
	Chunk* chunk = Get_Chunk(Node_Coordinates{x, y});

	//If the chunk is not null
	if (chunk != nullptr) {
		//Get the tile from the chunk
		return chunk->Get_Object(x, y);
	}

	return nullptr;
}

void World::Add_Object(Object* object) {
	//Get the chunk that the tile is in
	Chunk* chunk = Get_Chunk(Node_Coordinates{ object->Position->X, object->Position->Y });

	//If the chunk is not null
	if (chunk != nullptr) {
		//Add the tile to the chunk
		chunk->Objects.push_back(object);
	}
	else {
		//Create a new chunk
		Chunk* new_chunk = new Chunk();

		//Add the tile to the chunk
		new_chunk->Objects.push_back(object);

		//Add the chunk to the world
		Chunks[Get_Chunk_Key(object->Position->X, object->Position->Y)] = new_chunk;
	}
}

string World::Get_Chunk_Key(float x, float y) {
	//Normalise the tile coordinates to the chunks top left corner
	int X = x - ((int)x % CHUNK_SIZE);
	int Y = y - ((int)y % CHUNK_SIZE);

	return to_string(X) + "," + to_string(Y);
}