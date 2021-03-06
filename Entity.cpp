#include "Entity.h"
#include "File_Loader.h"
#include "Render.h"
#include "Tile.h"
#include "TerGen/Include.h"

#include "World.h"

vector<Entity_Template> Entities;

extern World* world;

float Rand() {
	return (float)rand() / RAND_MAX;
}

float Rand(float Min, float Max) {
	return Min + Rand() * (Max - Min);
}

constexpr double Distance = 10;
constexpr double Transfer_Speed = 0.01;

void Dum(Object* This, unsigned long long Delta) {
	if (Delta % ((Entity*)This)->Interval < 100) {
		((Entity*)This)->Interval = Rand(100, 10000);

		//This acts like the objective
		((Entity*)This)->Objective = FloatVector(Rand(-Distance, Distance), Rand(-Distance, Distance));
	}

	*This->Velocity = This->Velocity->Add(((Entity*)This)->Objective.Normalize());
	
	world->Apply_Velocity(This, Delta, Transfer_Speed);
}

void Entities_Init() {
	Entities = {
		//{Entity_Type::HUMAN, "./IMAGES/Player.png", 1},
		{Entity_Type::CRAB, "Crab.png", 1, 10, 1, 1, Dum},
		{Entity_Type::KING_CRAB, "King_Crab.png", 10, 20, 1, 1, Dum},
	};
}

Entity_Template* Get_Entity_Template(Entity_Type type) {
	for (auto &i : Entities) {
		if (i.Name == type)
			return &i;
	}

	return nullptr;
}

Entity::Entity(FloatVector Location, Entity_Type name) : Object(OBJECT_TYPES::ENTITY) {

	Entity_Template* Template = Get_Entity_Template(name);

	Position = new FloatVector(Location);

	Update = Template->Update;

	Position->Z = RENDER::Entity_Draw_Priority;

	Strength = Rand(Template->Min_Power, Template->Max_Power);

	Handle = Get_New_Handle((Vector*)Position, Strength);
	Name = name;

	Image = Template->Image;

	Width = Template->Width;
	Height = Template->Height;
}

void Entity::Render()
{
	SDL_Rect tmp = Compute_SDL_Rect();
	SDL_RenderCopy(RENDER::Renderer, Image->Texture, NULL, &tmp);
}

Entity_Template::Entity_Template(
	Entity_Type name, 
	string image, 
	float minpower, 
	float maxpower, 
	float width, 
	float height,
	void (*update)(Object*, unsigned long long)
){
	Name = name;
	Image = File_Loader::Load_File(image);
	Min_Power = minpower;
	Max_Power = maxpower;
	Width = width;
	Height = height;
	Update = update;
}