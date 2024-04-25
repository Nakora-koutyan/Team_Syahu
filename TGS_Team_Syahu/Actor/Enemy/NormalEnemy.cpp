#include "NormalEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

//コンストラクタ
NormalEnemy::NormalEnemy():enemyColor(0),damageColor(0),attackColor(0),usualColor(0),
attackRange{},attackCenser{},hp(100),findMark(NULL),angryMark(NULL),direction(0),isChase(false),markStatus(NULL),
colorRed(0),colorGreen(0),colorBlue(0),enemyImage{NULL},enemyNumber(0)
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

	//仮の色付け
	//通常のカラー
	usualColor = GetColor(0, 255, 0);
	//ダメージを受けた時の色
	damageColor = GetColor(255, 0, 0);
	//攻撃をするときの色
	attackColor = GetColor(0, 0, 255);

	colorRed = 255;
	colorGreen = 255;
	colorBlue = 255;

	//体の色の情報を受け取る変数
	enemyColor = GetColor(colorRed,colorGreen,colorBlue);
	
	//サイズ{ x , y }
	area = { 80.f,90.f };
	//表示座標{ x , y }
	location = { 1200,GROUND_LINE - area.height };
	//キャラクターの能力
	weaponType = Weapon::LargeSword;	//かり

	//攻撃範囲
	attackRange[0] = { GetCenterLocation() };
	attackRange[1] = { GetCenterLocation() };

	//プレイヤーを追跡する範囲
	attackCenser[0] = { GetCenterLocation() };
	attackCenser[1] = { GetCenterLocation() };

	//プレイヤーを見つけた際の座標
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
}

//描画以外の内容を更新
void NormalEnemy::Update(Player* player)
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(int(FPS * 0.5));
	KnockBack(FPS * 0.5);

	//エネミーの攻撃範囲
	AttackCenser();
	//プレイヤーを検知するセンサー
	AttackRange();

	//状態遷移
	switch (enemyStatus)
	{
		//パトロール処理
	case EnemyStatus::Patrol:
		EnemyPatrol(player);
		enemyNumber = 0;
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
		GetColor(colorRed,colorGreen,colorBlue), FALSE, 1.0f
	);
	DrawGraphF
	(
		screenLocation.x - 15.f, screenLocation.y-20.f,
		enemyImage[enemyNumber], TRUE
	);

	DrawFormatStringF(50.f, 120.f, 0xff0000, "colorRed %d", colorRed);
	DrawFormatStringF(50.f, 140.f, 0x00ff00, "colorGreen %d", colorGreen);
	DrawFormatStringF(50.f, 160.f, 0x0000ff, "colorBlue %d", colorBlue);
	DrawFormatStringF(50.f, 180.f, 0xffff00, "enemyImage %d", enemyNumber);

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

//攻撃範囲
void NormalEnemy::AttackCenser()
{
	attackRange[0].x = GetMinLocation().x - 400.f;
	attackRange[0].y = GetCenterLocation().y;

	attackRange[1].x = GetMaxLocation().x + 400.f;
	attackRange[1].y = GetCenterLocation().y;
}

//追跡に入る範囲
void NormalEnemy::AttackRange()
{
	attackCenser[0].x = GetMinLocation().x - 350.f;
	attackCenser[0].y = GetCenterLocation().y;

	attackCenser[1].x = GetMaxLocation().x + 350.f;
	attackCenser[1].y = GetCenterLocation().y;
}

//プレイヤーのいる方向に向かう
void NormalEnemy::EnemyPatrol(Player* player)
{
	//左向きの場合
	if (direction == DIRECTION_LEFT)
	{
		move.x = -WALK_SPEED;
		patrolCounter -= WALK_SPEED;
		//左に50進んだら向きを右にする
		if (patrolCounter <= -150.f)
		{
			direction = DIRECTION_RIGHT;
		}
	}
	//右向きの場合
	if (direction == DIRECTION_RIGHT)
	{
		move.x = WALK_SPEED;
		patrolCounter += WALK_SPEED;
		//右に50進んだら向きを左にする
		if (patrolCounter >= 150.f)
		{
			direction = DIRECTION_LEFT;
		}
	}

	if (attackCenser[0].x < player->GetMaxLocation().x &&
		attackCenser[1].x > player->GetMinLocation().x )
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
	}
	else if (location.x <= player->GetCenterLocation().x)
	{
		direction = DIRECTION_RIGHT;
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
	if (attackCenser[0].x > player->GetMaxLocation().x &&
		attackCenser[1].x < player->GetMinLocation().x)
	{
		//パトロール状態にする
		enemyStatus = EnemyStatus::Patrol;
	}

	//エネミーの色変更
	if (colorBlue > 0 && colorGreen > 0)
	{
		colorBlue -= 4.25;
		colorGreen -= 4.25;
	}
	
}

void NormalEnemy::AttackStart(Player* player)
{
	//プレイヤーがこの範囲内にいるなら攻撃を続行する
	if (attackRange[0].x <= player->GetCenterLocation().x && 
		attackRange[1].x >= player->GetCenterLocation().x)
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
			move.x = -(WALK_SPEED * ATTACK_SPEED);
		}
		//右向きに攻撃を行う
		if (direction == DIRECTION_RIGHT)
		{
			move.x = (WALK_SPEED * ATTACK_SPEED);
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