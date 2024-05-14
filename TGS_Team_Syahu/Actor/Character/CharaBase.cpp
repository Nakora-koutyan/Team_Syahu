#include "CharaBase.h"

CharaBase::CharaBase()
{
	move.x = 0.f;
	move.y = 0.f;
	direction.x = 0.f;
	direction.y = 0.f;

	weaponType = Weapon::None;
	objectType = ObjectType::Object;

	knockBackDirection = 0;

	framCount = 0;
	knockBackCount = 0;
	alphaBlend = 255;

	hp = 100.f;
	damage = 10.f;

	isAir = false;
	isJump = false;
	isMove = false;
	isHit = false;
	isShow = false;
	isAttack = false;
	isKnockBack = false;
	imageInversionFlg = false;
	isInvincible = false;
}

CharaBase::~CharaBase()
{

}

void CharaBase::Initialize()
{

}

void CharaBase::Finalize()
{

}

void CharaBase::Hit(ObjectBase* object, const float damage)
{
	const CharaBase* chara = static_cast<const CharaBase*>(object);

	if (!isKnockBack && !isHit && !isInvincible && !chara->GetIsInvincible())
	{
		isKnockBack = true;
		if (GetCenterLocation().x < chara->GetCenterLocation().x)
		{
			knockBackDirection = -1;
		}
		else
		{
			knockBackDirection = 1;
		}
	}

	//すでに当たってないならかつ同じオブジェクトじゃないなら
	if (!isHit && !isInvincible && objectType != chara->GetObjectType())
	{
		isHit = true;

		if (hp > 0)hp -= damage;
	}

	//中心の距離
	float disX = chara->GetCenterLocation().x - GetCenterLocation().x;

	//2点間の長さ
	float length = (GetArea().width / 2) + (chara->GetArea().width / 2);

	if (abs(disX) < length && !isInvincible && !chara->GetIsInvincible())
	{
		float dif = length - abs(disX);

		//左
		if (GetCenterLocation().x < chara->GetCenterLocation().x)
		{
			SetLocationX(location.x - dif);
		}
		//右
		else
		{
			SetLocationX(location.x + dif);
		}
	}

}

void CharaBase::Landing(const float height)
{
	//地面を超えない
	if (GetMaxLocation().y > height)
	{
		location.y = height - area.height;
		move.y = 0.f;
		isAir = false;
		direction = { direction.x,0.f };
	}

	if (direction.y != 0.f)
	{
		isAir = true;
	}

}

void CharaBase::DamageInterval(const double interval)
{
	//当たっているなら
	if (isHit)
	{	
		framCount++;

		//intervalの時間無敵
		if (framCount % int(interval) == 0)
		{
			//無敵解除
			isHit = false;
		}
	}
}

void CharaBase::KnockBack(const CharaBase* chara, const double time, const float x)
{
	if (isKnockBack)
	{
		knockBackCount++;

		if (knockBackDirection < 0)
		{
			move.x = -x;
		}
		else
		{
			move.x = x;
		}

		location.x += move.x;
		if (knockBackCount > time)
		{
			isKnockBack = false;
			knockBackCount = 0;
			knockBackDirection = 0;
			move.x = 0.f;
			move.y = 0.f;
		}
	}
}
