#include "Edit.h"
#include<string>
#include"../GameMain/GameMainScene.h"

Edit::Edit()
{

	KeyInput::SetIsShowMouse(TRUE);

	move.x = 0.f; move.y = WORLD_HEIGHT - SCREEN_HEIGHT;
	mouseX = 0; mouseY = 0;
	toolSelect = 1;
	rangeflg = false;
	LoadStage(NOW_LOAD_STAGE);
	for (int i = 0; i < BLOCK_TYPE; i++) {
		blockImg[i] = NULL;
	}
}

Edit::~Edit()
{
}

void Edit::Initialize()
{
	blockImg[0] = LoadGraph("Resource/Images/Stage/Tiles/blank.png");
	blockImg[1] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_1.png");
	blockImg[2] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_2.png");
	blockImg[3] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_3.png");
	blockImg[4] = LoadGraph("Resource/Images/Stage/Tiles/ceiling_4.png");
	blockImg[5] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_1.png");
	blockImg[6] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_2.png");
	blockImg[7] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_3.png");
	blockImg[8] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_4.png");
	blockImg[9] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_corner_left.png");
	blockImg[10] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_corner_right.png");
	blockImg[11] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_1.png");
	blockImg[12] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_2.png");
	blockImg[13] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_3.png");
	blockImg[14] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_4.png");
	blockImg[15] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_corner_left.png");
	blockImg[16] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_corner_right.png");
	blockImg[17] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_transition_1.png");
	blockImg[18] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_carpet_transition_2.png");
	blockImg[19] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_carpet_transition_1.png");
	blockImg[20] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_carpet_transition_2.png");
	blockImg[21] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_transition_1.png");
	blockImg[22] = LoadGraph("Resource/Images/Stage/Tiles/floor_tile_wood_transition_2.png");
	blockImg[23] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_1.png");
	blockImg[24] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_2.png");
	blockImg[25] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_3.png");
	blockImg[26] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_4.png");
	blockImg[27] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_corner_left.png");
	blockImg[28] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_corner_right.png");
	blockImg[29] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_1.png");
	blockImg[30] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_2.png");
	blockImg[31] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_3.png");
	blockImg[32] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_4.png");
	blockImg[33] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_corner_left.png");
	blockImg[34] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_corner_right.png");
	blockImg[35] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_transition_1.png");
	blockImg[36] = LoadGraph("Resource/Images/Stage/Tiles/floor_wood_carpet_transition_2.png");
	blockImg[37] = LoadGraph("Resource/Images/Stage/Tiles/tile_side_left.png");
	blockImg[38] = LoadGraph("Resource/Images/Stage/Tiles/tile_side_right.png");
}

void Edit::Finalize()
{
	for (int i = 0; i < BLOCK_TYPE; i++)
	{
		DeleteGraph(blockImg[i]);
	}

}

