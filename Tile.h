#ifndef _TILE_H_
#define _TILE_H_

#include <string>

#include "Object.h"

using namespace std;

namespace TILE_IMAGES{
    const string AIR = "Air.png";
    const string COBBLESTONE = "Cobblestone.png";
    const string OCEAN = "Ocean.png";
    const string GRASS = "Grass.png";
    const string SWAMP = "SwampGrass.png";
    const string DARK_GRASS = "GrassBG.png";
    const string SMOOTH_STONE = "Smooth Stone.png";
    const string ROCK = "Rock.png";
    const string BIRCH = "Birch.png";
    const string OAK = "Oak.png";
    const string RIKKA = "Rikka.png";
    const string CACTUS = "Cactus.png";
}

enum class TILE_TYPES{
    AIR,
    BG,
    ROCK,
    TREE,
    RIKKA,
    CACTUS,
    CRAB,
    COUNT
};

enum class BG_TYPES {
    OCEAN,
    START_OF_GENERATABLE_BG_TILES,
    SWAMP,
    DARK_GRASS,
    GRASS,
    COBBLESTONE,
    SMOOTH_STONE,
    COUNT,
};

enum class TREE_TYPES {
    AIR,
    OAK,
    BIRCH,
    COUNT
};

extern string Get_Tile_Image(TILE_TYPES name);

extern TILE_TYPES Get_Tile_Type(unsigned char color);

extern BG_TYPES Normalize_Y(float Y);

class File;

//The window consists of tiles.
//The amount of tiles ina window is subject to the zoom level.
class Tile : public Object {
public:
    File* Image;

    Tile(string tile_image, int width, int height, float x, float y, float z);

    virtual void Render() override;
};

#endif