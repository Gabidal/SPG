#ifndef _KEY_LISTENER_H_
#define _KEY_LISTENER_H_

#include "Render.h"

#include "SDL/SDL.h"

namespace KEY_LISTENER{
    void Listen_For_Key_Presses(float delta){
        auto Keyboard = SDL_GetKeyboardState(NULL);

        delta *= 10;

        Vector Direction(0, 0);

        if(Keyboard[SDL_SCANCODE_W]){
            Direction.Y -= 1;
        }
        if(Keyboard[SDL_SCANCODE_S]){
            Direction.Y += 1;
        }
        if(Keyboard[SDL_SCANCODE_A]){
            Direction.X -= 1;
        }
        if(Keyboard[SDL_SCANCODE_D]){
            Direction.X += 1;
        }

        RENDER::Camera = RENDER::Camera.Add(Direction.Normalize().Scale(delta));
    }
}

#endif