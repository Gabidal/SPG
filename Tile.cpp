#include "Tile.h"
#include "Render.h"
#include "SDL/SDL.h"

void Tile::Render() {
    SDL_Rect tmp = Compute_SDL_Rect();
    SDL_RenderCopy(RENDER::Renderer, Image->Texture, NULL, &tmp);
}