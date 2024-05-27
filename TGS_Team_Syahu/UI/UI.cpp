#include"UI.h"
#include"DxLib.h"
#include"../Actor/Character/Player/Player.h"
#include"../ResourceManager/ResourceManager.h"

UI::UI()
{
	for (int i = 0; i < 5; i++)
	{
		stockIcon[i] = Weapon::None;
		playerDaggerCnt[i] = PLAYER_WEAPON_DURABILITY;
	}

	playerHpBarLocation.x = 27.f;
	playerHpBarLocation.y = 11.5f;

	selectCount = 0;
	
	playerHp = 0.f;

	decisionFlg = false;
}

UI::~UI()
{

}

void UI::Update(const Player* player)
{
	this->playerHp = player->GetHp() * 3.f;

	selectCount = player->GetStockCount();

	for (int i = 0; i < 5; i++)
	{
		stockIcon[i] = player->GetStock(i);
		if (player->GetStock(i) == Weapon::Dagger)
		{
			playerDaggerCnt[i] = player->GetDaggerCount(i);
		}
	}

	decisionFlg = player->GetIsEquipment();
}

void UI::Draw() const
{
	PlayerHPBar();

	PlayerStock();
}

void UI::PlayerHPBar() const
{
	DrawExtendGraphF
	(playerHpBarLocation.x, playerHpBarLocation.y,
		playerHpBarLocation.x + 300.f, playerHpBarLocation.y + 21.f,
		ResourceManager::GetImage("UI/barBackground"), FALSE);
	DrawExtendGraphF
	(playerHpBarLocation.x, playerHpBarLocation.y,
		playerHpBarLocation.x + playerHp, playerHpBarLocation.y + 21.f,
		ResourceManager::GetImage("UI/healthBar"), TRUE);
	DrawGraphF(0.f, 2.f, ResourceManager::GetImage("UI/bar"), TRUE);
}

void UI::PlayerStock() const
{
	//50は画像サイズ
	for (int i = 0; i < 5; i++)
	{
		DrawGraph(10 + (i * 50), 38, ResourceManager::GetImage("UI/stock"), TRUE);

		if (stockIcon[i] == Weapon::None)
		{

		}
		else if (stockIcon[i] == Weapon::LargeSword)
		{
			DrawGraph(20 + (i * 50), 48, ResourceManager::GetImage("UI/largeSword"), TRUE);
		}
		else if (stockIcon[i] == Weapon::Dagger)
		{
			DrawGraph(20 + (i * 50), 48, ResourceManager::GetImage("UI/dagger"), TRUE);
			DrawFormatString(20 + (i * 50) + 5, 58, 0xffffff, "%d", playerDaggerCnt[i] + 1);
		}
		else if (stockIcon[i] == Weapon::Rapier)
		{
			DrawGraph(20 + (i * 50), 48, ResourceManager::GetImage("UI/rapier"), TRUE);
		}
	}

	decisionFlg ?
		DrawGraph(10 + (selectCount * 50), 38, ResourceManager::GetImage("UI/kariSelect"), TRUE) :
		DrawGraph(10 + (selectCount * 50), 38, ResourceManager::GetImage("UI/selectStock"), TRUE);
}

void UI::EnemyHPBar(const Vector2D location, const float hp) const
{
	DrawExtendGraphF
	(location.x - 20.f, location.y - 20.f,
		(location.x + 100.f) - 20.f, (location.y + 11.f) - 20.f,
		ResourceManager::GetImage("UI/barBackground"), FALSE);
	DrawExtendGraphF
	(location.x - 20.f, location.y - 20.f,
		(location.x + hp) - 20.f, (location.y + 11.f) - 20.f,
		ResourceManager::GetImage("UI/healthBar"), TRUE);
}
