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
            return "";
        case TILE_TYPES::ROCK:
            return TILE_IMAGES::ROCK;
        case TILE_TYPES::TREE: {
            int r = rand() % (int)TREE_TYPES::COUNT;

            switch ((TREE_TYPES)r)
            {
                case TREE_TYPES::BIRCH:
                    return TILE_IMAGES::BIRCH;
                case TREE_TYPES::OAK:
                    return TILE_IMAGES::OAK;
                default:
                    return "";
            }
        }
        case TILE_TYPES::CACTUS:
            return TILE_IMAGES::CACTUS;
        case TILE_TYPES::RIKKA:
            return TILE_IMAGES::RIKKA;
        default: {
            
            return "";
        }
    }
}