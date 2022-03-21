#ifndef _TILE_H_
#define _TILE_H_

#include <string>

#include "Object.h"

using namespace std;

namespace TILE_IMAGES{
    const string AIR = "Air.png";
    const string GRASS = "Grass.png";
    const string ROCK = "Rock.png";
}

enum class TILE_TYPES{
    AIR,
    GRASS,
    ROCK,
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