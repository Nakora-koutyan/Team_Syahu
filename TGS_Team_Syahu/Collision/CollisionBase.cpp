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
	//コリジョンの種類の取得
	CollisionType collisionType = collision->GetType();

	switch (collisionType)
	{
	//空
	case Empty:
		ret = false;
		break;

	//有向境界ボックス
	case box:
		ret = HitBox(static_cast<const BoxCollision*>(collision));
		break;

	//デフォルト
	default:
		ret = false;
		break;
	}

	return ret;
}
