#include "Functions.h"
#include "TerGen/Include.h"
#include "Chunk.h"

#include "Chaos/Include.h"
#include "Tile.h"

#include <iostream>
using namespace std;

constexpr int AIR_FREQUENCY = 20;
constexpr int INTEGRATION_FREQUENCY = AIR_FREQUENCY / 2;
constexpr int RIVER_WIDTH = 1;
constexpr int RIVER_SWIGLINES = 1;
constexpr int MAX_RIVER_MID_POINTS = 1;

unsigned char Rock_Generator(Pattern* p, Node* Integration_Handle) {
	if (Integration_Handle && rand() % INTEGRATION_FREQUENCY <= 2) {
		BG_TYPES Elevation = Normalize_Y(Integration_Handle->Y);

		if (Elevation == BG_TYPES::COBBLESTONE) {
			return p->Color;
		}
	}
	if (Integration_Handle)
		return 0;
	
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			if (rand() % AIR_FREQUENCY == 1) {
				BG_TYPES Elevation = Normalize_Y(p->Nodes[CHUNK_SIZE * x + z].Y);

				if (Elevation == BG_TYPES::COBBLESTONE) {
					p->Nodes[CHUNK_SIZE * x + z].Color = p->Color;
				}
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

			if (Elevation >= BG_TYPES::SWAMP && Elevation <= BG_TYPES::TUNDRA) {
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
	if (Integration_Handle)	//This function will not answer to integration.
		return 0;

	return 0;
	
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
		
			float Real_X = x + p->X * CHUNK_SIZE;
			float Real_Z = z + p->Z * CHUNK_SIZE;

			float Heigth = UTILS::Warp_Noise({ Real_X, Real_Z });

			if (Heigth < -0.3) {
				int index = CHUNK_SIZE * x + z;

				Node* n = &p->Nodes[index];
				
				n->Color = p->Color;

			}
		
		}
	}
}

unsigned char Cactus_Generator(Pattern* p, Node* Integration_Handle) {
	if (Integration_Handle && rand() % INTEGRATION_FREQUENCY <= 2) {
		BG_TYPES Elevation = Normalize_Y(Integration_Handle->Y);

		if (Elevation == BG_TYPES::SAND2) {
			return p->Color;
		}
	}
	if (Integration_Handle)
		return 0;

	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			BG_TYPES Elevation = Normalize_Y(p->Nodes[i].Y);

			if (Elevation == BG_TYPES::SAND2) {
				p->Nodes[i].Color = p->Color;
			}
		}
	}

	return 0;
}

unsigned char Water_Rock_Generator(Pattern* p, Node* Integration_Handle) {
	if (Integration_Handle)
		return 0;

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			if (rand() % AIR_FREQUENCY == 1) {
				BG_TYPES Elevation = Normalize_Y(p->Nodes[CHUNK_SIZE * x + z].Y);

				vector<TerGen_Node_Coordinates> Surrounding_Nodes = UTILS::Get_Surrounding_Coordinates({ x, z }, 1, { 0, CHUNK_SIZE });

				int Water_Surrounds = 0;
				int Sand_Surrounds = 0;

				for (TerGen_Node_Coordinates Coordinate : Surrounding_Nodes) {

					BG_TYPES Normalized_Elevation = Normalize_Y(p->Nodes[CHUNK_SIZE * Coordinate.X + Coordinate.Z].Y);

					if (Normalized_Elevation == BG_TYPES::WATER) {
						Water_Surrounds++;
					}
					else if (Normalized_Elevation == BG_TYPES::SAND) {
						Sand_Surrounds++;
					}

				}

				if (Sand_Surrounds == 5 && Water_Surrounds == 3) {
					p->Nodes[CHUNK_SIZE * x + z].Color = p->Color;
				}
			}
		}
	}

	return 0;
}

//void Water_Flow(Pattern* p, int X, int Z) {
//	if (X < 0 || Z < 0 || X > CHUNK_SIZE || Z > CHUNK_SIZE)
//		return;
//
//	bool Found_Lower_Ground = false;
//
//	float Min_X = max(X - 1, 0);
//	float Min_Z = max(Z - 1, 0);
//
//	float Max_X = min(X + 1, CHUNK_SIZE);
//	float Max_Z = min(Z + 1, CHUNK_SIZE);
//
//	Node* Current_Node = At(p->Nodes, X, Z);
//
//	for (int x = Min_X; x < Max_X; x++) {
//		for (int z = Min_Z; z < Max_Z; z++) {
//
//			if (x == X && z == Z)
//				continue;
//
//			Node* n = At(p->Nodes, x, z);
//
//			if (n->Y <= Current_Node->Y) {
//				if (n->Y < Current_Node->Y)
//					Found_Lower_Ground = true;
//
//				Water_Flow(p, x, z);
//			}
//		}
//	}
//
//	if (!Found_Lower_Ground) {
//		Current_Node->Color = p->Color;
//	}
//}
//
//unsigned char River_Generator(Pattern* p, Node* Integration_Handle) {
//	//First calculate the occurance of the river spawnability
//	if (Integration_Handle)
//		return 0;
//
//	for (int x = 0; x < CHUNK_SIZE; x += 2) {
//		for (int z = 0; z < CHUNK_SIZE; z += 2) {
//			Water_Flow(p, x, z);
//		}
//	}
//}


template<typename T>
void Append(vector<T>& a, vector<T> b) {
	for (auto i : b) {
		a.push_back(i);
	}
}

inline Node* At(Node* list, int x, int z) {
	return &list[CHUNK_SIZE * x + z];
}