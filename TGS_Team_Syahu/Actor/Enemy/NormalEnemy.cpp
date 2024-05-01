#include "NormalEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

#define MAX_WAITING_TIME 120

//コンストラクタ
NormalEnemy::NormalEnemy():enemyImage{NULL},enemyNumber(0),animInterval(0),animCountDown(false),animTurnFlg(false)
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
	weaponType = Weapon::Empty;	//突進(武器無し)

	//攻撃状態に入る範囲
	attackRange[0] = { GetCenterLocation() };
	attackRange[1] = { GetCenterLocation() };

	//プレイヤーを追跡する範囲
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

	enemyStatus = Patrol;
	enemyNumber = 0;
}

//描画以外の内容を更新
void NormalEnemy::Update(Player* player)
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(int(FPS * 0.5));
	KnockBack(FPS * 0.5);

	//徘徊状態から警戒状態に入る範囲
	AttackRange();

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
void NormalEnemy::Draw() const
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
			DrawGraphF(screenLocation.x + 35, screenLocation.y - 20, markStatus, TRUE);
		}
		if (direction == DIRECTION_RIGHT)
		{
			DrawGraphF(screenLocation.x, screenLocation.y - 20, markStatus, TRUE);
		}
	}
}

//攻撃に入る範囲
void NormalEnemy::AttackRange()
{
	attackRange[0].x = GetMinLocation().x - 410.f;
	attackRange[0].y = GetCenterLocation().y;

	attackRange[1].x = GetMaxLocation().x + 410.f;
	attackRange[1].y = GetCenterLocation().y;
}

//徘徊状態から警戒状態に入る範囲
void NormalEnemy::AttackCenser()
{
	attackCenser[0].x = GetMinLocation().x - 430.f;
	attackCenser[0].y = GetCenterLocation().y;

	attackCenser[1].x = GetMaxLocation().x + 430.f;
	attackCenser[1].y = GetCenterLocation().y;
}

//プレイヤーのいる方向に向かう
void NormalEnemy::EnemyPatrol(Player* player)
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

	if (attackRange[0].x < player->GetMinLocation().x &&
		attackRange[1].x > player->GetMaxLocation().x )
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

void NormalEnemy:: AttackStandBy(Player* player)
{
	//方向変化処理
	if (location.x >= player->GetCenterLocation().x)
	{
		direction = DIRECTION_LEFT;
		animTurnFlg = false;
	}
	else if (location.x <= player->GetCenterLocation().x)
	{
		direction = DIRECTION_RIGHT;
		animTurnFlg = true;
	}

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

void NormalEnemy::AttackStart(Player* player)
{
	//プレイヤーがこの範囲内にいるなら攻撃を続行する
	if ((direction == DIRECTION_LEFT && attackCenser[0].x < player->GetCenterLocation().x 
		&& GetMaxLocation().x + 200 > player->GetCenterLocation().x)||
		(direction == DIRECTION_RIGHT && attackCenser[1].x > player->GetCenterLocation().x)
		&& GetMinLocation().x - 200 < player->GetCenterLocation().x)
	{
		//攻撃を続行
		isAttack = true;
	}
	else
	{
		//攻撃を中止
		isAttack = false;
	}

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
	}
	//プレイヤーと接触した場合
	if (CollisionCheck(player) == true)
	{
		//ノックバック処理
		KnockBack(MAX_COOL_TIME);
		//衝突している
		isClash = true;
	}
	else
	{
		//衝突していない
		isClash = false;
	}

	//攻撃を続行しない場合またはプレイヤーと衝突した場合
	if (isAttack == false || isClash == true)
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
	}
}

void NormalEnemy::ClashToPlayer(Player* player)
{
	if (CollisionCheck(player) == true)
	{

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
		if (animInterval % 16 == 0)
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
}