#include "CollisionBase.h"
#include"Box/BoxCollision.h"

CollisionBase::CollisionBase()
{
	location = { 0.f,0.f };
	screenLocation = { 0.f,0.f };

	type = Empty;
}

CollisionBase::~CollisionBase()
{

}

bool CollisionBase::HitCheck(const CollisionBase* collision) const
{
	bool ret = false;
	//�R���W�����̎�ނ̎擾
	CollisionType collisionType = collision->GetType();

	switch (collisionType)
	{
	//��
	case Empty:
		ret = false;
		break;

	//�L�����E�{�b�N�X
	case box:
		ret = HitBox(static_cast<const BoxCollision*>(collision));
		break;

	//�f�t�H���g
	default:
		ret = false;
		break;
	}

	return ret;
}
