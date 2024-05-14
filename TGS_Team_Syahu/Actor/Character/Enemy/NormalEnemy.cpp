#include "NormalEnemy.h"
#include "../../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

#define MAX_WAITING_TIME 120
#define NORMAL_ENEMY_KNOCKBACK 3.f
#define MAX_ATTACK_TIME 40

//コンストラクタ
NormalEnemy::NormalEnemy():enemyImage{NULL},enemyNumber(0),animInterval(0),animCountDown(false),
animTurnFlg(false),attackTime(0),once(false)
{
}

//デストラクタ
NormalEnemy::~NormalEnemy()
{
}

//初期化処理
void NormalEnemy::Initialize()
{
	for (enemyNumber = 0; enemyNumber < 6; enemyNumber++)
	{
		enemyImage[enemyNumber] = NULL;
	}
	//エネミー画像の格納
	LoadDivGraph("Resource/Images/Enemy/rapier.png", 6, 6, 1, 120, 130, enemyImage);

	colorRed = 255;
	colorGreen = 255;
	colorBlue = 255;

	//サイズ{ x , y }
	area = { 80.f,90.f };
	//表示座標{ x , y }
	location = { 1200,GROUND_LINE - area.height };
	//キャラクターの能力
	weaponType = Weapon::Rapier;	//突進(武器無し)

	//プレイヤーを見つけた際のマーク
	findMark = LoadGraph("Resource/Images/Exclamation.png");
	angryMark = LoadGraph("Resource/images/Angry.png");

	//体の向き
	direction = DIRECTION_LEFT;

	//攻撃状態に入る範囲
	attackRange[0].x = GetMinLocation().x - 410.f;
	attackRange[0].y = GetMinLocation().y - 75;
	attackRange[1].x = GetMaxLocation().x + 410.f;
	attackRange[1].y = GetMaxLocation().y + 75;

	//プレイヤーを追跡する範囲
	attackCenser[0].x = GetMinLocation().x - 430.f;
	attackCenser[0].y = GetMinLocation().y - 75;
	attackCenser[1].x = GetMaxLocation().x + 430.f;
	attackCenser[1].y = GetMaxLocation().y + 75;

	//体力
	hp = 100;

	/*　状態　*/
	//表示するか?
	isShow = true;

	//攻撃時間
	attackWaitingTime = MAX_WAITING_TIME;
	statusChangeTime = MAX_COOL_TIME;

	enemyStatus = Patrol;
	enemyNumber = 0;
	attackTime = MAX_ATTACK_TIME;
}

//描画以外の内容を更新
void NormalEnemy::Update()
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(FPS * 0.5);
	KnockBack(this, FPS * 0.5f, NORMAL_ENEMY_KNOCKBACK);

	
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
void NormalEnemy::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, enemyAlpha);
	DrawRotaGraphF(screenLocation.x + 35.f, screenLocation.y + 45.f, 1, 0,
		enemyImage[enemyNumber], TRUE, animTurnFlg);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBoxAA(GetMinScreenLocation().x - (410.f/2.f),GetMinScreenLocation().y - (75.f/2.f),
			GetMaxScreenLocation().x + (410.f/2.f),GetMaxScreenLocation().y + (75.f/2.f),
			0x00ffff, FALSE, 1.f);

	if (markStatus != NULL)
	{
		//プレイヤーを発見した場合、状態に応じて符号を表示する
		if (direction == DIRECTION_LEFT)
		{
			DrawGraphF(screenLocation.x + 35, screenLocation.y - 20, markStatus, TRUE);
		}
		if (direction == DIRECTION_RIGHT)
		{
			DrawGraphF(screenLocation.x, screenLocation.y - 20, markStatus, TRUE);
		}
	}
}

void NormalEnemy::FindPlayer(Player* player)
{
	if ((enemyStatus == EnemyStatus::AttackStandBy || 
		enemyStatus == EnemyStatus::Patrol )&&
		player->GetIsHit() == false)
	{
		if ((attackRange[0].x < player->GetCenterLocation().x &&
			attackRange[1].x > player->GetCenterLocation().x)
			&& attackRange[0].y <= player->GetCenterLocation().y &&
			attackRange[1].y >= player->GetCenterLocation().y)
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
	}
}

