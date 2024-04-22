#include "EnemyBase.h"

EnemyBase::EnemyBase():isChase(false),attackCoolTime(0),attackTime(0),noMove(false)
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

void EnemyBase::EnemyPatrol(Player* player)
{
}

void EnemyBase::AttackRange()
{
}

void EnemyBase::ChaseRange()
{
}

void EnemyBase::ChaseToPlayer(Player* player)
{
}

void EnemyBase::AttackToPlayer(Player* player)
{
}
