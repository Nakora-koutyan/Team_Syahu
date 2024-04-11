#pragma once
#include"../CharaBase.h"

#define PLAYER_MOVE_SPEED		3.f				//�v���C���[�̈ړ����x
#define PLAYER_MAX_MOVE_SPEED	9.f				//�v���C���[�̍ō��ړ����x
#define PLAYER_DAMAGE_INTERVAL	60				//�_���[�W�󂯂��Ƃ��ɍēx�_���[�W���󂯂�܂ł̎���
#define PLAYER_DAMAGE_CUT		1.f - 0.25f		//�K�[�h�������̃_���[�W�J�b�g��
#define PLAYER_PARRY_FLAME		10				//�p���B�̗P�\�t���[��

class Player :public CharaBase
{
private:
	int framCount;			//�t���[���J�E���g
	int damageFramCount;	//�_���[�W�p�̃J�E���g

	float damageInterval;	//�_���[�W�̃C���^�[�o��

	bool isGuard;			//�K�[�h���Ă���H

public:
	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//�X�V
	void Update(GameMainScene* object)override;

	//�`��
	void Draw()const override;

	//�����蔻��̏���
	void Hit(GameMainScene* object);

private:
	//�ړ�
	void Movement();

	//�A�N�V����
	void Action();

};

