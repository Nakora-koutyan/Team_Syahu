#define _USE_MATH_DEFINES
#include<math.h>
#include"LineCollision.h"
#include"../Box/BoxCollision.h"
#include"../Sphere/SphereCollision.h"

LineCollision::LineCollision()
{
	directionVector = { 0.f,0.f };

	collisionType = CollisionType::Line;
}

LineCollision::~LineCollision()
{

}

bool LineCollision::HitLine(const LineCollision* collision) const
{
	bool ret = true;		//返り値

	Vector2D argLoc = collision->GetLocation();
	Vector2D argVec = collision->GetDirectionVector();

	//ベクトルを求める
	Vector2D v = Vec2DSub(argLoc, this->location);

	float crossVec = Vec2Cross(this->directionVector, argVec);
	if (crossVec == 0.f)
	{
		//平行状態
		ret = false;
	}

	float crossDirectV1 = Vec2Cross(v, this->directionVector);
	float crossDirectV2 = Vec2Cross(v, argVec);

	//内分比
	float t1 = crossDirectV2 / crossVec;
	float t2 = crossDirectV1 / crossVec;

	//誤差許容値
	const float eps = 0.00001f;

	if (t1 + eps < 0 || t1 - eps>1 || t2 + eps < 0 || t2 - eps>1)
	{
		//交差していない
		ret = false;
	}

	return ret;
}

bool LineCollision::HitBox(const BoxCollision* collision) const
{
	bool ret = false;		//返り値

	Vector2D min = collision->GetMinLocation();
	Vector2D max = collision->GetMaxLocation();
	Area area = collision->GetArea();

	LineCollision segment[4] = {};

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

	for (int i = 0; i < 4; i++)
	{
		//四辺のいずれかと交差していたら
		if (HitLine(&segment[i]))
		{
			ret = true;
			break;
		}
	}

	return ret;
}

bool LineCollision::HitSphere(const SphereCollision* collision) const
{
	bool ret = false;		//返り値

	Vector2D sphereLoc = collision->GetLocation();
	float sphereR = collision->GetRadius();

	//始点から中心点へのベクトル
	Vector2D vec1 = Vec2DSub(sphereLoc, location);
	//始点から中心点へのベクトルの大きさ
	float magnitudeVec1 = sqrtf(vec1.x * vec1.x + vec1.y * vec1.y);

	//終点から中心点へのベクトル
	Vector2D vec2 = Vec2DSub(sphereLoc, Vec2DAdd(location, directionVector));
	//終点から中心点へのベクトルの大きさ
	float magnitudeVec2 = sqrtf(vec2.x * vec2.x + vec2.y * vec2.y);

	//線分のベクトルの大きさ
	float magnitudeSegment = sqrtf(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
	//線分のベクトルの正規化
	Vector2D identity = {};
	identity.x = directionVector.x / magnitudeSegment;
	identity.y = directionVector.y / magnitudeSegment;

	//中心点と線分の距離
	float length = identity.x * vec1.y - vec1.x * identity.y;

	//中心点から線分までの距離が半径以下なら
	if (length <= sphereR)
	{
		//鈍角なら
		if (Vec2Dot(vec1, directionVector) * Vec2Dot(vec2, directionVector) <= 0)
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
