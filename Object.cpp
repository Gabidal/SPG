#include "Object.h"

#include "Render.h"

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
