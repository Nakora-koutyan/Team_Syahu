#include "LargeSwordEnemy.h"
#include "../../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

#define MAX_WAITING_TIME 90
#define LARGE_WALK_SPEED 3.f			//徘徊時のスピード
#define MAX_REST_TIME 60				//休息時間
#define ATTACK_COUNT_DOWN 31
#define LARGE_SWORD_KNOCKBACK 5		//ノックバック時間

//コンストラクタ
LargeSwordEnemy::LargeSwordEnemy():enemyImage(),enemyNumber(0),animInterval(0),animCountDown(false),animTurnFlg(true),
distance(0),restTime(0),attackCountDown(0),didAttack(false)
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
	LoadDivGraph("Resource/Images/Enemy/NightBorne3.png", 115, 23, 5, 240, 240, enemyImageOld);
	for (int i = 0; i < 115; i++)
	{
		//画像が存在しない部分を読み込まない
		if ((8 < i && i < 23) ||
			(28 < i && i < 46) ||
			(57 < i && i < 69) ||
			73 < i && i < 92)
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
	area = { 120.f,85.f };
	//表示座標{ x , y }
	location = { 1100,GROUND_LINE - area.height };
	
	//自身の持つ武器
	weaponType = Weapon::LargeSword;	//大剣

	//プレイヤーを見つけた際のマーク
	findMark = LoadGraph("Resource/Images/Exclamation.png");
	angryMark = LoadGraph("Resource/images/Angry.png");

	//体の向き
	direction = DIRECTION_LEFT;

	//体力
	hp = 100;

	//攻撃状態に入る範囲
	attackRange[0].x = GetMinLocation().x - 250.f;
	attackRange[0].y = GetCenterLocation().y;
	attackRange[1].x = GetMaxLocation().x + 250.f;
	attackRange[1].y = GetCenterLocation().y;

	//プレイヤーに攻撃を仕掛ける範囲
	attackCenser[0].x = GetMinLocation().x - 270.f;
	attackCenser[0].y = GetCenterLocation().y;
	attackCenser[1].x = GetMaxLocation().x + 270.f;
	attackCenser[1].y = GetCenterLocation().y;

	/*　状態　*/
	//表示するか?
	isShow = true;

	damage = 20.f;

	//攻撃時間
	attackWaitingTime = MAX_WAITING_TIME;
	statusChangeTime = MAX_COOL_TIME;

	//エネミーの状態(徘徊状態にする)
	enemyStatus = Patrol;
	//画像番号
	enemyNumber = 0;
	//休息時間の設定
	restTime = MAX_REST_TIME;

	attackCountDown = ATTACK_COUNT_DOWN;
}

