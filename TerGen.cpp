#include "TerGen.h"
#include "World.h"
#include "Object.h"
#include "Vector.h"

void Generate_Terrain(World** world) {

	//We want the 16x16 chunk size so it is same as our chunk size
	string Arguments = "-res 1 -world_size " + to_string(CHUNK_AMOUNT_SQRT);

	vector<Node*> Nodes = TerGen(Arguments);

	if (Nodes.size() == 0) {
		throw::exception("TerGen returned list size of 0!?");
	}

	//Now that we have the list of nodes we want to convert them to chunks
	for (int c_x = 0; c_x < CHUNK_AMOUNT_SQRT; c_x++) {
		for (int c_y = 0; c_y < CHUNK_AMOUNT_SQRT; c_y++) {
			int Chunk_Index = CHUNK_AMOUNT_SQRT * c_x + c_y;

			for (int x = 0; x < CHUNK_SIZE; x++) {
				for (int y = 0; y < CHUNK_SIZE; y++) {
					int Node_index = CHUNK_SIZE * x + y;

					//The Y in TerGen is same as our Z axis
					//Set the x & y based on the forloop x & y values
					Object* object = new Object(
						(OBJECT_TYPES)Nodes[Chunk_Index + Node_index]->Color,
						(float)x,
						(float)y,
						(float)Nodes[Chunk_Index + Node_index]->Y
					);

					((World*)world)->Add_Object(object);
				}
			}

		}
	}

	return;
}