#include "CharaBase.h"

CharaBase::CharaBase()
{
	vector = { 0.f,0.f };
	direction = { 0.f,0.f };

	abilityType = Ability::Empty;

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