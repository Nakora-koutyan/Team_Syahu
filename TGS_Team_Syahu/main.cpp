#include"SceneManager/SceneManager.h"
#include"Scene/GameMain/GameMainScene.h"
#include"Utility/common.h"

/************************************************
* �v���O�����̊J�n
*************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	double nextTime = GetNowCount();	//�V�X�e�����Ԃ̎擾

	//�^�C�g��
	SetMainWindowText("");

	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);	

	//��ɃA�N�e�B�u��Ԃɂ���
	//SetAlwaysRunFlag(TRUE);	

	//��ʃT�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	

	//DX���C�u�����̏���������
	if (DxLib_Init() == -1)return -1;	

	//�`���𗠂ɂ���
	SetDrawScreen(DX_SCREEN_BACK);		

	//�w�i�̐F��D�F�ɂ���
	SetBackgroundColor(128, 128, 128);

	//�}�E�X�J�[�\�����ʒ����ɐݒ�
	SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//�}�E�X�J�[�\����\�����Ȃ�
	SetMouseDispFlag(FALSE);

	try
	{
		SceenManager* sceenManager = new SceenManager(dynamic_cast<SceneBase*>(new GameMainScene()));

		//�Q�[�����[�v
		while ((ProcessMessage() == 0) &&
			sceenManager->Update() != nullptr &&
			!(CheckHitKey(KEY_INPUT_ESCAPE)))

		{	//��ʂ̏�����
			ClearDrawScreen();

			KeyInput::Update();

			PadInput::Update();

			sceenManager->Draw();


			nextTime += 1.0 / 60.0 * 1000.0;		//�t���[�����[�g�̐ݒ�{�~���P�ʂɍ��킹��

			if (nextTime > GetNowCount())
			{
				WaitTimer((int)nextTime - GetNowCount());
			}
			else
			{
				nextTime = GetNowCount();
			}

			//����ʂ̓�e��\��ʂɔ��f
			ScreenFlip();
		}
	}
	catch (const char* errorLog)
	{
		OutputDebugString(_T(errorLog));

		return -1;
	}

	//DX���C�u�����g�p�̏I������
	DxLib_End();		

	return 0;
}