#include"CollisionBase.h"
#include"Box/BoxCollision.h"
#include"Sphere/SphereCollision.h"

CollisionBase::CollisionBase()
{
	location = { 0.f,0.f };
	screenLocation = { 0.f,0.f };

	collisionType = CollisionType::Empty;
}

CollisionBase::~CollisionBase()
{

}

bool CollisionBase::HitCheck(const CollisionBase* collision) const
{
	bool ret = false;

	//�R���W�����̎�ނ̎擾
	CollisionType type = collision->GetType();

	switch (type)
	{
	//��
	case CollisionType::Empty:
		ret = false;
		break;

	//�{�b�N�X
	case CollisionType::Box:
		ret = HitBox(static_cast<const BoxCollision*>(collision));
		break;

	//�X�t�B�A
	case CollisionType::Sphere:
		ret = HitSphere(static_cast<const SphereCollision*>(collision));

	//�f�t�H���g
	default:
		ret = false;
		break;
	}

	return ret;
}

float CollisionBase::MakeHypotenuse(const float x1, const float y1, const float x2, const float y2) const
{
	float dX = x2 - x1;
	float dY = y2 - y1;

	return (dX * dX) + (dY * dY);
}