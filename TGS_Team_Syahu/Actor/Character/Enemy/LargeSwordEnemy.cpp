#include "LargeSwordEnemy.h"
#include "../../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

#define MAX_WAITING_TIME		87		//攻撃開始までの待機時間(MAX値)
#define LARGE_WALK_SPEED		2.5f	//徘徊時のスピード

#define RUSH_ATTACK_SPEED		5.f		//突進攻撃時の速度

#define MAX_REST_TIME			60		//休息時間
#define MAX_ATTACK_COUNT_DOWN	31		//
#define LARGE_SWORD_KNOCKBACK	5		//ノックバック時間

#define MAX_ATTACK_TIME			87		//大剣の攻撃時間
#define MAX_RUSH_ATTACKTIME		30		//突進攻撃の時間

#define LARGESWORD_ATTACKRANGE_X	60	//大剣の攻撃範囲(X)
#define LARGESWORD_ATTACKRANGE_Y	60	//大剣の攻撃範囲(Y)

#define MAX_ATTACK_CHARGE_TIME		60	//攻撃までの最大の貯め時間

//コンストラクタ
LargeSwordEnemy::LargeSwordEnemy():largeSwordEnemyImage(),largeSwordEnemyImageNumber(0),animInterval(0),animCountDown(false),animTurnFlg(true),
distance(0),restTime(0),attackCountDown(0),didAttack(false),canAttack(false),correctLocX(0), largeSwordCollisionBox(nullptr),once(false),
rushAttackTime(0),largeSwordAttackTime(0),weaponNoneEnemyImage{NULL},weaponNoneEnemyImageNumber(0),signToAttack(false),closeToPlayer(false),
attackChargeTime(0)
{
}

//デストラクタ
LargeSwordEnemy::~LargeSwordEnemy()
{
}

//変数などの初期化
void LargeSwordEnemy::Initialize()
{
	/** アニメーション画像に関する初期化 **/
	//大剣装備時のアニメーション
	largeSwordEnemyImageNumber = 0;
	//画像を仮格納するための配列
	int largeSwordEnemyImageOld[115];
	LoadDivGraph("Resource/Images/Enemy/NightBorne.png", 115, 23, 5, 240, 240, largeSwordEnemyImageOld);
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
		largeSwordEnemyImage[largeSwordEnemyImageNumber] = largeSwordEnemyImageOld[i];
		largeSwordEnemyImageNumber++;
	}

	//大剣を奪われている状態の際のアニメーション
	weaponNoneEnemyImageNumber = 0;
	//画像を仮格納するための配列
	int weaponNoneEnemyImageOld[115];
	LoadDivGraph("Resource/Images/Enemy/NightBorneWeaponNone.png", 115, 23, 5, 240, 240, weaponNoneEnemyImageOld);
	for (int i = 0; i < 115; i++)
	{
		//画像が存在しない部分を読み込まない
		if ((8 < i && i < 23) ||
			(i == 25 || i==28 )||
			(28 < i && i < 46) ||
			(57 < i && i < 69) ||
			73 < i && i < 92)
		{
			//スキップ
			continue;
		}
		weaponNoneEnemyImage[weaponNoneEnemyImageNumber] = weaponNoneEnemyImageOld[i];
		weaponNoneEnemyImageNumber++;
	}

	//仮ボックスの色
	colorRed = 255;
	colorGreen = 255;
	colorBlue = 255;

	//サイズ{ x , y }
	area = { 80.f,85.f };
	//表示座標{ x , y }
	location = { 1100,GROUND_LINE - area.height };
	
	//自身の持つ武器
	weaponType = Weapon::LargeSword;	//大剣
	enemyType = EnemyType::LargeSwordEnemy;

	//プレイヤーを見つけた際のマーク
	findMark = LoadGraph("Resource/Images/Exclamation.png");
	angryMark = LoadGraph("Resource/images/Angry.png");

	//体の向き
	direction.x = DIRECTION_LEFT;

	//体力
	hp = 130.f;

	//攻撃状態に入る範囲
	attackRange[0].x = GetMinLocation().x - 250.f;
	attackRange[0].y = GetCenterLocation().y;
	attackRange[1].x = GetMaxLocation().x + 250.f;
	attackRange[1].y = GetCenterLocation().y;

	//プレイヤーに攻撃を仕掛ける範囲
	attackCenser[0].x = GetMinLocation().x - 270.f;
	attackCenser[0].y = GetMinLocation().y - 25;
	attackCenser[1].x = GetMaxLocation().x + 270.f;
	attackCenser[1].y = GetMaxLocation().y + 25;

	/*　状態　*/
	//表示するか?
	isShow = true;

	damage = 5.f;

	//攻撃時間
	attackWaitingTime = MAX_WAITING_TIME;
	statusChangeTime = MAX_COOL_TIME;

	correctLocX = 50.f;

	//エネミーの状態(徘徊状態にする)
	enemyStatus = Patrol;

	//画像番号
	largeSwordEnemyImageNumber = 0;
	weaponNoneEnemyImageNumber = 0;

	//方向を切り替える前の休息時間
	restTime = MAX_REST_TIME;

	//攻撃までのカウントダウン
	attackCountDown = MAX_ATTACK_COUNT_DOWN;
	animTurnFlg = true;

	/** 攻撃時間 **/
	//大剣
	largeSwordAttackTime = MAX_RUSH_ATTACKTIME;
	//突進
	rushAttackTime = MAX_ATTACK_TIME;

	//攻撃開始までの貯め時間の設定
	attackChargeTime = MAX_ATTACK_CHARGE_TIME;

	//大剣を呼び出す
	largeSwordCollisionBox = new BoxCollision;
	largeSwordCollisionBox->SetArea({ 60,150 });
}

