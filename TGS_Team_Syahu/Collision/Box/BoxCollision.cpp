#include"BoxCollision.h"
#include"../Sphere/SphereCollision.h"
#include"../Line/LineCollision.h"

BoxCollision::BoxCollision()
{
	area.width = 0.f;
	area.height = 0.f;

	collisionType = CollisionType::Box;
	objectType = ObjectType::Object;
}

BoxCollision::~BoxCollision()
{

}

bool BoxCollision::HitBox(const ObjectBase* object) const
{
	const BoxCollision* box = static_cast<const BoxCollision*>(object);

	bool ret = false;		//返り値

	float myX[2] = {};
	float myY[2] = {};

	float subX[2] = {};
	float subY[2] = {};

	myX[0] = location.x;
	myY[0] = location.y;
	myX[1] = myX[0] + area.width;
	myY[1] = myY[0] + area.height;

	subX[0] = box->GetLocation().x;
	subY[0] = box->GetLocation().y;
	subX[1] = subX[0] + box->GetArea().width;
	subY[1] = subY[0] + box->GetArea().height;

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

bool BoxCollision::HitSphere(const ObjectBase* object) const
{
	const SphereCollision* sphere = static_cast<const SphereCollision*>(object);

	bool ret = false;		//返り値

	Vector2D min = location;
	Vector2D max = {};
	max.x = location.x + area.width;
	max.y = location.y + area.height;

	float sphereX = sphere->GetLocation().x;
	float sphereY = sphere->GetLocation().y;
	float sphereR = sphere->GetRadius();

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

bool BoxCollision::HitLine(const ObjectBase* object) const
{
	const LineCollision* line = static_cast<const LineCollision*>(object);

	bool ret = false;		//返り値

	LineCollision segment[4] = {};

	Vector2D min = location;
	Vector2D max = {};
	max.x = location.x + area.width;
	max.y = location.y + area.height;
	Area area = {};
	area.width = this->area.width;
	area.height = this->area.height;

	//上
	segment[0].SetLocation(min);
	segment[0].SetDirectionVector({ area.width,0.f });

	//左
	segment[1].SetLocation(min);
	segment[1].SetDirectionVector({ 0.f,area.height });

	//右
	segment[2].SetLocation({ max.x,min.y });
	segment[2].SetDirectionVector({ 0.f,area.height });

	//下
	segment[3].SetLocation({ min.x,max.y });
	segment[3].SetDirectionVector({ area.width,0.f });

	for (int i = 0; i < 3; i++)
	{
		//四辺のいずれかと交差していたら
		if (line->HitLine(&segment[i]))
		{
			ret = true;
			break;
		}
	}

	return ret;
}