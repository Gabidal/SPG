#include "Functions.h"
#include "TerGen/Include.h"
#include "Chunk.h"

#include "Chaos/Include.h"
#include "Tile.h"

constexpr int AIR_FREQUENCY = 10;
constexpr int INTEGRATION_FREQUENCY = AIR_FREQUENCY / 5;

unsigned char Rock_Generator(Pattern* p, int Amount) {
	for (int i = 0; i < Amount * Amount; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			p->Nodes[i].Y = CHAOS_UTILS::Rand(0, (int)BG_TYPES::COUNT - 1);
			p->Nodes[i].Color = p->Color;

		}
	}

	if (rand() % INTEGRATION_FREQUENCY == 1) {
		return p->Color;
	}

	return 0;
}

unsigned char  Tree_Generator(Pattern* p, int Amount) {
	for (int i = 0; i < Amount * Amount; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			p->Nodes[i].Y = CHAOS_UTILS::Rand(0, (int)BG_TYPES::COUNT - 1);
			p->Nodes[i].Color = p->Color;
		}
	}

	if (rand() % INTEGRATION_FREQUENCY == 1) {
		return p->Color;
	}

	return 0;
}

unsigned char  Rikka_Generator(Pattern* p, int Amount) {
	for (int i = 0; i < Amount * Amount; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			p->Nodes[i].Y = CHAOS_UTILS::Rand(0, (int)BG_TYPES::COUNT - 1);
			p->Nodes[i].Color = p->Color;
		}
	}

	if (rand() % INTEGRATION_FREQUENCY == 1) {
		return p->Color;
	}

	return 0;
}

unsigned char  Cactus_Generator(Pattern* p, int Amount) {
	for (int i = 0; i < Amount * Amount; i++) {
		if (rand() % AIR_FREQUENCY == 1) {
			p->Nodes[i].Y = CHAOS_UTILS::Rand(0, (int)BG_TYPES::COUNT - 1);
			p->Nodes[i].Color = p->Color;
		}
	}

	if (rand() % INTEGRATION_FREQUENCY == 1) {
		return p->Color;
	}

	return 0;
}
