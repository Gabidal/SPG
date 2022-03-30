#include "Entity.h"

#include "File_Loader.h"

#include "Render.h"

vector<Entity_Template> Entities;

void Entities_Init() {
	Entities = {
		//{Entity_Type::HUMAN, "./IMAGES/Player.png", 1},
		{Entity_Type::CRAB, "Crab.png", 1, 1, 1},
		{Entity_Type::KING_CRAB, "King_Crab.png", 10, 1, 1},
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

	Position->Z = 1;

	Handle = Get_New_Handle((Vector*)Position, Template->Power);
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

Entity_Template::Entity_Template(Entity_Type name, string image, float power, float width, float height)
{
	Name = name;
	Image = File_Loader::Load_File(image);
	Power = power;
	Width = width;
	Height = height;
}