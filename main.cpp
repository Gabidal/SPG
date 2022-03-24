#include <iostream>
#include <chrono>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#undef main

#include "Render.h"
#include "Vector.h"
#include "Tile.h"
#include "Key_Listener.h"
#include "World.h"

#include "TerGen.h"

extern FloatVector RENDER::Camera;

using namespace std;

int main(int argc, char** argv)
{
    bool quit = false;
    SDL_Event event;

    //Start the window
    RENDER::Start_Window(800, 600);

    //Create the world
    World* world = new World();

    RENDER::Camera.X = 32;
    RENDER::Camera.Y = 32;

    Generate_Terrain(world);

    /*world->Add_Object(new Tile("Rock.png", 3, 3, 1, 1, 0));
    world->Add_Object(new Tile("Grass.png", 2, 2, 0, 0, 0));
    world->Add_Object(new Tile("Rock.png", 4, 4, 0, -1, 0));*/

    SDL_Texture* Render_Buffer = SDL_CreateTexture(RENDER::Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RENDER::Width, RENDER::Height);

    auto Previus = chrono::high_resolution_clock::now();
    while (!quit)
    {
        auto Now = chrono::high_resolution_clock::now();

        auto Delta = chrono::duration_cast<chrono::nanoseconds>(Now - Previus).count() / 1000000000.0f;

        Previus = Now;

        RENDER::Update(world);

        SDL_SetRenderTarget(RENDER::Renderer, Render_Buffer);
        SDL_SetRenderDrawColor(RENDER::Renderer, 0, 0, 0, 255);

        SDL_RenderClear(RENDER::Renderer);

        RENDER::Render(world);

        SDL_SetRenderTarget(RENDER::Renderer, NULL);

        SDL_RenderClear(RENDER::Renderer);

        SDL_RenderCopy(RENDER::Renderer, Render_Buffer, NULL, NULL);

        //SDL_WaitEvent(&event);
        SDL_PumpEvents();

        /*if (event.type == SDL_QUIT)
        {
            quit = true;
        }*/
        //Listen on wasd keypresses to move the camera
        KEY_LISTENER::Listen_For_Key_Presses(Delta);

        SDL_RenderPresent(RENDER::Renderer);
    }

    SDL_DestroyRenderer(RENDER::Renderer);
    SDL_DestroyWindow(RENDER::Window);

    SDL_Quit();

    return 0;
}