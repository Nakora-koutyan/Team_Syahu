#include "EnemyBase.h"

EnemyBase::EnemyBase():isClash(false),statusChangeTime(0),attackWaitingTime(0),noMove(false),isPatrol(true),
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