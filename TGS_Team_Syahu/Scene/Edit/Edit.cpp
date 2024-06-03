#include "Edit.h"
#include<string>
#include"../GameMain/GameMainScene.h"

Edit::Edit()
{
	camera = new Camera;

	KeyInput::SetIsShowMouse(TRUE);

	move.x = 0.f; move.y = 0.f;
	mouseX = 0; mouseY = 0;
	toolSelect = 1;
	LoadStage(0);
}

Edit::~Edit()
{
}

void Edit::Initialize()
{
	
}

void Edit::Finalize()
{
	
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

	if (move.x < -200)
	{
		move.x = -200.f;
	}
	else if (move.x > WORLD_WIDTH - 1080)
	{
		move.x = WORLD_WIDTH - 1080;
	}

	if (move.y < -200)
	{
		move.y = -200.f;
	}
	else if (move.y > WORLD_HEIGHT - 520)
	{
		move.y = WORLD_HEIGHT - 520;
	}

	GetMousePoint(&mouseX, &mouseY);
	mouseX += move.x;
	mouseY += move.y;
	blockX = mouseX / BLOCK_WIDTH;
	blockY = mouseY / BLOCK_HEIGHT;

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
	for (int i = 0; i <= WORLD_WIDTH / BLOCK_WIDTH; i++)
	{
		DrawLine(BLOCK_WIDTH * i - move.x, 0 - move.y, BLOCK_WIDTH * i - move.x, WORLD_HEIGHT - move.y, 0xffffff, 0);
	}
	for (int i = 0; i <= WORLD_HEIGHT / BLOCK_HEIGHT; i++)
	{
		DrawLine(0 - move.x, BLOCK_HEIGHT * i - move.y, WORLD_WIDTH - move.x, BLOCK_HEIGHT * i - move.y, 0xffffff, 0);
	}

	for (int i = 0; i < WORLD_WIDTH / BLOCK_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT / BLOCK_HEIGHT; j++)
		{
			DrawFormatString(50 * i + 2 - move.x, 50 * j + 2 - move.y, 0x606000, "%d", stageData[j][i]);
		}
	}

	switch (mode)
	{
	case Normal:
		DrawBox(BLOCK_WIDTH * blockX - move.x, BLOCK_HEIGHT * blockY - move.y, BLOCK_WIDTH * (blockX + 1) - move.x + 1, BLOCK_HEIGHT * (blockY + 1) - move.y + 1, 0xFFFF00, 0);
		break;
	case Range:
		if (rangeflg) {
			bool showX = false, showY = false;
			if (rSelectX > blockX) showX = true;
			if (rSelectY > blockY) showY = true;
			DrawBox(BLOCK_WIDTH * rSelectX - move.x + (showX * BLOCK_WIDTH), BLOCK_HEIGHT * rSelectY - move.y + (showY * BLOCK_HEIGHT), BLOCK_WIDTH * (blockX + 1) - move.x-(showX * BLOCK_WIDTH), BLOCK_HEIGHT * (blockY + 1) - move.y-(showY * BLOCK_HEIGHT), 0x00FF00, 0);
		}
		else {
			DrawBox(BLOCK_WIDTH * blockX - move.x, BLOCK_HEIGHT * blockY - move.y, BLOCK_WIDTH * (blockX + 1) - move.x + 1, BLOCK_HEIGHT * (blockY + 1) - move.y + 1, 0x00FF00, 0);
		}
		break;
	}




	DrawFormatString(0, 0, 0xffff00, "X:%d,Y:%d", mouseX, mouseY);
	DrawFormatString(150, 0, 0x00ffff, "SelectObject:%s", objString[toolSelect]);
	DrawFormatString(300, 0, 0x00ffff, "%d", mode);

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
		for (int i = 0; i < stageHeight; i++)
		{
			for (int j = 0; j < stageWidth; j++)
			{
				file >> stageData[i][j];
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
		file << stageWidth << "\n";
		file << stageHeight << "\n";
		for (int i = 0; i < stageHeight; i++)
		{
			for (int j = 0; j < stageWidth; j++)
			{
				file << stageData[i][j] << "\n";
			}
		}
	}
}