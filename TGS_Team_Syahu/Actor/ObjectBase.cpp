#include"ObjectBase.h"
#include"../Collision/Box/BoxCollision.h"
#include"../Collision/Sphere/SphereCollision.h"
#include"../Collision/Line/LineCollision.h"

ObjectBase::ObjectBase()
{
	location.x = 0.f;
	location.y = 0.f;
	screenLocation.x = 0.f;
	screenLocation.y = 0.f;

	collisionType = CollisionType::None;
	objectType = ObjectType::None;

	damage = 0.f;

	isShow = false;
}

ObjectBase::~ObjectBase()
{

}

bool ObjectBase::CollisionCheck(const ObjectBase* object) const
{
	bool ret = false;

	//コリジョンの種類の取得
	CollisionType type = object->GetCollisionType();

	switch (type)
	{
	//空
	case CollisionType::None:
		ret = false;
		break;

	//四角
	case CollisionType::Box:
		ret = HitBox(static_cast<const BoxCollision*>(object));
		break;

	//円
	case CollisionType::Sphere:
		ret = HitSphere(static_cast<const SphereCollision*>(object));
		break;

	//線
	case CollisionType::Line:
		ret = HitLine(static_cast<const LineCollision*>(object));
		break;

	//デフォルト
	default:
		ret = false;
		break;
	}

	return ret;
}

float ObjectBase::MakeHypotenuse(const float x1, const float y1, const float x2, const float y2) const
{
	float dX = x2 - x1;
	float dY = y2 - y1;

	return (dX * dX) + (dY * dY);
}