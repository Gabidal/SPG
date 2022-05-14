#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "SDL/SDL.h"

enum class OBJECT_TYPES {
	TILE,
	ENTITY,
};

class FloatVector;

class Object {
public:
	OBJECT_TYPES Type;
	FloatVector* Position;
	FloatVector* Velocity;
	int Width;
	int Height;

	float Strength = 10;

	Object(OBJECT_TYPES type);

	Object(OBJECT_TYPES type, float x, float y, float z);

	//This function is used to render the object 
	virtual void Render() {}

	//This function is used to update the object
	//virtual void Update() {}
	void (*Update)(Object*, unsigned long long Delta);

	SDL_Rect Compute_SDL_Rect();
};
#endif