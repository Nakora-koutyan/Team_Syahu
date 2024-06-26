#include "EnemyBase.h"
#include "../../../ResourceManager/ResourceManager.h"

EnemyBase::EnemyBase() :isClash(false), statusChangeTime(0), attackWaitingTime(0), noMove(false),patrolCounter(0.f), 
enemyStatus{},attackRange{}, attackCenser{0},isBlink(false),blinkCounter(0),enemyAlpha(255),isFind(false),
signToAttack(false),isChangeDamageAnim(false),damageAnimCount(0)
{
	objectType = ObjectType::Enemy;
	enemyType = EnemyType::None;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
}

void EnemyBase::Finalize()
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
	CharaBase* chara = static_cast<CharaBase*>(target);

	if (damage > 0 && GetEnemyStatus()!= EnemyStatus::Death)
	{
		if (!isKnockBack && !isHit && objectType != chara->GetObjectType())
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
	}

	//すでに当たってないならかつ同じオブジェクトじゃないなら
	if (GetEnemyStatus() != EnemyStatus::Death && (!isHit && objectType != chara->GetObjectType()) 
		|| chara->GetIsKnockBack())
	{
		isHit = true;
		if (chara->GetIsKnockBack())
		{
			chara->SetIsKnockBack(false);
		}

		if (hp > 0)
		{
			ResourceManager::PlaySE("damage", FALSE);

			hp -= damage;
			//ダメージ処理に遷移する
			enemyStatus = EnemyStatus::Damage;
		}
	}


	if (hp < 0)
	{
		hp = 0;
	}

	//if (isKnockBack && !chara->GetIsKnockBack() && chara->GetObjectType() == ObjectType::Enemy)
	//{
	//	if (CollisionCheck(chara))
	//	{
	//		chara->Hit(this, this->damage);
	//	}
	//}

	//中心の距離
	float disX = chara->GetCenterLocation().x - GetCenterLocation().x;

	//2点間の長さ
	float length = (GetArea().width / 2) + (chara->GetArea().width / 2);

	if (chara->GetObjectType() == ObjectType::Player)
	{
		const Player* player = static_cast<const Player*>(chara);
		if (chara->GetIsAttack() && player->GetIsEquipment() && 
			player->GetStock(player->GetStockCount()) == Weapon::Rapier && 
			player->GetActionState() == Action::WeaponAttack)
		{
			length += RAPIER_LENGTH;
		}
	}

	if (GetEnemyStatus() != EnemyStatus::Death && (abs(disX) < length) && !chara->GetIsAttack())
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