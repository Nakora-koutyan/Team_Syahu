#include "Edit.h"
#include<string>

Edit::Edit()
{
	GameMain = new GameMainScene;
	mouseX = 0; mouseY = 0;
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

	GetMousePoint(mouseX, mouseY);

	if (KeyInput::GetKey(KEY_INPUT_L))
	{
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

	DrawFormatString(50, 50, 0xffff00, "X:%d,Y:%d", mouseX, mouseY);
	//int old_size = GetFontSize();
	//SetFontSize(24);
	//for (int i = 0; i < stage_height_num; i++)
	//{
	//	for (int j = 0; j < stage_width_num; j++)
	//	{
	//		stage[i][j]->Draw();
	//		if (select_data[i][j] == true)
	//		{
	//			DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x + BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0xff0000, false);
	//		}
	//		//�e�Ŕ�
	//		if (stage_data[i][j] == 9)
	//		{
	//			DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x + BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0x892F1B, true);
	//			DrawStringF(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, "�U��", 0x76D0E4);
	//		}
	//		if (stage_data[i][j] == 10)
	//		{
	//			DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x + BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0x892F1B, true);
	//			DrawStringF(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, "�W�����v", 0x76D0E4);
	//		}
	//		if (stage_data[i][j] == 11)
	//		{
	//			DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x + BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0x892F1B, true);
	//			DrawStringF(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, "�W�����v�U��", 0x76D0E4);
	//		}
	//		if (stage_data[i][j] == 12)
	//		{
	//			DrawBoxAA(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, stage[i][j]->GetLocalLocation().x + BOX_WIDTH, stage[i][j]->GetLocalLocation().y + BOX_HEIGHT, 0x892F1B, true);
	//			DrawStringF(stage[i][j]->GetLocalLocation().x, stage[i][j]->GetLocalLocation().y, "�������", 0x76D0E4);
	//		}
	//	}
	//}
	SetFontSize(16);
	/*DrawBoxAA(tool_location.x, tool_location.y, tool_location.x + tool_size.width, tool_location.y + tool_size.height, 0x000000, true);
	DrawBoxAA(tool_location.x, tool_location.y, tool_location.x + tool_size.width, tool_location.y + tool_size.height, 0xffffff, false);
	DrawStringF(tool_location.x, tool_location.y + 60, "���N���b�N�őI����z�u", 0xffffff);
	DrawStringF(tool_location.x, tool_location.y + 80, "ctrl+z�ň�߂�", 0xffffff);
	DrawStringF(tool_location.x + tool_size.width - 270, tool_location.y + 80, "B�L�[�ŕۑ����Q�[�����C���֖߂�", 0xffffff);*/

	//���ݑI�𒆂̃I�u�W�F�N�g�𕪂���₷��	
	/*for (int i = 0; i < OBJECT_TYPE_NUM; i++)
	{
		if (current_type == i)
		{
			DrawBoxAA(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0xffffff, true);
			DrawBoxAA(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0x000000, false);
			DrawFormatStringF(tool_location.x + (i * 50), tool_location.y + 15, 0x000000, "%s", obj_string[i]);
		}
		else
		{
			DrawBoxAA(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0x000000, true);
			DrawBoxAA(tool_location.x + (i * 50), tool_location.y, tool_location.x + (i * 50) + 50, tool_location.y + 50, 0xffffff, false);
			DrawFormatStringF(tool_location.x + (i * 50), tool_location.y + 15, 0xffffff, "%s", obj_string[i]);
		}
	}*/

	////�X�e�[�W���ύX�p�\��
	//DrawStringF(width_button_location.x - 5, width_button_location.y - 20, "�X�e�[�W��", 0xffffff);

	////�X�e�[�W�̉��̃u���b�N�����\�������G���A
	//DrawBoxAA(width_button_location.x + 15, width_button_location.y, width_button_location.x + 65, width_button_location.y + 25, 0x000000, true);
	//DrawBoxAA(width_button_location.x + 15, width_button_location.y, width_button_location.x + 65, width_button_location.y + 25, 0xffffff, false);
	//DrawFormatStringF(width_button_location.x + 25, width_button_location.y + 5, 0xffffff, "%d", stage_width_num);

	////�X�e�[�W�T�C�Y�ύX�{�^��
	//if (current_leftbutton_flg == false)
	//{
	//	DrawBoxAA(width_button_location.x, width_button_location.y, width_button_location.x + 15, width_button_location.y + 25, 0x000000, true);
	//	DrawBoxAA(width_button_location.x, width_button_location.y, width_button_location.x + 15, width_button_location.y + 25, 0xffffff, false);
	//	DrawStringF(width_button_location.x + 5, width_button_location.y + 5, "<", 0xffffff);
	//}
	//else
	//{
	//	DrawBoxAA(width_button_location.x, width_button_location.y, width_button_location.x + 15, width_button_location.y + 25, 0xffffff, true);
	//	DrawBoxAA(width_button_location.x, width_button_location.y, width_button_location.x + 15, width_button_location.y + 25, 0x000000, false);
	//	DrawStringF(width_button_location.x + 5, width_button_location.y + 5, "<", 0x000000);
	//}
	//if (current_rightbutton_flg == false)
	//{
	//	DrawBoxAA(width_button_location.x + 65, width_button_location.y, width_button_location.x + 80, width_button_location.y + 25, 0x000000, true);
	//	DrawBoxAA(width_button_location.x + 65, width_button_location.y, width_button_location.x + 80, width_button_location.y + 25, 0xffffff, false);
	//	DrawStringF(width_button_location.x + 70, width_button_location.y + 5, ">", 0xffffff);
	//}
	//else
	//{
	//	DrawBoxAA(width_button_location.x + 65, width_button_location.y, width_button_location.x + 80, width_button_location.y + 25, 0xffffff, true);
	//	DrawBoxAA(width_button_location.x + 65, width_button_location.y, width_button_location.x + 80, width_button_location.y + 25, 0x000000, false);
	//	DrawStringF(width_button_location.x + 70, width_button_location.y + 5, ">", 0x000000);
	//}

	////�X�e�[�W�����ύX�p�\��
	//DrawStringF(height_button_location.x - 15, height_button_location.y - 30, "�X�e�[�W����", 0xffffff);

	////�X�e�[�W�̏c�̃u���b�N�����\�������G���A
	//DrawBoxAA(height_button_location.x, height_button_location.y, height_button_location.x + 65, height_button_location.y + 25, 0x000000, true);
	//DrawBoxAA(height_button_location.x, height_button_location.y, height_button_location.x + 65, height_button_location.y + 25, 0xffffff, false);
	//DrawFormatStringF(height_button_location.x + 25, height_button_location.y + 5, 0xffffff, "%d", stage_height_num);

	////�X�e�[�W�T�C�Y�ύX�{�^��
	//if (current_upbutton_flg == false)
	//{
	//	DrawBoxAA(height_button_location.x, height_button_location.y - 15, height_button_location.x + 65, height_button_location.y, 0x000000, true);
	//	DrawBoxAA(height_button_location.x, height_button_location.y - 15, height_button_location.x + 65, height_button_location.y, 0xffffff, false);
	//	DrawRotaStringF(height_button_location.x + 40, height_button_location.y - 10, 1, 1, 0, 0, 1.6f, 0xffffff, 0, 0, "<");
	//}
	//else
	//{
	//	DrawBoxAA(height_button_location.x, height_button_location.y - 15, height_button_location.x + 65, height_button_location.y, 0xffffff, true);
	//	DrawBoxAA(height_button_location.x, height_button_location.y - 15, height_button_location.x + 65, height_button_location.y, 0x000000, false);
	//	DrawRotaStringF(height_button_location.x + 40, height_button_location.y - 10, 1, 1, 0, 0, 1.6f, 0x000000, 0, 0, "<");
	//}
	////�X�e�[�W�T�C�Y�ύX�{�^��
	//if (current_downbutton_flg == false)
	//{
	//	DrawBoxAA(height_button_location.x, height_button_location.y + 25, height_button_location.x + 65, height_button_location.y + 40, 0x000000, true);
	//	DrawBoxAA(height_button_location.x, height_button_location.y + 25, height_button_location.x + 65, height_button_location.y + 40, 0xffffff, false);
	//	DrawRotaStringF(height_button_location.x + 25, height_button_location.y + 35, 1, 1, 0, 0, 4.7f, 0xffffff, 0, 0, "<");
	//}
	//else
	//{
	//	DrawBoxAA(height_button_location.x, height_button_location.y + 25, height_button_location.x + 65, height_button_location.y + 40, 0xffffff, true);
	//	DrawBoxAA(height_button_location.x, height_button_location.y + 25, height_button_location.x + 65, height_button_location.y + 40, 0x000000, false);
	//	DrawRotaStringF(height_button_location.x + 25, height_button_location.y + 35, 1, 1, 0, 0, 4.7f, 0x000000, 0, 0, "<");
	//}

	//SetFontSize(old_size);
}

void Edit::LoadStage(int stage) 
{
	FILE* fp;
	std::string  fname;
	std::string fpassCoupling = "../../Resource/StageData/";
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
	//sprintf_s(fpass, "%s%s", &fpassCoupling, &fname);
	fpass = fpassCoupling + fname;

	fopen_s(&fp, fpass.c_str(), "r"); // ファイルを開く。失敗するとNULLを返す。
	if (fp == NULL) {
		DrawFormatString(50, 50, 0xff0000, "%s file not open!", fname);
	}
	else {
		DrawFormatString(50, 50, 0xffffff, "%s file opened!", fname);

	};

	fclose(fp); // ファイルを閉じる
}
