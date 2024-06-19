#pragma once
#include "StageBlock.h"
class BlockDeta
{
private:
	bool stageBlockData[WORLD_BLOCK_X][WORLD_BLOCK_Y];

public:
	BlockDeta();

	~BlockDeta();

	bool getStageBlockData(int x, int y) {
		return stageBlockData[x][y];
	}

	void setStageBlockData(int x, int y, bool is) {
		stageBlockData[x][y] = is;
	}

	void ResetStageBlockData();
};

