#include "Render.h"

#include "SDL/SDL.h"

SDL_Renderer* RENDER::Renderer;
SDL_Window* RENDER::Window;
int RENDER::Width;
int RENDER::Height;

Vector RENDER::Camera;

void RENDER::Start_Window(int width, int height){
    SDL_Init(SDL_INIT_VIDEO);

    Window = SDL_CreateWindow("SPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    
    Renderer = SDL_CreateRenderer(RENDER::Window, -1, 0);

    RENDER::Height = height;
    RENDER::Width = width;
}

void RENDER::Render(World* world){
    //Show the tiles in the window depending on the FOV and the render distance
    for(int i = 0; i < world->Tile_Buffer.size(); i++){
        if((world->Tile_Buffer[i]->Position->X - Camera.X + 1) >= 0 && (world->Tile_Buffer[i]->Position->X - Camera.X) < FOV * 2 && (world->Tile_Buffer[i]->Position->Y - Camera.Y + 1) >= 0 && (world->Tile_Buffer[i]->Position->Y - Camera.Y) < FOV * 2){
            //Render the tile
            world->Tile_Buffer[i]->Render();
        }
    }
}

void RENDER::Update(World* world){
    //Update all the objects in the world
    for(int i = 0; i < world->Tile_Buffer.size(); i++){
        world->Tile_Buffer[i]->Update();
    }

    for(int i = 0; i < world->Entity_Buffer.size(); i++){
        world->Entity_Buffer[i]->Update();
    }

    for(int i = 0; i < world->Particle_Buffer.size(); i++){
        world->Particle_Buffer[i]->Update();
    }
}