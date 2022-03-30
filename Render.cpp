#include "Render.h"

#include <algorithm>

#include "SDL/SDL.h"
#include "Tile.h"
#include "World.h"
#include "Vector.h"
#include "Chunk.h"
#include "TerGen.h"
#include "Object.h"

#include "Chaos/Include.h"

SDL_Renderer* RENDER::Renderer;
SDL_Window* RENDER::Window;
int RENDER::Width;
int RENDER::Height;

//This tells how many chunks are rendered around the camera
int RENDER::Render_Distance = 2;
int RENDER::Max_Render_Distance = 10;
int RENDER::Min_Render_Distance = 1;

//This tells how many tiles is fitted to a single row
int RENDER::FOV = 10;
int RENDER::Max_FOV = 32;
int RENDER::Min_FOV = 5;

FloatVector RENDER::Camera;

Object* RENDER::Follow;

void RENDER::Start_Window(int width, int height){
    SDL_Init(SDL_INIT_VIDEO);

    Window = SDL_CreateWindow("SPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    
    Renderer = SDL_CreateRenderer(RENDER::Window, -1, 0);

    RENDER::Height = height;
    RENDER::Width = width;
}

void RENDER::Render(World* world){
    //Gather all the objects in all the surrounding chunks
    vector<Object*> All_Objects;

    Generate_Background_Tiles(world);

    For_Each_Object_In_View([&](int x, int y){
        Chunk* chunk = world->Get_Chunk(Chunk_Coordinates{x, y});
        if (chunk != nullptr) {
            int Previus_All_Objects_Size = All_Objects.size();
            All_Objects.resize(All_Objects.size() + chunk->Objects.size());
            for (int i = 0; i < chunk->Objects.size(); i++) {
                All_Objects[Previus_All_Objects_Size + i] = chunk->Objects[i];
            }
        }
    });

    //Sort the objects by their Z coordinate
    sort(All_Objects.begin(), All_Objects.end(), [](Object* a, Object* b) {
        if (a->Position->Z != b->Position->Z)
            return a->Position->Z < b->Position->Z;

        int Difference = (a->Position->Y + a->Height) - (b->Position->Y + b->Height);
        
        if (Difference == 0) {
            return a->Height * a->Width < b->Height* b->Width;
        }

        return Difference < 0;
    });

    //Because the chunks objects are already ordered so that the first result is always the BG tile
    //Show the tiles in the window depending on the FOV and the render distance
    for (int i = 0; i < All_Objects.size(); i++) {
        All_Objects[i]->Render();
    }

    if (RENDER::Follow) {
        Camera.X = RENDER::Follow->Position->X;
        Camera.Y = RENDER::Follow->Position->Y;
        Camera.Z = RENDER::Follow->Position->Z;
    }
}

void RENDER::Update(World* world){
    Chaos_Update();
}

void RENDER::For_Each_Object_In_View(function<void(int, int)> lambda){
    //Calculate the current center chunk
    int Left = (int)Camera.X / CHUNK_SIZE * CHUNK_SIZE;
    int Top = (int)Camera.Y / CHUNK_SIZE * CHUNK_SIZE;

    //Calculate how many chunksare there to render in next to the center Chunk
    int Surrounding_Chunks_Count = RENDER::FOV / CHUNK_SIZE + Render_Distance + 1;

    for (int x = Left - Surrounding_Chunks_Count * CHUNK_SIZE; x <= Left + Surrounding_Chunks_Count * CHUNK_SIZE; x += CHUNK_SIZE) {
        for (int y = Top - Surrounding_Chunks_Count * CHUNK_SIZE; y <= Top + Surrounding_Chunks_Count * CHUNK_SIZE; y += CHUNK_SIZE) {
            lambda(x, y);
        }
    }
}