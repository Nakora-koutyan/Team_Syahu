#include"SphereCollision.h"
#include"../Box/BoxCollision.h"
#include"../Line/LineCollision.h"

SphereCollision::SphereCollision()
{
	radius = 0.f;

	collisionType = CollisionType::Sphere;
	objectType = ObjectType::Object;
}

SphereCollision::~SphereCollision()
{

}

bool SphereCollision::HitSphere(const ObjectBase* object) const
{
	const SphereCollision* sphere = static_cast<const SphereCollision*>(object);

	bool ret = false;		//返り値

	float dX = location.x - sphere->GetLocation().x;
	float dY = location.y - sphere->GetLocation().y;

	//中心点の距離
	float distance = dX * dX + dY * dY;

	float dR = radius + sphere->GetRadius();

	//2円の半径
	float length = dR * dR;

	//2円の半径が中心点の距離より大きいなら
	if (distance < length)
	{
		ret = true;
	}

	return ret;
}

bool SphereCollision::HitBox(const ObjectBase* object) const
{
	const BoxCollision* box = static_cast<const BoxCollision*>(object);

	bool ret = false;		//返り値

	Vector2D min = box->GetMinLocation();
	Vector2D max = box->GetMaxLocation();

	float sphereX = location.x;
	float sphereY = location.y;
	float sphereR = radius;

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
				//右下
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

bool SphereCollision::HitLine(const ObjectBase* object) const
{
	const LineCollision* line = static_cast<const LineCollision*>(object);

	bool ret = false;		//返り値

	Vector2D sphereLoc = location;
	float sphereR = radius;

	Vector2D lineLoc = line->GetLocation();
	Vector2D lineVec = line->GetDirectionVector();

	//始点から中心点へのベクトル
	Vector2D vec1 = Vec2DSub(sphereLoc, lineLoc);
	//始点から中心点へのベクトルの大きさ
	float magnitudeVec1 = sqrtf(vec1.x * vec1.x + vec1.y * vec1.y);

	//終点から中心点へのベクトル
	Vector2D vec2 = Vec2DSub(sphereLoc, Vec2DAdd(lineLoc, lineVec));
	//終点から中心点へのベクトルの大きさ
	float magnitudeVec2 = sqrtf(vec2.x * vec2.x + vec2.y * vec2.y);

	//線分のベクトルの大きさ
	float magnitudeSegment = sqrtf(lineVec.x * lineVec.x + lineVec.y * lineVec.y);
	//線分のベクトルの正規化
	Vector2D identity = {};
	identity.x = lineVec.x / magnitudeSegment;
	identity.y = lineVec.y / magnitudeSegment;

	//中心点と線分の距離
	float length = identity.x * vec1.y - vec1.x * identity.y;

	//中心点から線分までの距離が半径以下なら
	if (length <= sphereR)
	{
		//鈍角なら
		if (Vec2Dot(vec1, lineVec) * Vec2Dot(vec2, lineVec) <= 0)
		{
			ret = true;
		}
		else
		{
			//始点から中心点へのベクトルや終点から中心点へのベクトルの長さが半径よりも短いなら
			if (sphereR > magnitudeVec1 || sphereR > magnitudeVec2)
			{
				ret = true;
			}
		}
	}

	return ret;
}
