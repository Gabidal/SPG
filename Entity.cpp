#include "Entity.h"
#include "File_Loader.h"
#include "Render.h"
#include "Tile.h"
#include "TerGen/Include.h"

vector<Entity_Template> Entities;

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
		This->Velocity = new FloatVector(Rand(-Distance, Distance), Rand(-Distance, Distance));
	}

	float Velocity_Speed = sqrt(This->Velocity->X * This->Velocity->X + This->Velocity->Y * This->Velocity->Y);

	*This->Position = This->Position->Add(This->Velocity->Normalize().Multiply(Transfer_Speed));
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

	Position->Z = (int)BG_TYPES::COUNT;

	Handle = Get_New_Handle((Vector*)Position, Rand(Template->Min_Power, Template->Max_Power));
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