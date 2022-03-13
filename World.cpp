#include "World.h"
#include "Chunk.h"

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

Tile* World::Get_Tile(int x, int y) {
	//Get the chunk that the tile is in
	Chunk* chunk = Get_Chunk(x, y);

	//If the chunk is not null
	if (chunk != nullptr) {
		//Get the tile from the chunk
		return chunk->Get_Tile(x, y);
	}

	return nullptr;
}

void World::Add_Tile(Tile* tile) {
	//Get the chunk that the tile is in
	Chunk* chunk = Get_Chunk(tile->Position->X, tile->Position->Y);

	//If the chunk is not null
	if (chunk != nullptr) {
		//Add the tile to the chunk
		chunk->Tiles.push_back(tile);
	}
	else {
		//Create a new chunk
		Chunk* new_chunk = new Chunk();

		//Add the tile to the chunk
		new_chunk->Tiles.push_back(tile);

		//Add the chunk to the world
		Chunks[Get_Chunk_Key(tile->Position->X, tile->Position->Y)] = new_chunk;
	}
}

string World::Get_Chunk_Key(int x, int y) {
	//Normalise the tile coordinates to the chunks top left corner
	x = x - (x % CHUNK_SIZE);
	y = y - (y % CHUNK_SIZE);

	return to_string(x) + "," + to_string(y);
}