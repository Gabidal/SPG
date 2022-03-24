#ifndef _TILE_H_
#define _TILE_H_

#include <string>

#include "Object.h"

using namespace std;

namespace TILE_IMAGES{
    const string AIR = "Air.png";
    const string GRASS = "SwampGrass.png";
    const string ROCK = "Rock.png";
    const string BIRCH = "Birch.png";
    const string OAK = "Oak.png";
    const string RIKKA = "Rikka.png";
    const string CACTUS = "Cactus.png";
}

enum class TILE_TYPES{
    AIR,
    GRASS,
    ROCK,
    TREE,
    RIKKA,
    CACTUS,
    CRAB,
    COUNT
};

enum class TREE_TYPES {
    AIR,
    OAK,
    BIRCH,
    COUNT
};

extern string Get_Tile_Image(TILE_TYPES name);

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