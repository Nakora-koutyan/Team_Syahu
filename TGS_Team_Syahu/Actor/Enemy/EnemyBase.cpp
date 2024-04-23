#include "EnemyBase.h"

EnemyBase::EnemyBase():isChase(false),attackCoolTime(0),attackTime(0),noMove(false),isPatrol(true),
patrolCounter(0.f)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(Player* player)
{
}

void EnemyBase::Draw(Player* player)
{
}