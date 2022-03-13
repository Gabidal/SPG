#include <iostream>
#include <chrono>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#undef main

#include "Render.h"
#include "Vector.h"
#include "Tile.h"
#include "Key_Listener.h"

using namespace std;

int main(int argc, char** argv)
{
    bool quit = false;
    SDL_Event event;

    //Start the window
    RENDER::Start_Window(800, 600);

    //Create the world
    World* world = new World();

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            //create a test tile with Air.png
            Tile* tile = new Tile(TILE_IMAGES::GRASS, 1, 1, i, j);

            world->Tile_Buffer.push_back(tile);
        }
    }

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