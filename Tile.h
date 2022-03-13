#ifndef _TILE_H_
#define _TILE_H_

#include "Object.h"
#include "File_Loader.h"

namespace TILE_IMAGES{
    const string AIR = "Air.png";
    const string GRASS = "Grass.png";
}

//The window consists of tiles.
//The amount of tiles ina window is subject to the zoom level.
class Tile : public Object {
public:
    File* Image;

    Tile(string tile_image, int width, int height, int x, int y) : Object(OBJECT_TYPES::TILE, x, y) {
        Image = File_Loader::Load_File(tile_image);
        Width = width;
        Height = height;
    }

    virtual void Render() override;

    virtual void Update() override {
        //This is used for texture animations
    }
};

#endif