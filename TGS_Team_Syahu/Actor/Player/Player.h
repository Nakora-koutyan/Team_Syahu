#pragma once
#include"../CharaBase.h"
#include"Weapon/NormalWeapon.h"

#define PLAYER_MOVE_SPEED		3.f				//�v���C���[�̈ړ����x
#define PLAYER_MAX_MOVE_SPEED	9.f				//�v���C���[�̍ō��ړ����x
#define PLAYER_DAMAGE_INTERVAL	FPS * 1			//�_���[�W�󂯂��Ƃ��ɍēx�_���[�W���󂯂�܂ł̎���
#define PLAYER_DAMAGE_CUT		1.f - 0.25f		//�K�[�h�������̃_���[�W�J�b�g��
#define PLAYER_PARRY_FLAME		10				//�p���B�̗P�\�t���[��

class Player :public CharaBase
{
private:
	Ability weaponSlot1;		//����X���b�g1
	Ability weaponSlot2;		//����X���b�g2
	NormalWeapon* normalWeapon;	//�ʏ�U��

	int framCount;				//�t���[���J�E���g
	int damageFramCount;		//�_���[�W�p�̃J�E���g
	int parryFram;				//�p���B�p�̃J�E���g

	float damageInterval;		//�_���[�W�̃C���^�[�o��

	bool isGuard;				//�K�[�h���Ă���H
	bool parryFlg;				//�p���B�̃t���O

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

