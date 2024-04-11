#pragma once
#include"../CharaBase.h"

#define PLAYER_MOVE_SPEED		5.f			//�v���C���[�̈ړ����x
#define PLAYER_MAX_MOVE_SPEED	15.f		//�v���C���[�̍ō��ړ����x

class Player :public CharaBase
{
private:

public:
	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//�X�V
	void Update(GameMainScene* object)override;

	//�`��
	void Draw()const override;

private:
	//�ړ�
	void Movement();

	//�A�N�V����
	void Action();

};

