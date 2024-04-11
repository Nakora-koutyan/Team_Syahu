#pragma once
#include"../CharaBase.h"

#define MAX_ENEMY_SPEED -1.5
#define ATTACK_FORM_RANGE_X 150
#define ATTACK_FORM_RANGE_Y 50

class NormalEnemy :public CharaBase
{
private:
	int enemy_color;

	int usual_color;
	int damage_color;
	int attack_color;

public:
	//�R���X�g���N�^
	NormalEnemy();

	//�f�X�g���N�^
	~NormalEnemy();

	//�������֐�
	void Initialize();

	//�X�V
	void Update(GameMainScene* object)override;

	//�`��
	void Draw()const override;

	//�ړ�����
	void Movement();

	//�{�b�N�X�̒��S�l���擾
	float BoxCenter();
};

