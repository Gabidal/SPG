#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Vector.h"

#include "SDL/SDL.h"

enum class OBJECT_TYPES {
	TILE,
};

class Object {
public:
	OBJECT_TYPES Type;
	Vector* Position;
	Vector* Velocity;
	int Width;
	int Height;

	Object(OBJECT_TYPES type) {
		Type = type;
		Position = new Vector(0, 0);
		Velocity = new Vector(0, 0);
	}

	Object(OBJECT_TYPES type, float x, float y) {
		Type = type;
		Position = new Vector(x, y);
		Velocity = new Vector(0, 0);
	}

	//This function is used to render the object 
	virtual void Render() {}

	//This function is used to update the object
	virtual void Update() {}

	SDL_Rect Compute_SDL_Rect();
};



#endif