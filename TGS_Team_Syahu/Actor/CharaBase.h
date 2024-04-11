#pragma once
#include"../Collision/Box/BoxCollision.h"

#define NEED_STICK_RATIO	0.2f		//�K�v�ȃX�e�B�b�N�̌X������
#define MAX_SPEED			10.f		//�ō����x	
#define GRAVITY				0.8f		//�������x
#define JUMP_POWER			15.f		//�W�����v��

enum class Ability
{
	Empty = 0,			//��
	Slashing			//�a��
};

class GameMainScene;

class CharaBase :public BoxCollision
{
protected:
	Vector2D vector;			//�ړ���
	Vector2D direction;			//����

	Ability abilityType;		//�\�͂̎��

	float hp;					//HP
	float damage;				//�_���[�W

	bool isAir;					//�󒆁H
	bool isHit;					//���������H
	bool isShow;				//�\������H
	bool isAttack;				//�U������

public:
	//�R���X�g���N�^
	CharaBase();

	//�f�X�g���N�^
	~CharaBase();

	//�X�V
	virtual void Update(GameMainScene* object) = 0;

	//�`��
	virtual void Draw()const = 0;

	//HP���擾
	float GetHp()const { return hp; }

	//�_���[�W���擾
	float GetDamage()const { return damage; }

	//�U��������擾
	bool GetIsAttack()const { return isAttack; }

	//�U�������ݒ�
	void SetIsAttack(const bool flg) { isAttack = flg; }

	//�������擾
	Vector2D GetDirection()const { return direction; }

protected:
	//�\�͂̎�ނ��擾
	Ability GetAbilityType() { return abilityType; }
	
};
