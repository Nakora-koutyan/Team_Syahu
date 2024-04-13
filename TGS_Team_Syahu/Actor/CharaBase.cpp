#include "CharaBase.h"

CharaBase::CharaBase()
{
	vector = { 0.f,0.f };
	direction = { 0.f,0.f };

	abilityType = Ability::Empty;

	framCount = 0;

	hp = 100.f;
	damage = 10.f;

	isAir = false;
	isHit = false;
	isShow = false;
	isAttack = false;
}

CharaBase::~CharaBase()
{

}

void CharaBase::DamageInterval(const int interval)
{
	framCount++;

	//当たっているなら
	if (isHit)
	{
		//intervalの時間無敵
		if (framCount % interval == 0)
		{
			//無敵解除
			isHit = false;
		}
	}
}
