#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "SDL/SDL.h"

enum class OBJECT_TYPES {
	TILE,
};

class FloatVector;

class Object {
public:
	OBJECT_TYPES Type;
	FloatVector* Position;
	FloatVector* Velocity;
	int Width;
	int Height;

	Object(OBJECT_TYPES type);

	Object(OBJECT_TYPES type, float x, float y);

	//This function is used to render the object 
	virtual void Render() {}

	//This function is used to update the object
	virtual void Update() {}

	SDL_Rect Compute_SDL_Rect();
};
#endif