//描画以外の更新
void LargeSwordEnemy::Update()
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = Camera::ConvertScreenPosition(location);
	DamageInterval(FPS * 0.5);
	KnockBack(this,FPS * 0.5, knockBackMove);

	//エネミーアニメーション
	EnemyAnimationManager();

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

	//アニメーションの画像のX座標のずれを修正
	if (animTurnFlg)
	{
		//左向き
		correctLocX = 45.f;
		largeSwordCollisionBox->SetLocationX(GetMinLocation().x - GetArea().width);
	}
	else
	{
		//右向き
		correctLocX = 30.f;
		largeSwordCollisionBox->SetLocationX(GetMaxLocation().x);
	}

	largeSwordCollisionBox->SetLocationY(location.y - 60.f);

	largeSwordCollisionBox->SetScreenLocation(Camera::ConvertScreenPosition(largeSwordCollisionBox->GetLocation()));

	//移動処理
	location.x += move.x;

	//画面端を越えない
	DontCrossBorder();
}

//描画に関する更新
void LargeSwordEnemy::Draw() const
{
	//画像描画
	//大剣を所持している際
	if (weaponType == Weapon::LargeSword)
	{
		DrawRotaGraphF(screenLocation.x + correctLocX, screenLocation.y + 15.f, 1, 0,
			largeSwordEnemyImage[largeSwordEnemyImageNumber], TRUE, animTurnFlg);
	}
	//武器を取られている場合
	if (weaponType == Weapon::None)
	{
		DrawRotaGraphF(screenLocation.x + correctLocX, screenLocation.y + 15.f, 1, 0,
			weaponNoneEnemyImage[weaponNoneEnemyImageNumber], TRUE, animTurnFlg);
	}

	//デバッグ用文字列
	DrawFormatStringF(50.f, 300.f, 0xff0000, "colorRed %d", colorRed);
	DrawFormatStringF(50.f, 320.f, 0x00ff00, "colorGreen %d", colorGreen);
	DrawFormatStringF(50.f, 340.f, 0x0000ff, "colorBlue %d", colorBlue);
	DrawFormatStringF(50.f, 360.f, 0xffff00, "enemyImage %d", largeSwordEnemyImageNumber);
	DrawFormatStringF(50.f, 380.f, 0xff00ff, "animInterval %d", animInterval);
	DrawFormatStringF(50.f, 400.f, 0xff00ff, "enemystate %d", enemyStatus);
	DrawFormatStringF(50.f, 420.f, 0x00ff00, "weaponNoneImageNumber %d", weaponNoneEnemyImageNumber);
	DrawBoxAA(largeSwordCollisionBox->GetMinScreenLocation().x, largeSwordCollisionBox->GetMinScreenLocation().y,
		largeSwordCollisionBox->GetMaxScreenLocation().x, largeSwordCollisionBox->GetMaxScreenLocation().y,
		0xff00ff, FALSE);

	if (markStatus != NULL)
	{
		//プレイヤーを発見した場合、状態に応じて符号を表示する
		if (direction.x == DIRECTION_LEFT)
		{
			DrawGraphF(screenLocation.x + 75, screenLocation.y - 30, markStatus, TRUE);
		}
		if (direction.x == DIRECTION_RIGHT)
		{
			DrawGraphF(screenLocation.x - 25, screenLocation.y - 30, markStatus, TRUE);
		}
	}
}

