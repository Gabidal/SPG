#include <iostream>
#include <chrono>
#include <time.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#undef main

#include "Render.h"
#include "Vector.h"
#include "Tile.h"
#include "Key_Listener.h"
#include "World.h"
#include "Entity.h"
#include "Chunk.h"

#include "TerGen.h"
#include "Chaos/Include.h"

extern FloatVector RENDER::Camera;

using namespace std;

int main(int argc, char** argv)
{
    bool quit = false;
    SDL_Event event;

    //Start the window
    RENDER::Start_Window(1920, 1080);

    //Create the world
    World* world = new World();

    RENDER::Camera.X = 0;
    RENDER::Camera.Y = 0;

    srand(time(0));

    Generate_Terrain(world);

    Entities_Init();
    Chaos_Init(0.01);

    Entity* last;

    for (int i = 0; i < 100; i++) {
        FloatVector location = {
            (float)(rand() % (CHUNK_SIZE * CHUNK_AMOUNT_SQRT)),
            (float)(rand() % (CHUNK_SIZE * CHUNK_AMOUNT_SQRT)),
        };
		
        Entity_Type type = (Entity_Type)(rand() % (int)Entity_Type::COUNT);
        Entity* ent = new Entity(location, type);

        world->Add_Object(ent);

        last = ent;
    }

    //RENDER::Follow = last;

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

        SDL_PumpEvents();

        //Listen on wasd keypresses to move the camera
        KEY_LISTENER::Listen_For_Key_Presses(Delta);
        KEY_LISTENER::Listen_For_Mouse(Delta);

        SDL_RenderPresent(RENDER::Renderer);
    }

    SDL_DestroyRenderer(RENDER::Renderer);
    SDL_DestroyWindow(RENDER::Window);

    SDL_Quit();

    return 0;
}