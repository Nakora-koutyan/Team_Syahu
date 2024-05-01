#include "LargeSwordEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

#define MAX_WAITING_TIME 90
#define LARGE_WALK_SPEED 3.f			//徘徊時のスピード
#define MAX_REST_TIME 30				//休息時間

//コンストラクタ
LargeSwordEnemy::LargeSwordEnemy():enemyImage(),enemyNumber(0),animInterval(0),animCountDown(false),animTurnFlg(false),
distance(0),restTime(0)
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
		if ((8 < i && i < 23) ||
			(28 < 1 && i < 46) ||
			(57 < i && i < 69) ||
			73 < i || i < 92)
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
	//休息時間の設定
	restTime = MAX_REST_TIME;
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
	/*DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		GetColor(colorRed, colorGreen, colorBlue), FALSE, 1.0f
	);*/
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
	attackCenser[0].x = GetMinLocation().x - 270.f;
	attackCenser[0].y = GetCenterLocation().y;

	attackCenser[1].x = GetMaxLocation().x + 270.f;
	attackCenser[1].y = GetCenterLocation().y;
}

//エネミーの徘徊処理
void LargeSwordEnemy::EnemyPatrol(Player* player)
{
	//左向きの場合
	if (direction == DIRECTION_LEFT)
	{
		move.x = -LARGE_WALK_SPEED;
		patrolCounter -= LARGE_WALK_SPEED;
		//左に200進んだら向きを右にする
		if (patrolCounter <= -200.f)
		{
			direction = DIRECTION_RIGHT;
			animTurnFlg = true;
			restTime = MAX_REST_TIME;
		}
	}
	//右向きの場合
	if (direction == DIRECTION_RIGHT)
	{
		move.x = LARGE_WALK_SPEED;
		patrolCounter += LARGE_WALK_SPEED;
		//右に200進んだら向きを左にする
		if (patrolCounter >= 200.f)
		{
			direction = DIRECTION_LEFT;
			animTurnFlg = false;
			restTime = MAX_REST_TIME;
		}
	}

	//エネミーの状態遷移の処理
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

//プレイヤーへの接近処理
void LargeSwordEnemy::SuddenApproachToPlayer(Player* player)
{
	//restTimeを減算する
	if (restTime >= 0)
	{
		restTime--;
	}
	//restTimeが０になった場合
	if (restTime <= 0)
	{
		//プレイヤーと自身の距離を計算
		distance = abs(player->GetCenterLocation().x - GetCenterLocation().x);
		//距離が50以下の場合
		if (distance >= 50)
		{
			//8の速度で接近する
			move.x = 8.f;
		}

		//攻撃準備処理
		if (distance <= 50 && attackWaitingTime >= 0)
		{
			//移動を０にする
			move.x = 0.f;
			//攻撃時間を減算していく
			attackWaitingTime--;
		}
	}
}

//攻撃の準備時間
void LargeSwordEnemy::AttackStandBy(Player* player)
{
	//プレイヤーと自身の位置をみて方向を転換する
	if (location.x <= player->GetCenterLocation().x)
	{
		//左方向
		direction = DIRECTION_LEFT;
	}
	else if (location.x >= player->GetCenterLocation().x)
	{
		//右方向
		direction = DIRECTION_RIGHT;
	}

	//プレイヤーへの接近処理
	SuddenApproachToPlayer(player);

	//攻撃待ち時間が０になった場合
	if (attackWaitingTime <= 0)
	{
		//エネミーの状態を「攻撃開始」に遷移する
		enemyStatus = EnemyStatus::AttackStart;
		//攻撃待機時間をリセットする
		attackWaitingTime = MAX_WAITING_TIME;
	}

	//攻撃範囲からプレイヤーが離れた場合
	if (direction == DIRECTION_LEFT && attackCenser[0].x > player->GetMinLocation().x ||
		direction == DIRECTION_RIGHT && attackCenser[1].x < player->GetMaxLocation().x)
	{
		//パトロール状態にする
		enemyStatus = EnemyStatus::Patrol;
	}

	//エネミーの色変更
	if (colorBlue > 0 && colorGreen > 0)
	{
		colorBlue -= 4;
		colorGreen -= 4;
	}
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