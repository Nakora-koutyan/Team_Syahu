#include"BoxCollision.h"
#include"../Sphere/SphereCollision.h"

BoxCollision::BoxCollision()
{
	area = { 0.f,0.f };

	collisionType = CollisionType::Box;
}

BoxCollision::~BoxCollision()
{

}

bool BoxCollision::HitBox(const BoxCollision* collision) const
{
	bool ret = false;		//返り値

	//自分の当たり判定の範囲
	float myX[2] = {};
	float myY[2] = {};

	//相手の当たり判定の範囲
	float subX[2] = {};
	float subY[2] = {};

	//自分の当たり判定の範囲の計算
	myX[0] = location.x;
	myY[0] = location.y;
	myX[1] = myX[0] + area.width;
	myY[1] = myY[0] + area.height;

	//相手の当たり判定の範囲の計算
	subX[0] = collision->GetLocation().x;
	subY[0] = collision->GetLocation().y;
	subX[1] = subX[0] + collision->GetArea().width;
	subY[1] = subY[0] + collision->GetArea().height;

	//双方の四辺が当たっているか
	if ((myX[0] < subX[1]) &&
		(subX[0] < myX[1]) &&
		(myY[0] < subY[1]) &&
		(subY[0] < myY[1])) 
	{
		ret = true;
	}
	return ret;
}

bool BoxCollision::HitSphere(const SphereCollision* collision) const
{
	bool ret = false;		//返り値

	Vector2D min = location;
	Vector2D max = { location.x + area.width,location.y + area.height };

	float sphereX = collision->GetLocation().x;
	float sphereY = collision->GetLocation().y;
	float sphereR = collision->GetRadius();

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
