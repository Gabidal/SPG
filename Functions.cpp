#include "Functions.h"
#include "TerGen/Include.h"
#include "Chunk.h"

constexpr int AIR_FREQUENCY = 10;

void Rock_Generator(Pattern* p) {
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			p->Nodes[i].Y = 1;
			p->Nodes[i].Color = p->Color;
		}
	}
}

void Tree_Generator(Pattern* p) {
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			p->Nodes[i].Y = 1;
			p->Nodes[i].Color = p->Color;
		}
	}
}

void Rikka_Generator(Pattern* p) {
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			p->Nodes[i].Y = 1;
			p->Nodes[i].Color = p->Color;
		}
	}
}

void Cactus_Generator(Pattern* p) {
	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			p->Nodes[i].Y = 1;
			p->Nodes[i].Color = p->Color;
		}
	}
}