//プレイヤーを見つけた？
void LargeSwordEnemy::FindPlayer(const Player* player)
{
	if ((enemyStatus == EnemyStatus::Patrol ||
		enemyStatus == EnemyStatus::AttackStandBy) &&
		player->GetIsHit() == false)
	{
		if (attackCenser[0].x <= player->GetMaxLocation().x &&
			attackCenser[1].x >= player->GetMinLocation().x &&
			attackCenser[0].y <= player->GetMinLocation().y &&
			attackCenser[1].y >= player->GetMaxLocation().y)
		{
			//方向変化処理
			if (location.x >= player->GetCenterLocation().x)
			{
				//左向き
				direction.x = DIRECTION_LEFT;
				//画像を反転させる
				animTurnFlg = true;
			}
			else
			{
				//右向き
				direction.x = DIRECTION_RIGHT;
				//画像反転無し
				animTurnFlg = false;
			}

			//見つけた？
			isFind = true;
		}
		else
		{
			isFind = false;
		}
	}
	//攻撃準備状態&大剣を持っている場合、接近処理を行う
	if (enemyStatus == EnemyStatus::AttackStandBy && 
		weaponType==Weapon::LargeSword)
	{
		//プレイヤーへの接近処理
		SuddenApproachToPlayer(player);
	}
}

void LargeSwordEnemy::HitWeapon(ObjectBase* object)
{
	CharaBase* target = static_cast<CharaBase*>(object);

	if (signToAttack)
	{
		if (target->GetIsShow() && !target->GetIsHit())
		{
			target->SetKnockBackMove(LARGESWORD_KNOCKBACK);
		}
	}
}

//パトロール処理
void LargeSwordEnemy::EnemyPatrol()
{
	//playerを見つけることが出来ていない場合
	if (isFind == false)
	{
		//左向きの場合
		if (direction.x == DIRECTION_LEFT && restTime <= 0)
		{
			move.x = -LARGE_WALK_SPEED;
			patrolCounter -= LARGE_WALK_SPEED;
			//左に45進んだら向きを右にする
			if (patrolCounter <= -45.f)
			{
				direction.x = DIRECTION_RIGHT;
				animTurnFlg = false;
				restTime = MAX_REST_TIME;
			}
		}
		//右向きの場合
		if (direction.x == DIRECTION_RIGHT && restTime <= 0)
		{
			move.x = LARGE_WALK_SPEED;
			patrolCounter += LARGE_WALK_SPEED;
			//右に45進んだら向きを左にする
			if (patrolCounter >= 45.f)
			{
				direction.x = DIRECTION_LEFT;
				animTurnFlg = true;
				restTime = MAX_REST_TIME;
			}
		}
		if (restTime >= 0)
		{
			restTime--;
			move.x = 0.f;
		}
	}

	//エネミーの状態遷移の処理
	//playerを発見した場合
	if (isFind)
	{
		//攻撃準備の状態にする
		enemyStatus = EnemyStatus::AttackStandBy;
		//方向転換の際の待機時間のリセット
		restTime = MAX_REST_TIME;
		//アニメーション制御用のタイマーをリセット
		animInterval=0;
		if (weaponType == Weapon::None)
		{
			weaponNoneEnemyImageNumber = 6;
		}
	}

	//エネミーの色変更
	if (colorBlue < 255 && colorGreen < 255)
	{
		colorBlue += 15;
		colorGreen += 15;
	}
}

