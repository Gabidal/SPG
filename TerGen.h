#include "TerGen/Include.h"

#include <vector>

using namespace std;

class World;
class Object;

extern void Generate_Terrain(World* world);

extern Object* Get_Right_Object(Node*, int, int);

extern Object* Get_Right_BG_Tile(Node*, int, int);

extern string Get_BG_Tile_Name(enum class BG_TYPES bg);

extern void Generate_Background_Tiles(float Elevation, World* world, vector<Object*> &All_Objects);
