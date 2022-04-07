#include "Object.h"
#include "Render.h"
#include "Vector.h"

SDL_Rect Object::Compute_SDL_Rect()
{
	int Tile_Scale = RENDER::Width / (RENDER::FOV * 2);

	return {
		(int)((Position->X - RENDER::Camera.X) * Tile_Scale),
		(int)((Position->Y - RENDER::Camera.Y) * Tile_Scale),

		Width * Tile_Scale,
		Height * Tile_Scale
	};
}

void NULLPTR(Object*, unsigned long long) {}

Object::Object(OBJECT_TYPES type) {
	Type = type;
	Position = new FloatVector(0, 0);
	Velocity = new FloatVector(0, 0);
	Update = NULLPTR;
}

Object::Object(OBJECT_TYPES type, float x, float y, float z) {
	Type = type;
	Position = new FloatVector(x, y, z);
	Velocity = new FloatVector(0, 0);
	Update = NULLPTR;
}
