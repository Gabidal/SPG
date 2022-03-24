#ifndef _RENDER_H_
#define _RENDER_H_

#include <functional>

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

    //This tells how many chunks are rendered around the camera
    const int Render_Distance = 2; 

    //This tells how many tiles is fitted to a single row
    const int FOV = 10;

    const bool Full_Screen = false;

    //This function starts the window
    void Start_Window(int Width, int Height);

    //This is the main render function
    void Render(World* world);

    //This function updates all the objects in the world
    void Update(World* world);

    //Utils

    //This function goes through all the x & y coordinates that a camre is looking at and call the lambda function on them
    void For_Each_Object_In_View(function<void(int, int)> lambda);
}

#endif