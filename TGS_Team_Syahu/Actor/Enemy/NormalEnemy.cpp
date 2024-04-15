#include "NormalEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

//コンストラクタ
NormalEnemy::NormalEnemy():enemy_color(0),damage_color(0),attack_color(0),usual_color(0),
attack_range{},attack_censer{},hp(100),find_mark(NULL)
{
}

//デストラクタ
NormalEnemy::~NormalEnemy()
{
}

//初期化処理
void NormalEnemy::Initialize()
{
	damage_color = GetColor(255, 0, 0);
	attack_color = GetColor(0, 0, 255);
	usual_color = GetColor(0, 255, 0);

	enemy_color = usual_color;
	
	area = { 90.f,90.f };
	location = { 1200,GROUND_LINE - area.height };
	isShow = true;
	abilityType = Ability::Slashing;	//かり

	attack_range[0] = { GetCenterLocation() };
	attack_range[1] = { GetCenterLocation() };

	attack_censer[0] = { GetCenterLocation() };
	attack_censer[1] = { GetCenterLocation() };

	find_mark = LoadGraph("Resource/Images/Exclamation.png");

	hp = 100;
}

//描画以外の内容を更新
void NormalEnemy::Update(GameMainScene* object)
{
	screenLocation = object->GetCamera()->ConvertScreenPosition(location);

	//エネミーの移動
	EnemyPatrol(object);

	//エネミーの攻撃範囲
	AttackRange();

	//プレイヤーを検知するセンサー
	DiscoveryPlayer();

	//プレイヤーにダメージを与える処理
	//GiveDamage(object);

	DamageInterval(60);

	if (attack_range[0].x < object->GetPlayer()->GetMaxLocation().x &&
		attack_range[1].x > object->GetPlayer()->GetMinLocation().x)
	{
		isAttack = true;
	}
	else
	{
		isAttack = false;
	}
}

//描画に関する更新
void NormalEnemy::Draw() const
{
	//エネミー
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		isAttack ? attack_color : isHit ? 0xff0000 : usual_color, TRUE, 1.0f
	);
	//攻撃範囲表示
	DrawBoxAA
	(
		attack_range[0].x,attack_range[0].y - 45,
		attack_range[1].x,attack_range[1].y + 45,
		GetColor(255,0,255),FALSE,1.f
	);
	DrawFormatStringF(500.f, 550.f, GetColor(255, 0, 255), "%f", GetMinLocation().x);
	
	//プレイヤーを発見した場合、「！」を表示する
	if (isHit == true)
	{
		DrawGraphF
		(
			screenLocation.x + 75, screenLocation.y - 30,
			find_mark, TRUE
		);
	}
}

//プレイヤーのいる方向に向かう
void NormalEnemy::EnemyPatrol(GameMainScene* player)
{
	if (player->GetPlayer()->GetMaxLocation().x + 25 < location.x)
	{
		vector.x = ENEMY_SPEED;
	}
	else if (player->GetPlayer()->GetMinLocation().x - 125 > location.x)
	{
		vector.x = -ENEMY_SPEED;
	}

	if (!player->GetPlayer()->GetParryFlg())
	{
		location.x += vector.x;
	}
}

//攻撃範囲
void NormalEnemy::AttackRange()
{
	attack_range[0] = { GetMinLocation().x - 45.f,GetCenterLocation().y };
	attack_range[1] = { GetMaxLocation().x + 45.f , GetCenterLocation().y };
}

//戦闘態勢に入る範囲
void NormalEnemy::DiscoveryPlayer()
{
	attack_censer[0] = { GetMinLocation().x - 100.f,GetCenterLocation().y };
	attack_censer[1] = { GetMaxLocation().x + 100.f,GetCenterLocation().y };
}

float NormalEnemy::GiveDamage(GameMainScene* player_hp)
{
	hp = player_hp->GetPlayer()->GetHp();
	if (isHit == true)
	{
		hp -= GIVE_DAMAGE;
	}
	return player_hp->GetPlayer()->GetHp();
}