SceneBase* Edit::Update() {

	Camera::SetTarget({ 520,0 }, true);

	if (resultDisplay > 0) {
		resultDisplay--;
	}

	if (KeyInput::GetKeyDown(KEY_INPUT_W))
	{
		move.y -= 10.f;
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_S))
	{
		move.y += 10.f;
	}

	if (KeyInput::GetKeyDown(KEY_INPUT_A))
	{
		move.x -= 10.f;
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_D))
	{
		move.x += 10.f;
	}

	if (KeyInput::GetMouseWheel() < 0) {
		if (--toolSelect < 1) toolSelect = OBJECT_TYPE_MAX - 1;
	}
	else if (KeyInput::GetMouseWheel() > 0) {
		if (++toolSelect > OBJECT_TYPE_MAX - 1) toolSelect = 1;
	}



	if (move.x < -EDIT_MARGIN)
	{
		move.x = -EDIT_MARGIN;
	}
	else if (move.x > WORLD_WIDTH - SCREEN_WIDTH - EDIT_MARGIN)
	{
		move.x = WORLD_WIDTH - SCREEN_WIDTH - EDIT_MARGIN;
	}

	if (move.y < -EDIT_MARGIN)
	{
		move.y = -EDIT_MARGIN;
	}
	else if (move.y > WORLD_HEIGHT - SCREEN_HEIGHT - EDIT_MARGIN)
	{
		move.y = WORLD_HEIGHT - SCREEN_HEIGHT - EDIT_MARGIN;
	}

	GetMousePoint(&mouseX, &mouseY);
	mouseX += (int)move.x;
	mouseY += (int)move.y;
	blockX = mouseX / (int)BLOCK_WIDTH;
	blockY = mouseY / (int)BLOCK_HEIGHT;

	switch (mode)
	{
	case Normal:
		if (KeyInput::GetButtonDown(MOUSE_INPUT_LEFT)) {
			stageData[blockY][blockX] = toolSelect;
		}
		if (KeyInput::GetButtonDown(MOUSE_INPUT_RIGHT)) {
			stageData[blockY][blockX] = 0;
		}
		break;
	case Range:
		if (KeyInput::GetButtonDown(MOUSE_INPUT_LEFT) && !rangeflg) {
			rSelectX = blockX;
			rSelectY = blockY;
			rangeflg = true;
		}
		else if (KeyInput::GetButtonUp(MOUSE_INPUT_LEFT) && rangeflg) {
			int setBlockX = rSelectX; 
			int setBlockY = rSelectY;
			int defBlockX = blockX - rSelectX;
			int defBlockY = blockY - rSelectY;
			if (defBlockX >= 0) {
				setBlockX = rSelectX;
			} else {
				setBlockX = blockX;
			}
			if (defBlockY >= 0) {
				setBlockY = rSelectY;
			} else {
				setBlockY = blockY;
			}
			for (int i = 0; i <= abs(defBlockY); i++) {
				for (int j = 0; j <= abs(defBlockX); j++) {
					stageData[setBlockY + i][setBlockX + j] = toolSelect;
				}
			}
			rangeflg = false;
		}
		if (KeyInput::GetButtonDown(MOUSE_INPUT_RIGHT) && !rangeflg) {
			rSelectX = blockX;
			rSelectY = blockY;
			rangeflg = true;
		}
		else if (KeyInput::GetButtonUp(MOUSE_INPUT_RIGHT) && rangeflg) {
			int setBlockX = rSelectX;
			int setBlockY = rSelectY;
			int defBlockX = blockX - rSelectX;
			int defBlockY = blockY - rSelectY;
			if (defBlockX >= 0) {
				setBlockX = rSelectX;
			}
			else {
				setBlockX = blockX;
			}
			if (defBlockY >= 0) {
				setBlockY = rSelectY;
			}
			else {
				setBlockY = blockY;
			}
			for (int i = 0; i <= abs(defBlockY); i++) {
				for (int j = 0; j <= abs(defBlockX); j++) {
					stageData[setBlockY + i][setBlockX + j] = 0;
				}
			}
			rangeflg = false;
		}
		break;
	}

	if (KeyInput::GetButton(MOUSE_INPUT_MIDDLE)) {
		switch (mode) {
		case Normal:
			mode = Range;
			break;
		case Range:
			mode = Normal;
			break;
		default:
			break;
		}
	}

	if (KeyInput::GetKey(KEY_INPUT_L))
	{
		SaveStage();
		return new GameMainScene();
	}

	return this;
}

