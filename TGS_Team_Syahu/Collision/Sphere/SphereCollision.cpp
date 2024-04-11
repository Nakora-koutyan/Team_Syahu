#include"SphereCollision.h"
#include"../Box/BoxCollision.h"

SphereCollision::SphereCollision()
{
	radius = 0.f;

	collisionType = CollisionType::Sphere;
}

SphereCollision::~SphereCollision()
{

}

bool SphereCollision::HitSphere(const SphereCollision* collision) const
{
	bool ret = false;		//返り値

	float dX = location.x - collision->GetLocation().x;
	float dY = location.y - collision->GetLocation().y;

	//中心点の距離
	float distance = dX * dX + dY * dY;

	float dR = radius + collision->GetRadius();

	//2円の半径
	float length = dR * dR;

	//双方の中心からの距離が大きいか小さいか
	if (distance < length)
	{
		ret = true;
	}

	return ret;
}

bool SphereCollision::HitBox(const BoxCollision* collision) const
{

	bool ret = false;		//返り値

	Vector2D min = collision->GetMinLocation();
	Vector2D max = collision->GetMaxLocation();

	float sphereX = location.x;
	float sphereY = location.y;
	float sphereR = radius;

	// 四角形の四辺に対して円の半径分だけ足したとき円が重なっていたら
	if ((sphereX > min.x - sphereR) &&
		(sphereX < max.x + sphereR) &&
		(sphereY > min.y - sphereR) &&
		(sphereY < max.y + sphereR))
	{
		ret = true;
		float length = sphereR * sphereR;

		//左
		if (sphereR < min.x)
		{
			//左上
			if (sphereY < min.y)
			{
				if (MakeHypotenuse(min.x, min.y, sphereX, sphereY) >= length)
				{
					ret = false;
				}
			}
			else
			{
				//左下
				if (sphereY > max.y)
				{
					if (MakeHypotenuse(min.x, max.y, sphereX, sphereY) >= length)
					{
						ret = false;
					}
				}
			}
		}
		else
		{
			//右
			if (sphereX > max.x)
			{
				//右上
				if (sphereY < min.x)
				{
					if (MakeHypotenuse(max.x, min.y, sphereX, sphereY) >= length)
					{
						ret = false;
					}
				}
				else
				{
					//右下
					if (sphereY > max.y)
					{
						if (MakeHypotenuse(max.x, max.y, sphereX, sphereY) >= length)
						{
							ret = false;
						}
					}
				}
			}
		}
	}

	return ret;
}
