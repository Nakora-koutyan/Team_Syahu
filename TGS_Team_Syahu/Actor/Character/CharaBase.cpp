#include "CharaBase.h"

CharaBase::CharaBase()
{
	move.x = 0.f;
	move.y = 0.f;
	direction.x = 0.f;
	direction.y = 0.f;

	weaponType = Weapon::Empty;

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

	if (isHit)
	{
		if (GetCenterLocation().x < chara->GetCenterLocation().x)
		{
			knockBackDirection = -1;
		}
		else
		{
			knockBackDirection = 1;
		}
	}

	//すでに当たってないなら
	if (!isHit)
	{
		isHit = true;

		if (hp > 0)hp -= damage;
		isKnockBack = true;
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
