#include "Edit.h"
#include<string>
#include"../GameMain/GameMainScene.h"

Edit::Edit()
{
	GameMain = new GameMainScene;
	keyInput = new KeyInput;

	move.x = 0.f;
	move.y = 0.f;
	
	keyInput->SetIsShowMouse(TRUE);
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

	if (move.x < 0)
	{
		move.x = 0.f;
	}
	else if (move.x > WORLD_WIDTH - 1280)
	{
		move.x = WORLD_WIDTH - 1280;
	}

	if (move.y < 0)
	{
		move.y = 0.f;
	}
	else if (move.y > WORLD_HEIGHT - 720)
	{
		move.y = WORLD_HEIGHT - 720;
	}

	GetMousePoint(&mouseX, &mouseY);
	mouseX += move.x;
	mouseY += move.y;
	blockX = mouseX / BLOCK_WIDTH;
	blockY = mouseY / BLOCK_HEIGHT;

	if (KeyInput::GetButtonDown(MOUSE_INPUT_LEFT)) {

		stageData[blockY][blockX] = toolSelect;
	}

	if (KeyInput::GetKey(KEY_INPUT_L))
	{
		SaveStage();
		return new GameMainScene();
	}

	return this;
}

void Edit::Draw()const {
	for (int i = 0; i < WORLD_HEIGHT / BLOCK_HEIGHT; i++)
	{
		DrawLine(BLOCK_WIDTH * i - move.x, 0 - move.y, BLOCK_WIDTH * i - move.x, WORLD_HEIGHT - move.y, 0xffffff, 0);
	}
	for (int i = 0; i < WORLD_WIDTH / BLOCK_WIDTH; i++)
	{
		DrawLine(0 - move.x, BLOCK_HEIGHT * i - move.y, WORLD_WIDTH - move.x, BLOCK_HEIGHT * i - move.y, 0xffffff, 0);
	}

	for (int i = 0; i < WORLD_HEIGHT / BLOCK_HEIGHT; i++)
	{
		for (int j = 0; j < WORLD_WIDTH / BLOCK_WIDTH; j++)
		{
			DrawFormatString(50 * i + 2 - move.x, 50 * j + 2 - move.y, 0x606000, "%d", stageData[j][i]);
		}
	}

	DrawBox(BLOCK_WIDTH * blockX - move.x, BLOCK_HEIGHT * blockY - move.y, BLOCK_WIDTH * (blockX + 1) - move.x, BLOCK_HEIGHT * (blockY + 1) - move.y, 0xFFFF00, 0);



	DrawFormatString(0, 0, 0xffff00, "X:%d,Y:%d", mouseX, mouseY);

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
		//�����L���O�f�[�^�z����f�[�^��ǂݍ���
		for (int i = 0; i < stageHeight; i++)
		{
			for (int j = 0; j < stageWidth; j++)
			{
				file << stageData[i][j] << "\n";
			}
		}
	}
}