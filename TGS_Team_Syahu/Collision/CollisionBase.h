#pragma once
#include"DxLib.h"
#include"../Utility/Vector2D.h"
#include"../Utility/Area.h"

enum class CollisionType
{
	Empty = 0,		//��
	Box,			//�l�p
	Sphere			//�~
};

class BoxCollision;
class SphereCollision;

class CollisionBase
{
protected:
	Vector2D location;			//���[���h���W
	Vector2D screenLocation;	//�X�N���[�����W

	CollisionType collisionType;			//�R���W�����̎��
public:
	//�R���X�g���N�^
	CollisionBase();

	//�f�X�g���N�^
	~CollisionBase();

	//�����蔻��
	bool HitCheck(const CollisionBase* collision)const;

	//�l�p�Ɖ~�̓����蔻��ɕK�v�ȎΕӂ��쐬����
	float MakeHypotenuse(const float x1, const float y1, const float x2, const float y2)const;

public:
	//���[���h���W���擾����
	Vector2D GetLocation()const { return location; }

	//���[���h���W��ݒ�
	void SetLocation(const Vector2D location) { this->location = location; }

	//�X�N���[�����W���擾����
	Vector2D GetScreenLocation()const { return screenLocation; }

	//�X�N���[�����W��ݒ�
	void SetScreenLocation(const Vector2D location) { this->screenLocation = location; }

	//�R���W�����̎�ނ��擾����
	CollisionType GetType()const { return collisionType; }
	
protected:
	//�l�p�Ƃ̓����蔻��
	virtual bool HitBox(const BoxCollision* collision)const = 0;

	//�~�Ƃ̓����蔻��
	virtual bool HitSphere(const SphereCollision* collision)const = 0;

};

