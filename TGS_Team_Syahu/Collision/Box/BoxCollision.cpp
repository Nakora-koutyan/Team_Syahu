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

	float myX[2] = {};
	float myY[2] = {};

	float subX[2] = {};
	float subY[2] = {};

	myX[0] = location.x;
	myY[0] = location.y;
	myX[1] = myX[0] + area.width;
	myY[1] = myY[0] + area.height;

	subX[0] = collision->GetLocation().x;
	subY[0] = collision->GetLocation().y;
	subX[1] = subX[0] + collision->GetArea().width;
	subY[1] = subY[0] + collision->GetArea().height;

	//四辺に重なっていたら
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

	//円の座標が四辺の座標に半径を足した数より大きいまたは小さいなら
	if ((sphereX > min.x - sphereR) &&
		(sphereX < max.x + sphereR) &&
		(sphereY > min.y - sphereR) &&
		(sphereY < max.y + sphereR))
	{
		ret = true;
		float length = sphereR * sphereR;

		//右
		if (sphereR < min.x)
		{
			//右上
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
			//左
			if (sphereX > max.x)
			{
				//左上
				if (sphereY < min.x)
				{
					if (MakeHypotenuse(max.x, min.y, sphereX, sphereY) >= length)
					{
						ret = false;
					}
				}
				else
				{	
					//左下
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
