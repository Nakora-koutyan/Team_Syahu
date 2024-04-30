#include "LargeSwordEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

#define MAX_WAITING_TIME 90

//コンストラクタ
LargeSwordEnemy::LargeSwordEnemy():enemyImage(),enemyNumber(0),animInterval(0),animCountDown(false),animTurnFlg(false)
{
}

//デストラクタ
LargeSwordEnemy::~LargeSwordEnemy()
{
}

//変数などの初期化
void LargeSwordEnemy::Initialize()
{
	//アニメーション画像に関する初期化
	enemyNumber = 0;
	int enemyImageOld[115];
	LoadDivGraph("Resource/Images/Enemy/NightBorne.png", 72, 8, 9, 96, 96, enemyImageOld);
	for (int i = 0; i < 115; i++)
	{
		//画像が存在しない部分を読み込まない
		if ((9 < i && i < 24) ||
			(29 < 1 && i < 47) ||
			(58 < i && i < 70) ||
			74 < i || i < 93)
		{
			//スキップ
			continue;
		}
		enemyImage[enemyNumber] = enemyImageOld[i];
		enemyNumber++;
	}

	//仮ボックスの色
	colorRed = 255;
	colorGreen = 255;
	colorBlue = 255;

	//サイズ{ x , y }
	area = { 120.f,120.f };
	//表示座標{ x , y }
	location = { 1500,GROUND_LINE - area.height };
	
	//自身の持つ武器
	weaponType = Weapon::LargeSword;	//大剣

	//攻撃状態に入る範囲
	attackRange[0] = { GetCenterLocation() };
	attackRange[1] = { GetCenterLocation() };

	//プレイヤーに攻撃を仕掛ける範囲
	attackCenser[0] = { GetCenterLocation() };
	attackCenser[1] = { GetCenterLocation() };

	//プレイヤーを見つけた際のマーク
	findMark = LoadGraph("Resource/Images/Exclamation.png");
	angryMark = LoadGraph("Resource/images/Angry.png");


	//体の向き
	direction = DIRECTION_LEFT;

	//体力
	hp = 100;

	/*　状態　*/
	//表示するか?
	isShow = true;

	//攻撃時間
	attackWaitingTime = MAX_WAITING_TIME;
	statusChangeTime = MAX_COOL_TIME;

	//エネミーの状態(徘徊状態にする)
	enemyStatus = Patrol;
	//画像番号
	enemyNumber = 0;
}

//描画以外の更新
void LargeSwordEnemy::Update(Player* player)
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(int(FPS * 0.5));
	KnockBack(FPS * 0.5);

	//エネミーの攻撃範囲
	AttackCenser();
	
	//状態遷移
	switch (enemyStatus)
	{
		//パトロール処理
	case EnemyStatus::Patrol:
		EnemyPatrol(player);
		markStatus = NULL;
		break;

		//攻撃の予備動作
	case EnemyStatus::AttackStandBy:
		AttackStandBy(player);
		markStatus = findMark;
		break;

		//攻撃開始
	case EnemyStatus::AttackStart:
		AttackStart(player);
		markStatus = angryMark;
		break;

		//攻撃終了
	case EnemyStatus::AttackEnd:
		AttackEnd();
		markStatus = NULL;
		break;
	}

	//エネミーアニメーション
	EnemyAnimation();

	location.x += move.x;
}

//描画に関する更新
void LargeSwordEnemy::Draw() const
{
	//エネミー表示
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		GetColor(colorRed, colorGreen, colorBlue), FALSE, 1.0f
	);
	animTurnFlg ?
		DrawRotaGraphF(screenLocation.x + 35.f, screenLocation.y + 45.f, 1, 0,
			enemyImage[enemyNumber], TRUE, TRUE) :
		DrawRotaGraphF(screenLocation.x + 50.f, screenLocation.y + 45.f, 1, 0,
			enemyImage[enemyNumber], TRUE, FALSE);

	DrawFormatStringF(50.f, 120.f, 0xff0000, "colorRed %d", colorRed);
	DrawFormatStringF(50.f, 140.f, 0x00ff00, "colorGreen %d", colorGreen);
	DrawFormatStringF(50.f, 160.f, 0x0000ff, "colorBlue %d", colorBlue);
	DrawFormatStringF(50.f, 180.f, 0xffff00, "enemyImage %d", enemyNumber);
	DrawFormatStringF(50.f, 200.f, 0xff00ff, "animInterval %d", animInterval);

	if (markStatus != NULL)
	{
		//プレイヤーを発見した場合、状態に応じて符号を表示する
		if (direction == DIRECTION_LEFT)
		{
			DrawGraphF(screenLocation.x + 75, screenLocation.y - 30, markStatus, TRUE);
		}
		if (direction == DIRECTION_RIGHT)
		{
			DrawGraphF(screenLocation.x - 25, screenLocation.y - 30, markStatus, TRUE);
		}
	}
}

//徘徊状態から警戒状態に入る範囲
void LargeSwordEnemy::AttackRange()
{
	attackRange[0].x = GetMinLocation().x - 250.f;
	attackRange[0].y = GetCenterLocation().y;

	attackRange[1].x = GetMaxLocation().x + 250.f;
	attackRange[1].y = GetCenterLocation().y;
}

//プレイヤーに攻撃を仕掛ける範囲
void LargeSwordEnemy::AttackCenser()
{
	attackCenser[0].x = GetMinLocation().x - 200.f;
	attackCenser[0].y = GetCenterLocation().y;

	attackCenser[1].x = GetMaxLocation().x + 200.f;
	attackCenser[1].y = GetCenterLocation().y;
}

//エネミーの徘徊処理
void LargeSwordEnemy::EnemyPatrol(Player* player)
{
	//左向きの場合
	if (direction == DIRECTION_LEFT)
	{
		move.x = -WALK_SPEED;
		patrolCounter -= WALK_SPEED;
		//左に50進んだら向きを右にする
		if (patrolCounter <= -200.f)
		{
			direction = DIRECTION_RIGHT;
			animTurnFlg = true;
		}
	}
	//右向きの場合
	if (direction == DIRECTION_RIGHT)
	{
		move.x = WALK_SPEED;
		patrolCounter += WALK_SPEED;
		//右に50進んだら向きを左にする
		if (patrolCounter >= 15.f)
		{
			direction = DIRECTION_LEFT;
			animTurnFlg = false;
		}
	}

	if (attackCenser[0].x < player->GetMaxLocation().x &&
		attackCenser[1].x > player->GetMinLocation().x)
	{
		//攻撃準備の状態にする
		enemyStatus = EnemyStatus::AttackStandBy;
	}

	//エネミーの色変更
	if (colorBlue < 255 && colorGreen < 255)
	{
		colorBlue += 15;
		colorGreen += 15;
	}
}

//攻撃の準備時間
void LargeSwordEnemy::AttackStandBy(Player* player)
{
}

//攻撃開始
void LargeSwordEnemy::AttackStart(Player* player)
{
}

//攻撃終了
void LargeSwordEnemy::AttackEnd()
{
}

//プレイヤーと衝突した場合
void LargeSwordEnemy::ClashToPlayer(Player* player)
{
}

//アニメーション制御関数
void LargeSwordEnemy::EnemyAnimation()
{

}