//描画以外の更新
void LargeSwordEnemy::Update()
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(FPS * 0.5);
	KnockBack(this,FPS * 0.5, LARGE_SWORD_KNOCKBACK);

	//状態遷移
	switch (enemyStatus)
	{
		//パトロール処理
	case EnemyStatus::Patrol:
		EnemyPatrol();
		markStatus = NULL;
		break;

		//攻撃の予備動作
	case EnemyStatus::AttackStandBy:
		AttackStandBy();
		markStatus = findMark;
		break;

		//攻撃開始
	case EnemyStatus::AttackStart:
		AttackStart();
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
		DrawRotaGraphF(screenLocation.x + 50.f, screenLocation.y + 15.f, 1, 0,
			enemyImage[enemyNumber], TRUE, TRUE) :
		DrawRotaGraphF(screenLocation.x + 65.f, screenLocation.y + 15.f, 1, 0,
			enemyImage[enemyNumber], TRUE, FALSE);

	DrawFormatStringF(50.f, 300.f, 0xff0000, "colorRed %d", colorRed);
	DrawFormatStringF(50.f, 320.f, 0x00ff00, "colorGreen %d", colorGreen);
	DrawFormatStringF(50.f, 340.f, 0x0000ff, "colorBlue %d", colorBlue);
	DrawFormatStringF(50.f, 360.f, 0xffff00, "enemyImage %d", enemyNumber);
	DrawFormatStringF(50.f, 380.f, 0xff00ff, "animInterval %d", animInterval);
	DrawFormatStringF(50.f, 400.f, 0xff00ff, "enemystate %d", enemyStatus);

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

void LargeSwordEnemy::FindPlayer(Player* player)
{
	if (attackCenser[0].x < player->GetMaxLocation().x &&
		attackCenser[1].x > player->GetMinLocation().x)
	{
		//方向変化処理
		if (location.x >= player->GetCenterLocation().x)
		{
			direction = DIRECTION_LEFT;
			animTurnFlg = false;
		}
		else
		{
			direction = DIRECTION_RIGHT;
			animTurnFlg = true;
		}

		isFind = true;
	}
	else
	{
		isFind = false;
	}

	//プレイヤーへの接近処理
	SuddenApproachToPlayer(player);
}

//エネミーの徘徊処理
void LargeSwordEnemy::EnemyPatrol()
{
	
	//左向きの場合
	if (direction == DIRECTION_LEFT && restTime <= 0)
	{
		move.x = -LARGE_WALK_SPEED;
		patrolCounter -= LARGE_WALK_SPEED;
		//左に45進んだら向きを右にする
		if (patrolCounter <= -45.f)
		{
			direction = DIRECTION_RIGHT;
			animTurnFlg = false;
			restTime = MAX_REST_TIME;
		}
	}
	//右向きの場合
	if (direction == DIRECTION_RIGHT && restTime <= 0)
	{
		move.x = LARGE_WALK_SPEED;
		patrolCounter += LARGE_WALK_SPEED;
		//右に45進んだら向きを左にする
		if (patrolCounter >= 45.f)
		{
			direction = DIRECTION_LEFT;
			animTurnFlg = true;
			restTime = MAX_REST_TIME;
		}
	}
	if (restTime >= 0)
	{
		restTime--;
		move.x = 0.f;
	}

	//エネミーの状態遷移の処理
	if (isFind)
	{
		//攻撃準備の状態にする
		enemyStatus = EnemyStatus::AttackStandBy;
		restTime = MAX_REST_TIME;
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
		//距離が100以上の場合
		if (distance > 100)
		{
			//左向きの場合
			if (direction == DIRECTION_LEFT)
			{
				//画像：左向き
				animTurnFlg = true;
				//速度：８で移動
				move.x = -8.f;
			}
			if (direction == DIRECTION_RIGHT)
			{
				//画像：右向き
				animTurnFlg = false;
				//速度：８で移動
				move.x = 8.f;
			}
		}

		//攻撃準備処理
		if (distance <= 100)
		{
			//移動を０にする
			move.x = 0.f;

			//待機時間のリセット
			restTime = MAX_REST_TIME;

			//エネミーの状態を「攻撃開始」に遷移する
			enemyStatus = EnemyStatus::AttackStart;
		}
	}
}

//攻撃の準備時間
void LargeSwordEnemy::AttackStandBy()
{
	//攻撃範囲からプレイヤーが離れた場合
	if (!isFind)
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
void LargeSwordEnemy::AttackStart()
{
	//攻撃ができるなら
	if (isAttack == true && attackWaitingTime <= 0)
	{
		//攻撃までのカウントダウンを行う
		attackCountDown--;
		
		if (attackCountDown >= 0)
		{
			//カウントダウンが行われている間は動けない
			move.x = 0;
		}
		else if (attackCountDown <= 0)
		{
			//カウントダウンが０になったらリセット
			attackCountDown = ATTACK_COUNT_DOWN;
		}
	}

	if (didAttack == true)
	{
		//攻撃をしていれば状態を「攻撃終了」に遷移する
		enemyStatus = EnemyStatus::AttackEnd;
	}

	//攻撃の待ち時間の制御
	if (attackWaitingTime >= 0)
	{
		//攻撃時間を減算していく
		attackWaitingTime--;
	}
}

//攻撃終了
void LargeSwordEnemy::AttackEnd()
{
	enemyStatus = EnemyStatus::Patrol;
	restTime = 0;
	enemyNumber = 0;
	didAttack = false;

	//攻撃待機時間をリセットする
	attackWaitingTime = MAX_WAITING_TIME;
}

//アニメーション制御関数
void LargeSwordEnemy::EnemyAnimation()
{
	animInterval++;
	//パトロール時のアニメーション
	if (enemyStatus == EnemyStatus::Patrol)
	{
		//待機時間が０より大きい場合：待機アニメーション
		if (restTime >= 0)
		{
			//画像番号が８より大きい場合:0にする
			if (enemyNumber > 8)
			{
				enemyNumber = 0;
			}

			//5フレームに1回
			if (animInterval % 5 == 0)
			{
				//アニメーションを更新
				enemyNumber++;
			}
		}
		else if (restTime <= 0)
		{
			if (enemyNumber > 14)
			{
				enemyNumber = 9;
			}
			if (animInterval % 3 == 0)
			{
				enemyNumber++;
			}
		}
	}
	//攻撃準備中のアニメーション
	if (enemyStatus == EnemyStatus::AttackStandBy)
	{
		if (enemyNumber > 14)
		{
			enemyNumber = 9;
		}
		if (animInterval % 3 == 0)
		{
			enemyNumber++;
		}
	}
	//攻撃開始時のアニメーション
	if (enemyStatus == EnemyStatus::AttackStart)
	{
		if (attackWaitingTime >= 0)
		{
			if (enemyNumber >= 20)
			{
				enemyNumber = 18;
			}
			if (animInterval % 6 == 0)
			{
				enemyNumber++;
			}
		}
		else if (attackWaitingTime <= 0)
		{
			if (enemyNumber >= 26)
			{
				enemyNumber = 15;
				didAttack = true;
			}
			if (animInterval % 5 == 0)
			{
				enemyNumber++;
			}
		}
	}
}