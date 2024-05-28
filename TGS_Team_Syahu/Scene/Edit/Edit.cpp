#include "Edit.h"
#include<string>
#include"../GameMain/GameMainScene.h"

Edit::Edit()
{
	GameMain = new GameMainScene;
	keyInput = new KeyInput;
	
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

	GetMousePoint(&mouseX, &mouseY);
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
		DrawLine(BLOCK_WIDTH * i, 0, BLOCK_WIDTH * i, WORLD_HEIGHT, 0xffffff, 0);
	}
	for (int i = 0; i < WORLD_WIDTH / BLOCK_WIDTH; i++)
	{
		DrawLine(0, BLOCK_HEIGHT * i, WORLD_WIDTH, BLOCK_HEIGHT * i, 0xffffff, 0);
	}

	for (int i = 0; i < WORLD_HEIGHT / BLOCK_HEIGHT; i++)
	{
		for (int j = 0; j < WORLD_WIDTH / BLOCK_WIDTH; j++)
		{
			DrawFormatString(50 * i + 2, 50 * j + 2, 0x606000, "%d", stageData[j][i]);
		}
	}

	DrawBox(BLOCK_WIDTH * blockX, BLOCK_HEIGHT * blockY, BLOCK_WIDTH * (blockX + 1), BLOCK_HEIGHT * (blockY + 1), 0xFFFF00, 0);



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