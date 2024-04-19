#include"CollisionBase.h"
#include"Box/BoxCollision.h"
#include"Sphere/SphereCollision.h"
#include"Line/LineCollision.h"

CollisionBase::CollisionBase()
{
	location.x = 0.f;
	location.y = 0.f;
	screenLocation.x = 0.f;
	screenLocation.y = 0.f;

	collisionType = CollisionType::Empty;
}

CollisionBase::~CollisionBase()
{

}

bool CollisionBase::CollisionCheck(const CollisionBase* collision) const
{
	bool ret = false;

	//コリジョンの種類の取得
	CollisionType type = collision->GetType();

	switch (type)
	{
	//空
	case CollisionType::Empty:
		ret = false;
		break;

	//四角
	case CollisionType::Box:
		ret = HitBox(static_cast<const BoxCollision*>(collision));
		break;

	//円
	case CollisionType::Sphere:
		ret = HitSphere(static_cast<const SphereCollision*>(collision));
		break;

	//線
	case CollisionType::Line:
		ret = HitLine(static_cast<const LineCollision*>(collision));
		break;

	//デフォルト
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