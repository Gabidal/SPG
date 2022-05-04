#include "Functions.h"
#include "TerGen/Include.h"
#include "Chunk.h"

#include "Chaos/Include.h"
#include "Tile.h"

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
	if (rand() % AIR_FREQUENCY == 1 || Integration_Handle)
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

	vector<TerGen_Node_Coordinates> Points;
	Points.push_back({ Highest_Point.first.X, Highest_Point.first.Y });

	int Point_Count = CHAOS_UTILS::Rand(1, MAX_RIVER_MID_POINTS);

	for (int Point = 0; Point < Point_Count; Point++) {
		float Min_X = max(Points.back().X - RIVER_SWIGLINES, 0);
		float Min_Z = max(Points.back().Z - RIVER_SWIGLINES, 0);

		float Max_X = min(Points.back().X + RIVER_SWIGLINES, CHUNK_SIZE);
		float Max_Z = min(Points.back().Z + RIVER_SWIGLINES, CHUNK_SIZE);

		//the more the index is the more closer it should be to the last point.
		int X = (int)CHAOS_UTILS::Rand(Min_X, Max_X);
		int Z = (int)CHAOS_UTILS::Rand(Min_Z, Max_Z);

		float Distance_X = Lowest_Point.first.X - X;
		float Distance_Z = Lowest_Point.first.Y - Z;

		float Normalized_Distance_X = Distance_X / Point_Count;
		float Normalized_Distance_Z = Distance_Z / Point_Count;

		X += Normalized_Distance_X;
		Z += Normalized_Distance_Z;

		TerGen_Node_Coordinates Next_Point = { X, Z };

		Points.push_back(Next_Point);
	}

	vector<pair<TerGen_Node_Coordinates, pair<float, float>>> Paths;

	for (int Point = 1; Point < Points.size(); Point++) {
		Append(Paths, UTILS::Path_Find(Nodes, Points[(size_t)Point - 1], Points[Point], 1));
	}

	//Now that we have all points the path goes through we can start to populate them.
	for (auto& Point : Paths) {

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
//
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

template<typename T>
void Append(vector<T>& a, vector<T> b) {
	for (auto i : b) {
		a.push_back(i);
	}
}

inline Node* At(Node* list, int x, int z) {
	return &list[CHUNK_SIZE * x + z];
}