void Edit::Draw()const {

	for (int i = 0; i < WORLD_WIDTH / BLOCK_WIDTH; i++)
	{
		DrawLineAA(BLOCK_WIDTH * i - move.x, -move.y, BLOCK_WIDTH * i - move.x, WORLD_HEIGHT - move.y, 0xffffff, 0);
		for (int j = 0; j < WORLD_HEIGHT / BLOCK_HEIGHT; j++)
		{
			DrawLineAA(-move.x, BLOCK_HEIGHT * j - move.y, WORLD_WIDTH - move.x, BLOCK_HEIGHT * j - move.y, 0xffffff, 0);
			int offset = 2;
			DrawFormatStringF(BLOCK_WIDTH * i + offset - move.x, BLOCK_HEIGHT * j + offset - move.y, color[stageData[j][i]], "%d", stageData[j][i]);
			if (stageData[j][i] >= OTHER_OBJECT) {
				DrawExtendGraph(BLOCK_WIDTH * i - (int)move.x, BLOCK_HEIGHT * j - (int)move.y, BLOCK_WIDTH * (i + 1) - (int)move.x, BLOCK_HEIGHT * (j + 1) - (int)move.y, blockImg[stageData[j][i]-4], 0);
			}
		}
	}

	switch (mode)
	{
	case Normal:
		DrawBox((int)BLOCK_WIDTH * blockX - (int)move.x, (int)BLOCK_HEIGHT * blockY - (int)move.y, (int)BLOCK_WIDTH * (blockX + 1) - (int)move.x + 1, (int)BLOCK_HEIGHT * (blockY + 1) - (int)move.y + 1, 0xFFFF00, 0);
		break;
	case Range:
		if (rangeflg) {
			bool showX = false, showY = false;
			if (rSelectX > blockX) showX = true;
			if (rSelectY > blockY) showY = true;
			DrawBox((int)BLOCK_WIDTH * rSelectX - (int)move.x + (showX * (int)BLOCK_WIDTH), (int)BLOCK_HEIGHT * rSelectY - (int)move.y + (showY * (int)BLOCK_HEIGHT), (int)BLOCK_WIDTH * (blockX + 1) - (int)move.x-(showX * (int)BLOCK_WIDTH), (int)BLOCK_HEIGHT * (blockY + 1) - (int)move.y-(showY * (int)BLOCK_HEIGHT), 0x00FF00, 0);
		}
		else {
			DrawBox((int)BLOCK_WIDTH * blockX - (int)move.x, (int)BLOCK_HEIGHT * blockY - (int)move.y, (int)BLOCK_WIDTH * (blockX + 1) - (int)move.x + 1, (int)BLOCK_HEIGHT * (blockY + 1) - (int)move.y + 1, 0x00FF00, 0);
		}
		break;
	}

	if (toolSelect < OTHER_OBJECT) {
		DrawFormatString(0, 0, 0x00ffff, "SelectObject:%s", objString[toolSelect]);
	}
	else
	{
		DrawFormatString(0, 0, 0x00ffff, "SelectObject:");
		DrawGraph(100, 0, blockImg[toolSelect - OTHER_OBJECT], 0);
	}

	if (resultDisplay > 0) {
		if (success) {
			DrawFormatString(50, 50, 0x00ff00, "file opened!");
		}
		else
		{
			DrawFormatString(50, 50, 0xff0000, "file not open!");
		}
	}

}

void Edit::LoadStage(int stage) 
{
	stageNum = stage;
	std::string fname;
	std::string fpassCoupling = "Resource/StageData/";
	std::string fpass;

	switch (stage)
	{
	case 0:
		fname = "FirstStage.txt";
		break;
	case 1:
		fname = "SecondStage.txt";
		break;
	case 2:
		fname = "ThirdStage.txt";
		break;
	default:
		break;
	}

	// 文字列の連結
	fpass = fpassCoupling + fname;

	std::ifstream file(fpass.c_str());
	if (file)
	{
		file >> stageWidth;
		file >> stageHeight;
		for (int i = 0; i < stageHeight; i++) {
			for (int j = 0; j < stageWidth; j++) {
				file >> stageData[i][j];
				ObjectExchange(stageData[i][j], 1, 4);
				stageOldData[i][j] = stageData[i][j];
			}
		}
		success = TRUE;
	}
	else {
		success = FALSE;
	}
	resultDisplay = 180;
}

void Edit::SaveStage() {
	const char* fpass = "";
	switch (stageNum)
	{
	case 0:
		fpass = "Resource/StageData/FirstStage.txt";
		break;
	case 1:
		fpass = "Resource/StageData/SecondStage.txt";
		break;
	case 2:
		fpass = "Resource/StageData/ThirdStage.txt";
		break;
	}
	std::ofstream file(fpass);
	if (file)
	{
		int newStageHeight = WORLD_BLOCK_Y;
		int newStageWidth = WORLD_BLOCK_X;
		file << newStageWidth << "\n";
		file << newStageHeight << "\n";
		for (int i = 0; i < newStageHeight; i++) {
			for (int j = 0; j < newStageWidth; j++) {
				file << stageData[i][j] << "\n";
			}
		}
	}
}

void Edit::ObjectExchange(int watch, int target, int exchange) {
	if (watch == target) {
		watch = exchange;
	}
}