//プレイヤーへの接近処理
void LargeSwordEnemy::SuddenApproachToPlayer(const Player* player)
{
	//プレイヤーと自身の距離を計算
	distance = abs(player->GetCenterLocation().x - GetCenterLocation().x);
	//距離が100以上の場合
	if (abs(distance) > 100 && canAttack == false)
	{
		//左向きの場合
		if (direction.x == DIRECTION_LEFT)
		{
			//画像：左向き
			animTurnFlg = true;
			//速度：4で移動
			move.x = -4.f;
		}
		if (direction.x == DIRECTION_RIGHT)
		{
			//画像：右向き
			animTurnFlg = false;
			//速度：4で移動
			move.x = 4.f;
		}
	}
	else if (distance <= 100)
	{
		canAttack = true;
	}
}

//攻撃準備
void LargeSwordEnemy::AttackStandBy()
{
	//大剣を持っている場合
	if (weaponType == Weapon::LargeSword)
	{
		if (canAttack == true)
		{
			//移動を0にする
			move.x = 0.f;

			attackChargeTime--;
		}
		if (attackChargeTime <= 0)
		{
			//エネミーの状態を「攻撃開始」に遷移する
			enemyStatus = EnemyStatus::AttackStart;

			//貯め時間のリセット
			attackChargeTime = MAX_ATTACK_CHARGE_TIME;
			//プレイヤーに近づいか？(リセット)
			canAttack = false;
		}
	}
	//大剣を持っていない場合
	if (weaponType == Weapon::None)
	{
		if (attackWaitingTime >= 0)
		{
			//攻撃までの時間を減少
			attackWaitingTime--;
			//移動量は０のまま
			move.x = 0.f;
		}
		else if (attackWaitingTime <= 0)
		{
			//攻撃までの準備時間をリセット
			attackWaitingTime = MAX_WAITING_TIME;

			//エネミーの状態を「攻撃開始」に遷移する
			enemyStatus = EnemyStatus::AttackStart;
		}
	}

	//攻撃範囲からプレイヤーが離れた場合
	if (!isFind)
	{
		//パトロール状態にする
		enemyStatus = EnemyStatus::Patrol;
		animInterval = 0;
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
	//大剣を振るう攻撃
	if (weaponType == Weapon::LargeSword)
	{
		//攻撃OK
		signToAttack = true;

		if (!didAttack)
		{
			//カウントダウンが行われている間は動けない(その場で剣をふるう攻撃のため)
			move.x = 0;
		}
	}
	//大剣がない場合は突進攻撃になる
	if (weaponType == Weapon::None)
	{
		//攻撃時間を減算
		rushAttackTime--;

		//突進攻撃の時間
		if (rushAttackTime >= 0)
		{
			if (direction.x == DIRECTION_LEFT)
			{
				move.x = -RUSH_ATTACK_SPEED;
			}
			else if (direction.x == DIRECTION_RIGHT)
			{
				move.x = RUSH_ATTACK_SPEED;
			}
		}
		else if (rushAttackTime <= 0)
		{
			enemyStatus = EnemyStatus::AttackEnd;
		}
	}
	if (didAttack == true)
	{
		//攻撃をしていれば状態を「攻撃終了」に遷移する
		enemyStatus = EnemyStatus::AttackEnd;
	}
}

//攻撃終了
void LargeSwordEnemy::AttackEnd()
{
	enemyStatus = EnemyStatus::Patrol;
	if (weaponType == Weapon::LargeSword)
	{
		signToAttack = false;
		restTime = 0;
		didAttack = false;
		animInterval = 0;
		largeSwordAttackTime = MAX_ATTACK_TIME;
	}
	if (weaponType == Weapon::None)
	{
		move.x = 0.f;
		weaponNoneEnemyImageNumber = 0;
		//カウントダウンをリセット
		rushAttackTime = MAX_RUSH_ATTACKTIME;
	}
}

//アニメーション制御関数
void LargeSwordEnemy::EnemyAnimationManager()
{
	//パトロール時のアニメーション
	if (enemyStatus == EnemyStatus::Patrol)
	{
		PatrolAnim();
	}
	//攻撃準備中のアニメーション
	if (enemyStatus == EnemyStatus::AttackStandBy)
	{
		//大剣を持っている場合のアニメーション
		if (weaponType == Weapon::LargeSword)
		{
			LargeSwordAttackStandByAnim();
		}
		//武器がないときのアニメーション
		if (weaponType == Weapon::None)
		{
			WeaponNoneAttackStandByAnim();
		}
	}
	//攻撃開始時のアニメーション
	if (enemyStatus == EnemyStatus::AttackStart)
	{
		if (weaponType == Weapon::LargeSword)
		{
			LargeSwordAttackStartAnim();
		}
		if (weaponType == Weapon::None)
		{
			WeaponNoneAttackStartAnim();
		}
	}
	animInterval++;
}

//パトロール時のアニメーション
void LargeSwordEnemy::PatrolAnim()
{
	//待機時間が０より大きい場合：待機アニメーション
	if (restTime >= 0)
	{
		//画像番号が８より大きい場合:0にする
		if (largeSwordEnemyImageNumber > 8)
		{
			largeSwordEnemyImageNumber = 0;
		}

		//5フレームに1回
		if (animInterval % 5 == 0)
		{
			//アニメーションを更新
			largeSwordEnemyImageNumber++;
		}
	}
	else if (restTime <= 0)
	{
		if (largeSwordEnemyImageNumber > 14)
		{
			largeSwordEnemyImageNumber = 9;
		}
		if (animInterval % 3 == 0)
		{
			largeSwordEnemyImageNumber++;
		}
	}
}

//大剣を持っているときの攻撃準備アニメーション
void LargeSwordEnemy::LargeSwordAttackStandByAnim()
{
	if (!canAttack)
	{
		//9番目の画像から14番目までを使い回す
		if (largeSwordEnemyImageNumber > 14)
		{
			largeSwordEnemyImageNumber = 9;
		}
		//3フレーム毎にアニメーションを切り替え
		if (animInterval % 3 == 0)
		{
			largeSwordEnemyImageNumber++;
		}
	}
	/** 剣に力を込めている **/
		//攻撃待機時間が０以上の場合
	if (canAttack && attackChargeTime >= 0)
	{
		//画像番号が20以上になった場合
		if (largeSwordEnemyImageNumber >= 20)
		{
			//18番にする
			largeSwordEnemyImageNumber = 18;
		}
		// 5フレーム毎にアニメーションを切り替える
		if (animInterval % 5 == 0)
		{
			largeSwordEnemyImageNumber++;
		}
	}
}
//大剣がない場合の攻撃準備アニメーション
void LargeSwordEnemy::WeaponNoneAttackStandByAnim()
{
	if (weaponNoneEnemyImageNumber >= 8)
	{
		weaponNoneEnemyImageNumber = 6;
	}
	if (animInterval % 3 == 0)
	{
		weaponNoneEnemyImageNumber++;
	}
}

//大剣を持っている場合の攻撃開始アニメーション
void LargeSwordEnemy::LargeSwordAttackStartAnim()
{
	/** 剣を振り下ろす **/
	//攻撃待機時間が０以下になった場合
	//画像番号が26以上なら
	if (largeSwordEnemyImageNumber > 26)
	{
		//画像の番号を15番に設定
		largeSwordEnemyImageNumber = 13;
		//攻撃したかのフラグ変数をtruenにする
		didAttack = true;
	}
	// 7フレーム毎にアニメーションを切り替える
	if (animInterval % 7 == 0 && !didAttack)
	{
		largeSwordEnemyImageNumber++;
	}
}
//大剣をもっていない場合の攻撃開始アニメーション
void LargeSwordEnemy::WeaponNoneAttackStartAnim()
{
	//画像番号のループ
	if (weaponNoneEnemyImageNumber >= 12)
	{
		weaponNoneEnemyImageNumber = 9;
	}
	else if (animInterval % 4 == 0)
	{
		weaponNoneEnemyImageNumber++;
	}

}

//攻撃を持っている場合の攻撃終了アニメーション
void LargeSwordEnemy::LargeSwordAttackEndAnim()
{
}
//攻撃を持っていない場合の攻撃終了アニメーション
void LargeSwordEnemy::WeaponNoneAttackEndAnim()
{
}
