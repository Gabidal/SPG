#include "Functions.h"
#include "TerGen/Include.h"
#include "Chunk.h"

#include "Chaos/Include.h"
#include "Tile.h"

constexpr int AIR_FREQUENCY = 20;
constexpr int INTEGRATION_FREQUENCY = AIR_FREQUENCY / 2;
constexpr int RIVER_WIDTH = 1;

unsigned char Rock_Generator(Pattern* p, Node* Integration_Handle) {
	if (Integration_Handle && rand() % INTEGRATION_FREQUENCY <= 2) {
		BG_TYPES Elevation = Normalize_Y(Integration_Handle->Y);

		if (Elevation == BG_TYPES::COBBLESTONE) {
			return p->Color;
		}
	}

	if (Integration_Handle)
		return 0;
	
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			BG_TYPES Elevation = Normalize_Y(p->Nodes[i].Y);

			if (Elevation == BG_TYPES::COBBLESTONE) {
				p->Nodes[i].Color = p->Color;
			}
		}
	}

	return 0;
}

unsigned char Tree_Generator(Pattern* p, Node* Integration_Handle) {
	if (Integration_Handle && rand() % INTEGRATION_FREQUENCY <= 2) {
		BG_TYPES Elevation = Normalize_Y(Integration_Handle->Y);

		if (Elevation < BG_TYPES::COBBLESTONE) {
			return p->Color;
		}
	}

	if (Integration_Handle)
		return 0;
	
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			BG_TYPES Elevation = Normalize_Y(p->Nodes[i].Y);

			if (Elevation < BG_TYPES::COBBLESTONE) {
				p->Nodes[i].Color = p->Color;
			}
		}
	}

	return 0;
}

unsigned char Rikka_Generator(Pattern* p, Node* Integration_Handle) {
	if (Integration_Handle && rand() % INTEGRATION_FREQUENCY <= 2) {
		BG_TYPES Elevation = Normalize_Y(Integration_Handle->Y);

		if (Elevation == BG_TYPES::SMOOTH_STONE) {
			return p->Color;
		}
	}

	if (Integration_Handle)
		return 0;

	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			BG_TYPES Elevation = Normalize_Y(p->Nodes[i].Y);

			if (Elevation == BG_TYPES::SMOOTH_STONE) {
				p->Nodes[i].Color = p->Color;
			}
		}
	}

	return 0;
}

unsigned char River_Generator(Pattern* p, Node* Integration_Handle) {
	//First calculate the occurance of the river spawnability
	if (/*rand() % AIR_FREQUENCY != 1 ||*/ Integration_Handle)
		return 0;

	//Ok so we have made our mind to make a river then?
	//Start by finding the most a top point in the chunk.
	//Then find the most lowest point.

	//Dont need to worry about interchunkitential river generations.
	//TerGen has a system like the Integrate, that can see occuring patterns especially with the river like straight lines.

	//Two different chunk river start/end points can be made into a single more bigger creation, lake for an example.
	/*pair<IntVector, float> Highest_Point = { {(int)CHAOS_UTILS::Rand(0, CHUNK_SIZE), (int)CHAOS_UTILS::Rand(0, CHUNK_SIZE)}, 10 };
	pair<IntVector, float> Lowest_Point = { {(int)CHAOS_UTILS::Rand(0, CHUNK_SIZE), (int)CHAOS_UTILS::Rand(0, CHUNK_SIZE)}, 0 };*/
	pair<IntVector, float> Highest_Point = { {}, (float)INT32_MIN };
	pair<IntVector, float> Lowest_Point = { {}, (float)INT32_MAX };

	//find the most highest and lowest points
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {

			float Node_Height = At(p->Nodes, x, z)->Y;

			if (Node_Height > Highest_Point.second) {
				Highest_Point = { {x, z}, Node_Height };
			}
			if (Node_Height < Lowest_Point.second) {
				Lowest_Point = { {x, z}, Node_Height };
			}
		}
	}

	vector<Node> Nodes = vector<Node>(&p->Nodes[0], &p->Nodes[CHUNK_SIZE * CHUNK_SIZE]);

	TerGen_Node_Coordinates A = { Highest_Point.first.X, Highest_Point.first.Y };
	TerGen_Node_Coordinates B = { Lowest_Point.first.X, Lowest_Point.first.Y };

	//Now that we have the most highest point and the lowest point awaiable to us, we can start to generate the river.
	vector<pair<TerGen_Node_Coordinates, pair<float, float>>> Result = UTILS::Path_Find(Nodes, A, B, 0);

	//Now that we have all points the path goes through we can start to populate them.
	for (auto Point : Result) {

		int Start_X = max(Point.first.X - RIVER_WIDTH, 0);
		int Start_Z = max(Point.first.Z - RIVER_WIDTH, 0);

		int End_X = min(Point.first.X + RIVER_WIDTH, CHUNK_SIZE);
		int End_Z = min(Point.first.Z + RIVER_WIDTH, CHUNK_SIZE);

		for (int x = Start_X; x < End_X; x++) {
			for (int z = Start_Z; z < End_Z; z++) {

				At(p->Nodes, x, z)->Color = p->Color;

			}
		}
	}
}

inline Node* At(Node* list, int x, int z) {
	return &list[CHUNK_SIZE * x + z];
}