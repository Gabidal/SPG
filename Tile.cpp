#include "Tile.h"
#include "Render.h"
#include "SDL/SDL.h"
#include "File_Loader.h"

void Tile::Render() {
    SDL_Rect tmp = Compute_SDL_Rect();
    SDL_RenderCopy(RENDER::Renderer, Image->Texture, NULL, &tmp);
}

Tile::Tile(string tile_image, int width, int height, float x, float y, float z) : Object(OBJECT_TYPES::TILE, x, y, z) {
    Image = File_Loader::Load_File(tile_image);
    Width = width;
    Height = height;
}