#include "Render.h"

#include "SDL/SDL.h"
#include "Tile.h"
#include "World.h"
#include "Vector.h"

SDL_Renderer* RENDER::Renderer;
SDL_Window* RENDER::Window;
int RENDER::Width;
int RENDER::Height;

FloatVector RENDER::Camera;

void RENDER::Start_Window(int width, int height){
    SDL_Init(SDL_INIT_VIDEO);

    Window = SDL_CreateWindow("SPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    
    Renderer = SDL_CreateRenderer(RENDER::Window, -1, 0);

    RENDER::Height = height;
    RENDER::Width = width;
}

void RENDER::Render(World* world){
    //Show the tiles in the window depending on the FOV and the render distance
    for(int x = 0; x <= RENDER::FOV * 2; x++){
        for(int y = 0; y <= RENDER::FOV * 2; y++){
            //Get the tile at the current position
            Tile* tile = world->Get_Tile(RENDER::Camera.X + x, RENDER::Camera.Y + y);

            //If the tile is not null
            if(tile != nullptr){
                //Render the tile
                tile->Render();
            }
        }
    }
}

void RENDER::Update(World* world){
    //Update all the objects in the world
}