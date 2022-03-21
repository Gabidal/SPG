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

string Get_Tile_Image(TILE_TYPES name){
    switch(name){
        case TILE_TYPES::AIR:
            return TILE_IMAGES::AIR;
        case TILE_TYPES::GRASS:
            return TILE_IMAGES::GRASS;
        case TILE_TYPES::ROCK:
            return TILE_IMAGES::ROCK;
        default: {
            
            return "";
        }
    }
}