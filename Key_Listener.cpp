#include "SDL/SDL.h"

#include "Key_Listener.h"
#include "Render.h"
#include "Vector.h"
#include "Object.h"

void KEY_LISTENER::Listen_For_Key_Presses(float delta) {
    auto Keyboard = SDL_GetKeyboardState(NULL);

    delta *= 100;

    FloatVector Direction(0, 0);

    if (Keyboard[SDL_SCANCODE_W]) {
        Direction.Y -= 1;
    }
    if (Keyboard[SDL_SCANCODE_S]) {
        Direction.Y += 1;
    }
    if (Keyboard[SDL_SCANCODE_A]) {
        Direction.X -= 1;
    }
    if (Keyboard[SDL_SCANCODE_D]) {
        Direction.X += 1;
    }

    RENDER::Camera = RENDER::Camera.Add(Direction.Normalize().Scale(delta));

    if (RENDER::Follow)
        *RENDER::Follow->Position = RENDER::Follow->Position->Add(Direction.Normalize().Scale(delta));
}

void KEY_LISTENER::Listen_For_Mouse(float delta)
{

    //10% of Render Distance
    int Render_Part_Incrementer = (RENDER::Max_Render_Distance - RENDER::Min_Render_Distance) / 10;
    int FOV_Part_incrementer = (RENDER::Max_FOV - RENDER::Min_FOV) / 10;

    SDL_Event Event;

    SDL_PollEvent(&Event);

    if (Event.type == SDL_MOUSEWHEEL)
    {
        if (Event.wheel.y > 0) // scroll up
        {
            RENDER::Render_Distance = max(RENDER::Render_Distance - Render_Part_Incrementer, RENDER::Min_Render_Distance);
            RENDER::FOV = max(RENDER::FOV - FOV_Part_incrementer, RENDER::Min_FOV);
        }
        else if (Event.wheel.y < 0) // scroll down
        {
            RENDER::Render_Distance = min(RENDER::Render_Distance + Render_Part_Incrementer, RENDER::Max_Render_Distance);
            RENDER::FOV = min(RENDER::FOV + FOV_Part_incrementer, RENDER::Max_FOV);
        }
    }
    else if (Event.type == SDL_MOUSEBUTTONDOWN)
    {
        // ... handle mouse clicks ...
    }

}