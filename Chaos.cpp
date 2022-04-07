#include "Chaos.h"

#include "Entity.h"

#include <map>

Vector Cache(0, 0);

Vector* Get_Cache() {
	Cache = Vector(0, 0);

	return &Cache;
}

Vector* A_Is_Inside_Of_B(Chaos_Handle* A, Chaos_Handle* B) {
	Vector* Result = Get_Cache();
	
	*Result += *B->Location - *A->Location;

	return Result;
}

Vector* Close(Chaos_Handle* A, Chaos_Handle* B) {
	if (A->Radius < B->Radius) {
		Vector* Result = Get_Cache();

		*Result += *B->Location - *A->Location;
	}

	return nullptr;
}

Vector* Too_Close(Chaos_Handle* A, Chaos_Handle* B) {
	Vector* Result = Get_Cache();

	*Result -= *B->Location - *A->Location;

	return Result;
}

void Init_Chaos()
{
	Entities_Init();
	Chaos_Init({
		{STATE::A_INSIDE_OF_B, A_Is_Inside_Of_B},
		{STATE::SAME_RADIUS, Too_Close},

		{STATE::CLOSE, Close},
	}, 0.025);
}