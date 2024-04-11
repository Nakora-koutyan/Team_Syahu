#pragma once
#include"../Collision/Box/BoxCollision.h"

#define NEED_STICK_RATIO	0.2f		//�K�v�ȃX�e�B�b�N�̌X������
#define MAX_SPEED			10.f		//�ō����x	
#define GRAVITY				0.8f		//�������x
#define JUMP_POWER			15.f		//�W�����v��

enum Ebility
{

};

class GameMainScene;

class CharaBase :public BoxCollision
{
protected:
	Vector2D vector;			//�ړ���

	float hp;					//HP
	float damage;				//�_���[�W

	bool isAir;					//�󒆁H
	bool isHit;					//���������H

public:
	//�R���X�g���N�^
	CharaBase();

	//�f�X�g���N�^
	~CharaBase();

	//�X�V
	virtual void Update(GameMainScene* object) = 0;

	//�`��
	virtual void Draw()const = 0;

	//HP���擾����
	float GetHp()const { return hp; }

	//�_���[�W���擾����
	float GetDamage()const { return damage; }
	
};
