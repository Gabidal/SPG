#include "World.h"
#include "Chunk.h"
#include "Object.h"

Chunk* World::Get_Chunk(int x, int y) {
	//Normalize the tile coordinates to fir the chunks top left corner
	x = x - (x % CHUNK_SIZE);
	y = y - (y % CHUNK_SIZE);

	string key = to_string(x) + "," + to_string(y);
	if (Chunks.find(key) != Chunks.end()) {
		return Chunks[key];
	}
	return nullptr;
}

Object* World::Get_Object(int x, int y) {
	//Get the chunk that the tile is in
	Chunk* chunk = Get_Chunk(x, y);

	//If the chunk is not null
	if (chunk != nullptr) {
		//Get the tile from the chunk
		return chunk->Get_Object(x, y);
	}

	return nullptr;
}

void World::Add_Object(Object* object) {
	//Get the chunk that the tile is in
	Chunk* chunk = Get_Chunk(object->Position->X, object->Position->Y);

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

string World::Get_Chunk_Key(int x, int y) {
	//Normalise the tile coordinates to the chunks top left corner
	x = x - (x % CHUNK_SIZE);
	y = y - (y % CHUNK_SIZE);

	return to_string(x) + "," + to_string(y);
}