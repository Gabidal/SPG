#ifndef _FILE_LOADER_H_
#define _FILE_LOADER_H_

#include <string>
#include <fstream>
#include <map>
#include <sstream>

#include "World.h"

using namespace std;

enum class FILE_TYPE{
    PNG,
    RAW
};

class SDL_Texture;
class SDL_Surface;

class File{
public:
    FILE_TYPE Type;
    SDL_Texture* Texture;
    SDL_Surface* Surface;

    string Data;
    string Name;

    int Width;
    int Height;

    File(FILE_TYPE type, SDL_Texture* texture, SDL_Surface* surface, string name, int width, int height) {
        Type = type;
        Texture = texture;
        Surface = surface;
        Name = name;
        Width = width;
        Height = height;
    }

    File(){
        Type = FILE_TYPE::RAW;
    }
};

namespace File_Loader {
    //Store all already loaded images to a cache to avoid loading the same image multiple times.
    static map<string, File*> Image_Cache;

    //Loads a file into a string.
    //Also checks if the file is loaded already.
    File* Load_File(string file_name);
    inline void Clear_Cache();
    inline string Save_File(string file_name, World* world) { return ""; }
}

#endif