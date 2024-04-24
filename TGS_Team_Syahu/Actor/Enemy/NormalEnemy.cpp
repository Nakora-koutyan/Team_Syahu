#include "NormalEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

//コンストラクタ
NormalEnemy::NormalEnemy():enemyColor(0),damageColor(0),attackColor(0),usualColor(0),
attackRange{},chaseCenser{},hp(100),findMark(NULL),angryMark(NULL),direction(0),isChase(false)
{
}

//デストラクタ
NormalEnemy::~NormalEnemy()
{
}

//初期化処理
void NormalEnemy::Initialize()
{
	//仮の色付け
	//通常のカラー
	usualColor = GetColor(0, 255, 0);
	//ダメージを受けた時の色
	damageColor = GetColor(255, 0, 0);
	//攻撃をするときの色
	attackColor = GetColor(0, 0, 255);

	//体の色の情報を受け取る変数
	enemyColor = usualColor;
	
	//サイズ{ x , y }
	area = { 90.f,90.f };
	//表示座標{ x , y }
	location = { 1200,GROUND_LINE - area.height };
	//キャラクターの能力
	weaponType = Weapon::LargeSword;	//かり

	//攻撃範囲
	attackRange[0] = { GetCenterLocation() };
	attackRange[1] = { GetCenterLocation() };

	//プレイヤーを追跡する範囲
	chaseCenser[0] = { GetCenterLocation() };
	chaseCenser[1] = { GetCenterLocation() };

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
	attackTime = MAX_ATTACK_TIME;
	attackCoolTime = MAX_COOL_TIME;
}

//描画以外の内容を更新
void NormalEnemy::Update(Player* player)
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(int(FPS * 0.5));
	KnockBack(FPS * 0.5);

	//エネミーの攻撃範囲
	AttackRange();
	//プレイヤーを検知するセンサー
	ChaseRange();

	if (noMove != true)
	{
		//エネミーの徘徊処理
		EnemyPatrol(player);
		if (isAttack != true)
		{
			//プレイヤーへの追跡
			AttackStandBy(player);
		}
		//プレイヤーへの攻撃
		AttackStart(player);

		location.x += move.x;
	}
	else if (noMove == true)
	{
		attackCoolTime--;
		if (attackCoolTime <= 0)
		{
			noMove = false;
		}
	}
}

//描画に関する更新
void NormalEnemy::Draw() const
{
	//エネミー表示
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		isHit ? 0xff0000 : isAttack ? attackColor : usualColor, TRUE, 1.0f
	);
	DrawFormatStringF(50.f, 80.f, GetColor(255, 0, 255), "%f GetMinLocation().x", GetMinLocation().x);
	DrawFormatStringF(50.f, 180.f, GetColor(255, 0, 255), "%s isChase", isChase ? "true" : "false");
	DrawFormatStringF(50.f, 100.f, GetColor(255, 0, 255), "%d AttackCoolTime", attackCoolTime);
	DrawFormatStringF(50.f, 120.f, GetColor(255, 0, 255), "%d attackTime", attackTime);
	DrawFormatStringF(50.f, 140.f, GetColor(255, 0, 255), "%s noMove", noMove ? "true" : "false");
	DrawFormatStringF(50.f, 160.f, GetColor(255, 0, 255), "%s isAttack", isAttack ? "true" : "false");
	DrawFormatStringF(50.f, 180.f, GetColor(255, 0, 255), "%s isChase", isChase ? "true" : "false");
	DrawFormatStringF(50.f, 200.f, GetColor(255, 0, 255), "%s isPatrol", isPatrol ? "true" : "false");
	DrawFormatStringF(50.f, 220.f, GetColor(255, 0, 255), "%f patrolCounter", patrolCounter);
	
	//プレイヤーを発見した場合、「！」を表示する
	if (isChase == true)
	{
		if (direction == DIRECTION_LEFT)
		{
			DrawGraphF
			(
				screenLocation.x + 25, screenLocation.y - 30,
				isAttack ? angryMark:findMark, TRUE
			);
		}
		if (direction == DIRECTION_RIGHT)
		{
			DrawGraphF
			(
				screenLocation.x - 25, screenLocation.y - 30,
				isAttack ? angryMark : findMark, TRUE
			);
		}
	}
}

//攻撃範囲
void NormalEnemy::AttackRange()
{
	attackRange[0].x = GetMinLocation().x - 250.f;
	attackRange[0].y = GetCenterLocation().y;

	attackRange[1].x = GetMaxLocation().x + 250.f;
	attackRange[1].y = GetCenterLocation().y;
}

//追跡に入る範囲
void NormalEnemy::ChaseRange()
{
	chaseCenser[0].x = GetMinLocation().x - 400.f;
	chaseCenser[0].y = GetCenterLocation().y;

	chaseCenser[1].x = GetMaxLocation().x + 400.f;
	chaseCenser[1].y = GetCenterLocation().y;
}

//プレイヤーのいる方向に向かう
void NormalEnemy::EnemyPatrol(Player* player)
{
	//パトロール条件(攻撃・追跡の範囲にプレイヤーが存在しない場合)
	if (isChase == false && isAttack == false)
	{
		//パトロールをする
		isPatrol = true;
	}
	else
	{
		//パトロールを中止する
		isPatrol = false;
	}

	//パトロール処理
	if (isPatrol == true)
	{
		//左向きの場合
		if(direction == DIRECTION_LEFT)
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
	}
}

void NormalEnemy:: AttackStandBy(Player* player)
{
	//プレイヤーが追跡範囲内にいるかのチェック
	if (chaseCenser[0].x < player->GetMaxLocation().x &&
		chaseCenser[1].x > player->GetMinLocation().x &&
		attackTime >= 0)
	{
		isChase = true;
	}
	else
	{
		isChase = false;
	}

	//追跡処理
	//プレイヤーが自身よりも左側にいる場合
	if (player->GetCenterLocation().x < location.x
		&& isChase == true)
	{
		//左を向く
		direction = DIRECTION_LEFT;
		//左方向に進む
		move.x = -(WALK_SPEED * CHASE_SPEED);
	}
	//プレイヤーが自身よりも右側にいる場合
	if (player->GetCenterLocation().x > location.x
		&& isChase == true)
	{
		//右を向く
		direction = DIRECTION_RIGHT;
		//左方向に進む
		move.x = (WALK_SPEED * CHASE_SPEED);
	}
}

void NormalEnemy::AttackStart(Player* player)
{
	//プレイヤーが攻撃範囲にいるかのチェック
	if (attackRange[0].x < player->GetMaxLocation().x &&
		attackRange[1].x > player->GetMinLocation().x )
	{
		isAttack = true;
	}
	else
	{
		isAttack = false;
	}

	//左向きに攻撃を行う
	if (direction == DIRECTION_LEFT && isAttack == true)
	{
		move.x = -(WALK_SPEED*ATTACK_SPEED);
	}
	//右向きに攻撃を行う
	if (direction == DIRECTION_RIGHT && isAttack == true)
	{
		move.x = (WALK_SPEED * ATTACK_SPEED);
	}
	//プレイヤーと接触した場合
	if (CollisionCheck(player) == true && noMove == false)
	{
		isAttack = false;
		noMove = true;
		attackCoolTime = MAX_COOL_TIME;
	}
}

void NormalEnemy::ClashToPlayer(Player* player)
{
	if (CollisionCheck(player) == true)
	{

	}
}

void NormalEnemy::AttackEnd()
{
}