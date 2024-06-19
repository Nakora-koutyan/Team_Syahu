#include "BlockDeta.h"

BlockDeta::BlockDeta() {

};

BlockDeta::~BlockDeta() {
};

void BlockDeta::ResetStageBlockData() {
	for (int i = 0; i < WORLD_BLOCK_X; i++) {
		for (int j = 0; j < WORLD_BLOCK_Y; j++) {
			stageBlockData[i][j] = false;
		}
	}
}
