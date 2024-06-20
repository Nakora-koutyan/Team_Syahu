#include"CharaBase.h"
#include"../Actor/Camera/Camera.h"

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
	damage = 1.f;
	knockBackMove = 0.f;

	isAir = false;
	isJump = false;
	isMove = false;
	isHit = false;
	isShow = true;
	isAttack = false;
	isKnockBack = false;
	imageInversionFlg = false;
	deathFlg = false;
	invincibleFlg = false;
	hitBlockFlg = false;
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

void CharaBase::Update()
{

}

void CharaBase::Draw() const
{

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

void CharaBase::MovementUpdate()
{
	//重力
	Gravity();

	//座標に加算
	location.x += move.x;
	location.y += move.y;

	screenLocation = Camera::ConvertScreenPosition(location);
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

		if (isAir)
		{
			move.x /= 2;
		}

		location.x += move.x;
		if (knockBackCount > time)
		{
			isKnockBack = false;
			knockBackCount = 0;
			knockBackDirection = 0;
			knockBackMove = 0.f;
			move.x = 0.f;
			move.y = 0.f;
		}
	}
}

void CharaBase::Gravity()
{
	//重力
	move.y += GRAVITY;
}
