#include "EnemyBase.h"

EnemyBase::EnemyBase() :isClash(false), statusChangeTime(0), attackWaitingTime(0), noMove(false),patrolCounter(0.f), enemyStatus{},
findMark(NULL),angryMark(NULL),attackRange{}, attackCenser{0}, colorRed(NULL), colorGreen(NULL), colorBlue(NULL),
markStatus(NULL),isBlink(false),blinkCounter(0),enemyAlpha(255),isFind(false)
{
	objectType = ObjectType::Enemy;
	enemyType = EnemyType::None;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw(Player* player)
{
}

void EnemyBase::Hit(ObjectBase* target, const float damage)
{
	const Player* player = static_cast<const Player*>(target);

	if (!isKnockBack && !isHit)
	{
		isKnockBack = true;
		if (GetCenterLocation().x < player->GetCenterLocation().x)
		{
			knockBackDirection = -1;
		}
		else
		{
			knockBackDirection = 1;
		}
	}

	//すでに当たってないならかつ同じオブジェクトじゃないなら
	if (!isHit && objectType != player->GetObjectType())
	{
		isHit = true;

		if (hp > 0)
		{
			hp -= damage;
		}
		else
		{
			deathFlg = true;
		}
	}

	//中心の距離
	float disX = player->GetCenterLocation().x - GetCenterLocation().x;

	//2点間の長さ
	float length = (GetArea().width / 2) + (player->GetArea().width / 2);

	if (player->GetIsAttack() && player->GetIsEquipment() && player->GetStock(player->GetStockCount()) == Weapon::Rapier)
	{
		length += RAPIER_LENGTH;
	}

	if (abs(disX) < length)
	{
		float dif = length - abs(disX);

		//左
		if (GetCenterLocation().x < player->GetCenterLocation().x)
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

//画面端を越えない
void EnemyBase::DontCrossBorder()
{
	//左端を超えない
	if (GetMinLocation().x < 0.f)
	{
		location.x = 0.f;
		move.x = 0.f;
	}
	//右端を超えない
	else if (GetMaxLocation().x > WORLD_WIDTH)
	{
		location.x = WORLD_WIDTH - area.width;
		move.x = 0.f;
	}
}
