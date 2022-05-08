#include "TerGen.h"
#include "Vector.h"
#include "Chunk.h"
#include "./TerGen/Include.h"
#include "./Chaos/Include.h"
#include "Render.h"
#include "Tile.h"
#include "Object.h"
#include "World.h"

#include "Functions.h"

#include <map>

using namespace std;

void Generate_Terrain(World* world) {
	//We want the 16x16 chunk size so it is same as our chunk size
	string Arguments = "-res 1 -world_size " + to_string(CHUNK_AMOUNT_SQRT);

	vector<Node*> Nodes = TerGen(Arguments, {
		{Rikka_Generator, 1},
		{Rock_Generator, 1},
		{Tree_Generator, 0.1},
		{River_Generator, 1},
	}, 0.001, 1, 10, 0.3, CHAOS_UTILS::Rand(-100, 100), 4, 0);

	//master zoom, 1, second master zoom, master roughnes, seed, master control amount, little effecter zoom
	//0.001, 1, 10, 0.3, CHAOS_UTILS::Rand(-100, 100), 4, 2 <- good
	//0.01, 1, 1.1, 2, CHAOS_UTILS::Rand(-100, 100), 25, 0 <- buble

	if (Nodes.size() == 0) {
		throw::exception("TerGen returned list size of 0!?");
	}

	world->Raw_Nodes = Nodes;

	UTILS::For_All_Nodes(Nodes, [world](Node* node, double x, double y, double Chunk_X, double Chunk_Y) {
		//The Y in TerGen is same as our Z axis
		//Set the x & y based on the forloop x & y values
		world->Add_Object(Get_Right_BG_Tile(node, Chunk_X + x, Chunk_Y + y));
		world->Add_Object(Get_Right_Object(node, Chunk_X + x, Chunk_Y + y));
	});

	return;
}

Object* Get_Right_BG_Tile(Node* node, int x, int y) {
	BG_TYPES Offset_Y = Normalize_Y(node->Y);

	string Bg_Name = Get_BG_Tile_Name(Offset_Y);

	Tile* Result = new Tile(
		Bg_Name,
		1,
		1,
		x, y,
		node->Y
	);

	return Result;
}

Object* Get_Right_Object(Node* node, int x, int y) {
	Tile* Result = nullptr;

	TILE_TYPES Tile_Type = Get_Tile_Type(node->Color);

	string Tile_Image = Get_Tile_Image(Tile_Type);

	if (Tile_Image == "")
		return nullptr;

	int Size = 1;

	if (Tile_Type == TILE_TYPES::TREE) {
		Size = 2 + rand() % (5 - 2);
	}

	Result = new Tile(
		Tile_Image,
		Size,
		Size,
		x, y,
		(abs(node->Y)) + (int)BG_TYPES::COUNT
	);

	return Result;
}

string Get_BG_Tile_Name(BG_TYPES bg) {
	if (bg == BG_TYPES::GRASS) {
		return TILE_IMAGES::GRASS;
	}
	else if(bg == BG_TYPES::COBBLESTONE) {
		return TILE_IMAGES::COBBLESTONE;
	}
	else if (bg == BG_TYPES::SMOOTH_STONE) {
		return TILE_IMAGES::SMOOTH_STONE;
	}
	else if (bg == BG_TYPES::SWAMP) {
		return TILE_IMAGES::SWAMP;
	}
	else if (bg == BG_TYPES::DARK_GRASS) {
		return TILE_IMAGES::DARK_GRASS;
	}
	else {
		return "";
	}
}

void Generate_Background_Tiles(float Elevation, World* world, vector<Object*> &All_Objects) {
	BG_TYPES BackGround_type = (BG_TYPES)((int)(Elevation) % (int)BG_TYPES::COUNT);
	
	string Bg_Name = Get_BG_Tile_Name(BackGround_type);

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
						Tile* tile = new Tile(Bg_Name,
							1, 1,
							(float)x + X,
							(float)y + Y,
							(float)0
						);

						world->Add_Object(tile);
						All_Objects.push_back(tile);
					}
				}
			}

			//try to find the current chunk again
			chunk = world->Get_Chunk(Chunk_Coordinates({ X, Y }));

			chunk->Has_Background = true;
		}
	);
}