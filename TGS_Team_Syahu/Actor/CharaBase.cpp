#include "CharaBase.h"

CharaBase::CharaBase()
{
	move.x = 0.f;
	move.y = 0.f;
	direction.x = 0.f;
	direction.y = 0.f;

	weaponType = Weapon::Empty;

	framCount = 0;
	knockBackCount = 0;

	hp = 100.f;
	damage = 10.f;

	isAir = false;
	isMove = false;
	isHit = false;
	isShow = false;
	isAttack = false;
	isKnockBack = false;
}

CharaBase::~CharaBase()
{

}

void CharaBase::DamageInterval(const int interval)
{
	//当たっているなら
	if (isHit)
	{	
		framCount++;

		//intervalの時間無敵
		if (framCount % interval == 0)
		{
			//無敵解除
			isHit = false;
		}
	}
}

void CharaBase::KnockBack(const double time)
{
	if (isKnockBack)
	{
		knockBackCount++;
		location.x += move.x;
		if (knockBackCount > time)
		{
			isKnockBack = false;
			knockBackCount = 0;
			move.x = 0.f;
			move.y = 0.f;
		}
	}
}