//プレイヤーのいる方向に向かう
void NormalEnemy::EnemyPatrol()
{
	//左向きの場合
	if (direction == DIRECTION_LEFT)
	{
		move.x = -NORMAL_WALK_SPEED;
		patrolCounter -= NORMAL_WALK_SPEED;
		//左に50進んだら向きを右にする
		if (patrolCounter <= -150.f)
		{
			direction = DIRECTION_RIGHT;
			animTurnFlg = true;
		}
	}
	//右向きの場合
	if (direction == DIRECTION_RIGHT)
	{
		move.x = NORMAL_WALK_SPEED;
		patrolCounter += NORMAL_WALK_SPEED;
		//右に50進んだら向きを左にする
		if (patrolCounter >= 150.f)
		{
			direction = DIRECTION_LEFT;
			animTurnFlg = false;
		}
	}

	//攻撃準備に入る処理
	if (isFind)
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

void NormalEnemy:: AttackStandBy()
{
	//攻撃準備処理
	if (attackWaitingTime >= 0)
	{
		//エネミーの移動を０にする
		move.x = 0;
		//攻撃待機時間を減算していく
		attackWaitingTime--;
	}

	if (attackWaitingTime <= 0)
	{
		//エネミーの状態を「攻撃開始」に遷移する
		enemyStatus = EnemyStatus::AttackStart;
		//攻撃待機時間をリセットする
		attackWaitingTime = MAX_WAITING_TIME;
	}

	//攻撃範囲からプレイヤーが離れた場合
	if (isFind = false && attackWaitingTime >= 0)
	{
		//パトロール状態にする
		enemyStatus = EnemyStatus::Patrol;
		//攻撃待機時間をリセットする
		attackWaitingTime = MAX_WAITING_TIME;
	}

	//エネミーの色変更
	if (colorBlue > 0 && colorGreen > 0)
	{
		colorBlue -= 4;
		colorGreen -= 4;
	}
}

void NormalEnemy::AttackStart()
{
	//攻撃時間が０秒以上であれば
	if (attackTime >= 0)
	{
		//攻撃可能にする
		isAttack = true;
	}
	else
	{
		isAttack = false;
	}

	//攻撃可能なら
	if (isAttack == true)
	{
		//左向きに攻撃を行う
		if (direction == DIRECTION_LEFT)
		{
			animTurnFlg = false;
			move.x = -(NORMAL_WALK_SPEED * ATTACK_SPEED);
		}
		//右向きに攻撃を行う
		if (direction == DIRECTION_RIGHT)
		{
			animTurnFlg = true;
			move.x = (NORMAL_WALK_SPEED * ATTACK_SPEED);
		}

		attackTime--;
	}
	//攻撃を続行しない場合またはプレイヤーと衝突した場合
	if (!isAttack || isKnockBack)
	{
		//エネミーの状態を攻撃終了に遷移する
		enemyStatus = EnemyStatus::AttackEnd;
	}
}

void NormalEnemy::AttackEnd()
{
	statusChangeTime--;
	move.x = 0;
	if (statusChangeTime <= 0)
	{
		enemyStatus = EnemyStatus::Patrol;
		statusChangeTime = MAX_COOL_TIME;
		attackTime = MAX_ATTACK_TIME;
	}
}

//アニメーション制御関数
void NormalEnemy::EnemyAnimation()
{
	animInterval++;
	//パトロール状態の場合
	if (enemyStatus == EnemyStatus::Patrol)
	{
		//敵画像の番号が2以上でカウントダウンがfalseの場合
		if (enemyNumber >= 2 && animCountDown == false)
		{
			//カウントダウンに切り替える
			animCountDown = true;
		}
		//16フレームごとにアニメーションを切り替える
		if (animInterval % 12 == 0)
		{
			//画像番号を減少する
			if (animCountDown == true)
			{
				enemyNumber--;
			}
			//画像番号を増加する
			if (animCountDown == false)
			{
				enemyNumber++;
			}
		}
		//エネミーの画像番号が０以下になった場合
		if (enemyNumber <= 0 && animCountDown == true)
		{
			//カウントダウンをfalseに切り替える
			animCountDown = false;
		}
	}

	//攻撃準備状態の場合
	if (enemyStatus == EnemyStatus::AttackStandBy)
	{
		enemyNumber = 2;
		animCountDown = false;
	}

	//攻撃中の場合
	if (enemyStatus == EnemyStatus::AttackStart)
	{
		//画像の番号が３以下の場合
		if (enemyNumber <= 3)
		{
			enemyNumber = 3;
		}
		//画像番号が5以上でカウントダウンが解除されている場合
		if (enemyNumber >= 5 && animCountDown == false)
		{
			//カウントダウン状態に切り替える
			animCountDown = true;
		}
		//16フレーム毎に画像を切り替える
		if (animInterval % 8 == 0)
		{
			//画像番号を減少する
			if (animCountDown == true)
			{
				enemyNumber--;
			}
			//画像番号を増加する
			if (animCountDown == false)
			{
				enemyNumber++;
			}
		}
		//エネミーの画像番号が４以下になった場合
		if (enemyNumber <= 4 && animCountDown == true)
		{
			//カウントダウンをfalseに切り替える
			animCountDown = false;
		}
	}

	//攻撃終了状態の場合
	if (enemyStatus == EnemyStatus::AttackEnd)
	{
		//8フレーム毎に切り替える
		if (animInterval % 8 == 0)
		{
			//画像番号を減少させる
			enemyNumber--;
		}
		//エネミーの画像番号が０以下になった場合
		if (enemyNumber <= 0)
		{
			enemyNumber = 0;
		}
	}

	//ノックバックが発生した場合
	if (isHit)
	{
		//点滅処理用カウンター
		blinkCounter++;

		//4フレーム毎に行う処理
		if (blinkCounter % 8 == 0)
		{
			//現在のtrue,falseを入れ替える
			isBlink = !isBlink;

			isBlink ? enemyAlpha = 124 : enemyAlpha = 255;
		}
	}
	else
	{
		enemyAlpha = 255;
	}
}