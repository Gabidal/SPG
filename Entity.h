#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Object.h"
#include "Vector.h"

#include <string>
#include <vector>

#include "Chaos/Include.h"

using namespace std;

enum class Entity_Type
{
	CRAB,
	KING_CRAB,
	COUNT,
};

class Entity : public Object {
public:
	Entity_Type Name;
	Chaos_Handle* Handle;
	class File* Image;

	Entity(FloatVector Location, Entity_Type name);

	virtual void Render() override;
};

class Entity_Template {
public:
	Entity_Type Name;
	class File* Image;
	float Power;
	float Width;
	float Height;

	Entity_Template(Entity_Type name, string image, float power, float width, float height);
};

extern vector<Entity_Template> Entities;

extern Entity_Template* Get_Entity_Template(Entity_Type type);

extern void Entities_Init();

#endif