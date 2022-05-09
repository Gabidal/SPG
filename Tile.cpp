#include "Tile.h"
#include "Render.h"
#include "SDL/SDL.h"
#include "File_Loader.h"
#include "TerGen/Include.h"

#include "Functions.h"

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
        case TILE_TYPES::WATER_ROCK:
            return TILE_IMAGES::WATER_ROCK;
        default: {
            
            return "";
        }
    }
}

TILE_TYPES Get_Tile_Type(unsigned char color)
{
    FUNCTION func = UTILS::Get_Function(color);

    if (func == Rock_Generator)
        return TILE_TYPES::ROCK;
    else if (func == Tree_Generator)
        return TILE_TYPES::TREE;
    else if (func == Rikka_Generator)
        return TILE_TYPES::RIKKA;
    else if (func == Cactus_Generator)
        return TILE_TYPES::CACTUS;
    else if (func == Water_Rock_Generator)
        return TILE_TYPES::WATER_ROCK;  
    else {
        return TILE_TYPES::AIR;
    }
}

BG_TYPES Normalize_Y(float Y) {
    int Normalized_Y = (abs(Y) * (int)BG_TYPES::COUNT);

    int Offset_Y = (Normalized_Y % (int)BG_TYPES::COUNT);

    //if (Offset_Y <= (int)BG_TYPES::START_OF_GENERATABLE_BG_TILES) {
    //    Offset_Y += ((int)BG_TYPES::START_OF_GENERATABLE_BG_TILES) + 1;
    //}

    return (BG_TYPES)Offset_Y;
}