#include "Chunk.h"
#include "Vector.h"

int CHUNK_SIZE = 16;
int CHUNK_AMOUNT_SQRT = 100; //total amount is CHUNK_AMOUNT_SQRT^2

Tile* Chunk::Get_Object(int x, int y) {
    //because SDL library doesnt have Z axis support we need to make
    //a hacky style by sorting the chunks objects by their Z coordinate to draw
    //the lower objects first.
    //This is a very inefficient way of doing this but it works for now.

    for (int i = 0; i < Objects.size(); i++) {
        if (Objects[i]->Position->X == x && Objects[i]->Position->Y == y) {
            return (Tile*)Objects[i];
        }
    }

    return nullptr;
}