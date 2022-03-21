#include "TerGen.h"
#include "Vector.h"
#include "Chunk.h"
#include "./TerGen/Include.h"
#include "Render.h"
#include "Tile.h"
#include "Object.h"
#include "World.h"

#include <map>

using namespace std;

void Foo(Pattern* p) {
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		int r = rand() % (int)TILE_TYPES::COUNT;

		p->Nodes[i].Color = r;
		p->Nodes[i].Y = -1;
	}
}

void Generate_Terrain(World* world) {
	//We want the 16x16 chunk size so it is same as our chunk size
	string Arguments = "-res 1 -world_size " + to_string(CHUNK_AMOUNT_SQRT);

	vector<Node*> Nodes = TerGen(Arguments, {
		Foo
	});

	if (Nodes.size() == 0) {
		throw::exception("TerGen returned list size of 0!?");
	}

	UTILS::For_All_Nodes(Nodes, [world](Node* node, double x, double y) {
		//The Y in TerGen is same as our Z axis
		//Set the x & y based on the forloop x & y values
		world->Add_Object(Get_Right_Object(node, x, y));
	});

	return;
}

Object* Get_Right_Object(Node* node, int x, int y) {
	Tile* Result = nullptr;

	string Tile_Type = Get_Tile_Image((TILE_TYPES)node->Color);

	Result = new Tile(
		Tile_Type,
		1,
		1,
		x, y,
		node->Y
	);

	return Result;
}

void Seed_Terrain(World* world)
{
	for (int c_x = 0; c_x < CHUNK_AMOUNT_SQRT; c_x++) {
		for (int c_y = 0; c_y < CHUNK_AMOUNT_SQRT; c_y++) {
			int Chunk_Index = (CHUNK_AMOUNT_SQRT * c_x + c_y) * CHUNK_SIZE * CHUNK_SIZE;

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					int Node_index = CHUNK_SIZE * x + y;

					//The Y in TerGen is same as our Z axis
					//Set the x & y based on the forloop x & y values
					Tile* tile = new Tile(TILE_IMAGES::GRASS,
						1, 1,
						(float)x + c_x * CHUNK_SIZE,
						(float)y + c_y * CHUNK_SIZE,
						(float)0
					);

					world->Add_Object(tile);
				}
			}

		}
	}
}

void Generate_Background_Tiles(World* world) {
	RENDER::For_Each_Object_In_View(
		[&](int X, int Y) {

			//This function task is to fill the background tiles for every chunk on X & Y coordinates
			//First try to find if the backgroud tiles are already generated for this chunk. 
			//if so then dont do anything. else generate the background tiles for this chunk
			//and add them to the world.
			Chunk* chunk = world->Get_Chunk(Chunk_Coordinates({ X, Y }));

			if (chunk == nullptr || !chunk->Has_Background){
				//now we need to fill this chunk with background tiles
				for (int x = 0; x < CHUNK_SIZE; x++) {
					for (int y = 0; y < CHUNK_SIZE; y++) {
						Tile* tile = new Tile(TILE_IMAGES::GRASS,
							1, 1,
							(float)x + X,
							(float)y + Y,
							(float)0
						);

						world->Add_Object(tile);
					}
				}
			}

			//try to find the current chunk again
			chunk = world->Get_Chunk(Chunk_Coordinates({ X, Y }));

			chunk->Has_Background = true;
		}
	);
}