#include "NormalEnemy.h"
#include "../Player/Player.h"
#include "../../Camera/Camera.h"

#define NORMAL_ENEMY_KNOCKBACK 3.f

//コンストラクタ
NormalEnemy::NormalEnemy(float x, float y):enemyImage{NULL},enemyNumber(0),animInterval(0),animCountDown(false),
animTurnFlg(false),attackTime(0), CountChangeCounter(0),onlyOnce(false),isFirst(false),locXCorrect(0), locYCorrect(0)
{
	//表示座標{ x , y }
	location = { x,y };
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

	int enemyDeathImageOld[12];
	LoadDivGraph("Resource/Images/Enemy/RapierEnemyDeath.png", 12, 3, 4, 120, 130, enemyDeathImageOld);
	for (int i = 0; i < 12; i++)
	{
		enemyDeathImage[i] = NULL;
		if (11 < i)
		{
			continue;
		}
		enemyDeathImage[i] = enemyDeathImageOld[i];
	}

	//当たり判定のサイズ{ x , y }
	area = { 60.f,90.f };
	//キャラクターの能力
	weaponType = Weapon::Rapier;	//突進(武器無し)
	enemyType = EnemyType::RapierEnemy;

	//体の向き
	direction.x = DIRECTION_LEFT;

	//体力
	hp = 100;

	/*　状態　*/
	//表示するか?
	isShow = true;

	damage = 10.f;

	rapier = new Rapier;

	//攻撃時間
	attackWaitingTime = MAX_WAITING_TIME;
	statusChangeTime = MAX_COOL_TIME;

	enemyStatus = Patrol;
	enemyNumber = 0;
	attackTime = MAX_ATTACK_TIME;

	//画像のX・Y座標それぞれの補正
	locXCorrect = 35.f;
	locYCorrect = 45.f;
}

void NormalEnemy::Finalize()
{
	delete rapier;
}

//描画以外の内容を更新
void NormalEnemy::Update()
{
	DamageInterval(FPS * 0.2);
	KnockBack(this, FPS * 0.5f, knockBackMove);
	Landing(WORLD_HEIGHT);
	
	//状態遷移
	switch (enemyStatus)
	{
		//パトロール処理
	case EnemyStatus::Patrol:
		EnemyPatrol();
		break;

		//攻撃の予備動作
	case EnemyStatus::AttackStandBy:
		AttackStandBy();
		break;

		//攻撃開始
	case EnemyStatus::AttackStart:
		AttackStart();
		break;

		//攻撃終了
	case EnemyStatus::AttackEnd:
		AttackEnd();
		break;

		//死亡
	case EnemyStatus::Death:
		Death();
		break;

		//ダメージ処理
	case EnemyStatus::Damage:

		Damage();
		break;
	}

	if (hp <= 0)
	{
		enemyStatus = EnemyStatus::Death;
		isShow = false;
	}

	//武器がなくなった場合
	if (weaponType == Weapon::None)
	{
		Finalize();
		rapier = nullptr;
	}

	//攻撃範囲
	AttackRange();
	
	//エネミーアニメーション
	EnemyAnimationManager();

	//世界の両端を越えない
	DontCrossBorder();

	if (weaponType == Weapon::Rapier)
	{
		//レイピアの呼び出し (引数：(装備対象,攻撃時の速度))
		rapier->Update(this, ATTACK_SPEED, { 30,15 });
	}

	oldLocation = location;

}

//描画に関する更新
void NormalEnemy::Draw() const
{
	//説明変数宣言
	bool enemyDamageOrDeath = (enemyStatus == EnemyStatus::Death || enemyStatus == EnemyStatus::Damage);

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, enemyAlpha);
	DrawRotaGraphF(screenLocation.x + locXCorrect, screenLocation.y + locYCorrect, 1, 0,
		enemyDamageOrDeath ? enemyDeathImage[enemyNumber] : enemyImage[enemyNumber],
		TRUE, animTurnFlg);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#ifdef DEBUG
	DrawBoxAA(GetMinScreenLocation().x, GetMinScreenLocation().y,
		GetMaxScreenLocation().x, GetMaxScreenLocation().y, 0xff00ff, FALSE);
	
	//攻撃範囲用の矩形
	DrawBoxAA(GetMinScreenLocation().x - 310.f,GetMinScreenLocation().y - 75.f,
			GetMaxScreenLocation().x + 310.f,GetMaxScreenLocation().y + 75.f,
			0x00ffff, FALSE, 1.f);
	//体力表示用のデバッグ表示
	DrawFormatString(250, 300, 0xff0f0f, "HP　%d", hp);
#endif
	if (weaponType == Weapon::Rapier)
	{
		rapier->Draw();
	}
}

//攻撃範囲の指定
void NormalEnemy::AttackRange()
{
	//攻撃状態に入る範囲
	attackRange[0].x = GetMinLocation().x - 310.f;
	attackRange[0].y = GetMinLocation().y - 75;
	attackRange[1].x = GetMaxLocation().x + 310.f;
	attackRange[1].y = GetMaxLocation().y + 75;
}

