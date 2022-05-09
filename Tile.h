#ifndef _TILE_H_
#define _TILE_H_

#include <string>

#include "Object.h"

using namespace std;

namespace TILE_IMAGES{
    const string AIR = "Air.png";
    const string OCEAN = "Ocean.png";
    const string SAND = "Sand.png";
    const string SAND2 = "Sand2.png";
    const string SAND_GRASSY = "Sand_Grassy.png";
    const string SWAMP = "Swamp.png";
    const string GRASS = "Grass.png";
    const string GRASS2 = "Grass2.png";
    const string TUNDRA = "Tundra.png";
    const string TUNDRA2 = "Tundra2.png";
    const string TUNDRA3 = "Tundra3.png";
    const string GRAVEL = "Gravel.png";
    const string GRAVEL2 = "Gravel2.png";
    const string COBBLESTONE = "Cobblestone.png";
    const string SMOOTH_STONE = "Smooth Stone.png";
    const string SNOW = "Snow.png";

	
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
	WATER,
    SAND,
    SAND2,
    SAND_GRASSY,
    SWAMP,
    GRASS,
    GRASS2,
    TUNDRA,
    TUNDRA2,
    TUNDRA3,
    GRAVEL,
    GRAVEL2,
    COBBLESTONE,
    COBBLESTONE2,
    COBBLESTONE3,
    SMOOTH_STONE,
    SNOW,
    SNOW2,
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