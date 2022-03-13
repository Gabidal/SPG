#ifndef _RENDER_H_
#define _RENDER_H_

#include "SDL/SDL.h"
#include "Vector.h"

class World;

namespace RENDER{
    //Renderer handle for SDL2
    extern SDL_Renderer* Renderer;
    extern SDL_Window* Window;

    extern int Width;
    extern int Height;
    extern FloatVector Camera;

    //This render distnce is used to determine how big of a buffer if given to openGL to render the world.
    //Every unit of distance is a tile
    const int Render_Distance = 10; 

    //This tells how many tiles are rendered in a window from the center of the screen
    const int FOV = 5;

    const bool Full_Screen = false;

    //This function starts the window
    void Start_Window(int Width, int Height);

    //This is the main render function
    void Render(World* world);

    //This function updates all the objects in the world
    void Update(World* world);
}

#endif