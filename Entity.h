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
	vector<FloatVector> Path_Cache;

	int Interval = 1;

	Entity(FloatVector Location, Entity_Type name);

	virtual void Render() override;
};

class Entity_Template {
public:
	Entity_Type Name;
	class File* Image;
	float Min_Power;
	float Max_Power;
	float Width;
	float Height;

	void (*Update)(Object*, unsigned long long);

	Entity_Template(Entity_Type name, string image, float minpower, float maxpower, float width, float height, void (*update)(Object*, unsigned long long));
};

extern vector<Entity_Template> Entities;

extern Entity_Template* Get_Entity_Template(Entity_Type type);

extern void Entities_Init();

#endif