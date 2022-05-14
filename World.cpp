#include "World.h"
#include "Chunk.h"
#include "Object.h"

#include "TerGen/Include.h"
#include "Render.h"

#include <iostream>

using namespace std;

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
	if (object == nullptr)
		return;
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
	int X = x - ((int)(x + CHUNK_SIZE) % CHUNK_SIZE);
	int Y = y - ((int)(y + CHUNK_SIZE) % CHUNK_SIZE);

	/*int X = x / CHUNK_SIZE;
	int Y = y / CHUNK_SIZE;*/

	return to_string(X) + "," + to_string(Y);
}

void World::Apply_Velocity(Object* object, unsigned long long delta_time, float Transfer_Speed) {
	//The velocity formula: made by u/refD
	//New Velocity = old_velocity * (1 - delta_time * transition_speed) + desired_velocity * (delta_time * transition_speed)

	//We can get the transition_speed by calculating the height of each tiles around the entity.
	float Goal_Tile = 0;

	Object* obj = this->Get_Object((int)(object->Velocity->X + object->Position->X), (int)(object->Velocity->Y + object->Position->Y));

	if (obj == nullptr)
		return;

	//SPG moves at (X, Y) and height Z
	//Average_Height += obj->Position->Z * object->Stength;
	Goal_Tile = obj->Position->Z;
	//cout << Goal_Tile;

	//Calculate the difference between the entity and the average height
	float Height_Difference = Goal_Tile - ((object->Position->Z) - RENDER::Entity_Draw_Priority);
	//Apply gravity to the position of the entity
	//make sure the entity always stays at the right render order.
	if (delta_time % 1000 == 0)
		object->Position->Z += Height_Difference;

	//normalize the height difference to the range of 0 to 2;
	//first create a normal verctor perpectural tot he height difference
	FloatVector Normal_Vector = { 1, -1/abs(Height_Difference * object->Strength) };	//we insert the 1, because the velocity is a normalized vector.
	Normal_Vector = Normal_Vector.Normalize();
	
	/*Normal_Vector.X = 0;
	Normal_Vector.Y *= 1;*/
	
	float Normal = Normal_Vector.Y;	//-1 to 1
	//cout << " Normal: " << Normal << endl;

	/*int sign = 1;
	if (Height_Difference < 0)
		sign = -1;*/

	//Calculate the desired velocity
	*object->Velocity = object->Velocity->Multiply(Normal * Normal * Transfer_Speed);

	//Add the velocity to the position of object and then modify the velocity by the drag coefficient.
	*object->Position = object->Position->Add(*object->Velocity);
}