void NormalEnemy::FindPlayer(const Player* player)
{
	//パトロール状態もしくは攻撃準備の状態でPlayerが攻撃を受けていない
	if ((enemyStatus == EnemyStatus::Patrol ||
		enemyStatus == EnemyStatus::AttackStandBy)&&
		player->GetIsHit() == false)
	{
		if ((attackRange[0].x <= player->GetCenterLocation().x &&
			attackRange[1].x >= player->GetCenterLocation().x)
			&& attackRange[0].y <= player->GetCenterLocation().y &&
			attackRange[1].y >= player->GetCenterLocation().y)
		{
			//方向変化処理
			if (location.x >= player->GetCenterLocation().x)
			{
				direction.x = DIRECTION_LEFT;
				animTurnFlg = false;
			}
			else
			{
				direction.x = DIRECTION_RIGHT;
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

void NormalEnemy::HitWeapon(ObjectBase* object)
{
	CharaBase* target = static_cast<CharaBase*>(object);

	if (signToAttack)
	{
		if (target->GetIsShow() && !target->GetIsHit())
		{
			target->SetKnockBackMove(NORMAL_ENEMY_KNOCKBACK);
		}
	}
}

//プレイヤーのいる方向に向かう
void NormalEnemy::EnemyPatrol()
{
	//左向きの場合
	if (direction.x == DIRECTION_LEFT)
	{
		move.x = -NORMAL_WALK_SPEED;
		patrolCounter -= NORMAL_WALK_SPEED;
		//左に50進んだら向きを右にする
		if (patrolCounter <= -150.f)
		{
			direction.x = DIRECTION_RIGHT;
			animTurnFlg = true;
		}
	}
	//右向きの場合
	if (direction.x == DIRECTION_RIGHT)
	{
		move.x = NORMAL_WALK_SPEED;
		patrolCounter += NORMAL_WALK_SPEED;
		//右に50進んだら向きを左にする
		if (patrolCounter >= 150.f)
		{
			direction.x = DIRECTION_LEFT;
			animTurnFlg = false;
		}
	}

	//攻撃準備に入る処理
	if (isFind)
	{
		//攻撃準備の状態にする
		enemyStatus = EnemyStatus::AttackStandBy;
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
	if (isFind == false && attackWaitingTime >= 0)
	{
		//パトロール状態にする
		enemyStatus = EnemyStatus::Patrol;
		//攻撃待機時間をリセットする
		attackWaitingTime = MAX_WAITING_TIME;
	}
}

void NormalEnemy::AttackStart()
{
	//レイピアの攻撃
	if (weaponType == Weapon::Rapier)
	{
		//攻撃の瞬間に呼び出される
		if (signToAttack)
		{
			//レイピアの攻撃関数を呼び出す
			rapier->Attack(this);
		}
		//アニメーションを繰り返した回数が２回以上なら
		if (CountChangeCounter >= 1)
		{
			//攻撃関数の呼び出しを停止
			signToAttack = false;
			//カウンターのリセット
			CountChangeCounter = 0;
			//エネミーの状態を攻撃終了に遷移する
			enemyStatus = EnemyStatus::AttackEnd;
		}
	}
	if (weaponType == Weapon::None)
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
			if (direction.x == DIRECTION_LEFT)
			{
				animTurnFlg = false;
				move.x = -(NORMAL_WALK_SPEED * ATTACK_SPEED);
			}
			//右向きに攻撃を行う
			if (direction.x == DIRECTION_RIGHT)
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

void NormalEnemy::Death()
{
	move.x = 0.f;
}

void NormalEnemy::Damage()
{
	move.x = 0.f;
	if (damageAnimCount >= 10)
	{
		damageAnimCount = 0;
		enemyStatus = EnemyStatus::Patrol;
	}
}

//アニメーション制御関数
void NormalEnemy::EnemyAnimationManager()
{
	animInterval++;
	//パトロール状態の場合
	if (enemyStatus == EnemyStatus::Patrol)
	{
		PatrolAnim();
	}

	//攻撃準備状態の場合
	if (enemyStatus == EnemyStatus::AttackStandBy)
	{
		AttackStandByAnim();
	}

	//攻撃中の場合
	if (enemyStatus == EnemyStatus::AttackStart)
	{
		NormalEnemyAttackStartAnim();
	}

	//攻撃終了状態の場合
	if (enemyStatus == EnemyStatus::AttackEnd)
	{
		AttackEndAnim();
	}

	//死亡した場合
	if (enemyStatus == EnemyStatus::Death)
	{
		NormalEnemyDeathAnim();
	}

	//ダメージを受けた場合
	if (enemyStatus == EnemyStatus::Damage)
	{
		NormalEnemyDamageAnim();
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

void NormalEnemy::PatrolAnim()
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

void NormalEnemy::AttackStandByAnim()
{
	enemyNumber = 2;
	animCountDown = false;
}

void NormalEnemy::NormalEnemyAttackStartAnim()
{
	signToAttack = true;
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
		CountChangeCounter++;
	}
}

void NormalEnemy::WeaponNoneAttackStartAnim()
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

void NormalEnemy::AttackEndAnim()
{
	enemyNumber = 2;
}

void NormalEnemy::NormalEnemyDeathAnim()
{
	//Deathに遷移した際一度だけ呼ばれる処理
	if (!isFirst)
	{
		//番号をリセット
		enemyNumber = 0;
		isFirst = true;

		//ノックバックを解除
		isKnockBack = false;
	}
	//死亡したら死亡フラグをtrueにする
	if (enemyNumber >= 11)
	{
		//死亡した?：yes
		deathFlg = true;
	}

	//画像番号の更新
	if (animInterval % 5 == 0)
	{
		enemyNumber++;
		
		if (enemyNumber <= 7)
		{
			locYCorrect -= 3.f;
		}
	}
}

void NormalEnemy::NormalEnemyDamageAnim()
{
	//boolがtrueの場合
	if (isChangeDamageAnim)
	{
		enemyNumber = 0;
	}
	//falseの場合
	else
	{
		enemyNumber = 1;
	}

	//９フレームに一度、boolを切り替える
	if (animInterval % 10 == 0)
	{
		isChangeDamageAnim = !isChangeDamageAnim;
		damageAnimCount++;
	}
}