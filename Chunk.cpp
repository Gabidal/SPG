#include "Chunk.h"

int CHUNK_SIZE = 16;

Tile* Chunk::Get_Tile(int x, int y) {
    for (int i = 0; i < Tiles.size(); i++) {
        if (Tiles[i]->Position->X == x && Tiles[i]->Position->Y == y) {
            return (Tile*)Tiles[i];
        }
    }
    return nullptr;
}