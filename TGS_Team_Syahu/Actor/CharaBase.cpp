#include "CharaBase.h"

CharaBase::CharaBase()
{
	vector = { 0.f,0.f };
	direction = { 0.f,0.f };

	abilityType = Ability::Empty;

	framCount = 0;
	knockBackCount = 0;

	hp = 100.f;
	damage = 10.f;

	isAir = false;
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
