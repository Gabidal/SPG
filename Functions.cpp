#include "Functions.h"
#include "TerGen/Include.h"
#include "Chunk.h"

#include "Chaos/Include.h"
#include "Tile.h"

constexpr int AIR_FREQUENCY = 10;
constexpr int INTEGRATION_FREQUENCY = AIR_FREQUENCY / 5;

unsigned char Rock_Generator(Pattern* p, int Amount, Node* node) {
	for (int i = 0; i < Amount * Amount; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			BG_TYPES Elevation = Normalize_Y(p->Nodes[i].Y);

			if (Elevation == BG_TYPES::COBBLESTONE) {
				p->Nodes[i].Color = p->Color;
			}
		}
	}

	if (node && rand() % INTEGRATION_FREQUENCY == 1) {
		BG_TYPES Elevation = Normalize_Y(node->Y);

		if (Elevation == BG_TYPES::COBBLESTONE) {
			return p->Color;
		}
	}

	return 0;
}

unsigned char  Tree_Generator(Pattern* p, int Amount, Node* node) {
	for (int i = 0; i < Amount * Amount; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			BG_TYPES Elevation = Normalize_Y(p->Nodes[i].Y);

			if (Elevation < BG_TYPES::COBBLESTONE) {
				p->Nodes[i].Color = p->Color;
			}
		}
	}

	if (node && rand() % INTEGRATION_FREQUENCY == 1) {
		BG_TYPES Elevation = Normalize_Y(node->Y);

		if (Elevation == BG_TYPES::COBBLESTONE) {
			return p->Color;
		}
	}

	return 0;
}

unsigned char  Rikka_Generator(Pattern* p, int Amount, Node* node) {
	for (int i = 0; i < Amount * Amount; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			BG_TYPES Elevation = Normalize_Y(p->Nodes[i].Y);

			if (Elevation == BG_TYPES::SMOOTH_STONE) {
				p->Nodes[i].Color = p->Color;
			}
		}
	}

	if (node && rand() % INTEGRATION_FREQUENCY == 1) {
		BG_TYPES Elevation = Normalize_Y(node->Y);

		if (Elevation == BG_TYPES::COBBLESTONE) {
			return p->Color;
		}
	}

	return 0;
}
