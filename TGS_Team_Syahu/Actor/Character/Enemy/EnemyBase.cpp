#include "EnemyBase.h"

EnemyBase::EnemyBase() :isClash(false), statusChangeTime(0), attackWaitingTime(0), noMove(false),patrolCounter(0.f), enemyStatus{},
findMark(NULL),angryMark(NULL),attackRange{}, attackCenser{0}, colorRed(NULL), colorGreen(NULL), colorBlue(NULL),hp(0),
markStatus(NULL),isBlink(false),blinkCounter(0),enemyAlpha(255),isFind(false)
{
	objectType = ObjectType::Enemy;
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