#include "EnemyBase.h"

EnemyBase::EnemyBase() :isClash(false), statusChangeTime(0), attackWaitingTime(0), noMove(false),patrolCounter(0.f), enemyStatus{},
findMark(NULL),angryMark(NULL),attackRange{}, attackCenser{0}, colorRed(NULL), colorGreen(NULL), colorBlue(NULL), direction(NULL), hp(0),
markStatus(NULL)
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