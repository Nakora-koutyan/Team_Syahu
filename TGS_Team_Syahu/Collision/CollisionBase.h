#pragma once
#include"DxLib.h"
#include"../Utility/Vector2D.h"
#include"../Utility/Area.h"

enum CollisionType
{
	Empty = 0,		//��
	box				//�{�b�N�X
};

class BoxCollision;

class CollisionBase
{
protected:
	Vector2D location;			//���W
	Vector2D screenLocation;	//�X�N���[�����W

	CollisionType type;			//�R���W�����̎��
public:
	//�R���X�g���N�^
	CollisionBase();

	//�f�X�g���N�^
	~CollisionBase();

	//�����蔻��
	bool HitCheck(const CollisionBase* collision)const;

	//���W���擾����
	Vector2D GetLocation()const { return location; }

	//�R���W�����̎�ނ��擾����
	CollisionType GetType()const { return type; }
	
protected:
	//�{�b�N�X�Ƃ̓����蔻��
	virtual bool HitBox(const BoxCollision* obb)const = 0;

};

