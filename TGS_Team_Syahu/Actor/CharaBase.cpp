#include "CharaBase.h"

CharaBase::CharaBase()
{
	vector = { 0.f,0.f };

	hp = 100.f;
	damage = 5.f;

	isAir = false;
	isHit = false;
}

CharaBase::~CharaBase()
{

}