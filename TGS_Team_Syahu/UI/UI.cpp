#include"UI.h"
#include"../Actor/Character/Player/Player.h"
#include"../ResourceManager/ResourceManager.h"

UI::UI()
{
	for (int i = 0; i < 5; i++)
	{
		stockIcon[i] = Weapon::None;
		playerDaggerCnt[i] = PLAYER_WEAPON_DURABILITY;
		playerWeaponDurability[i] = PLAYER_WEAPON_DURABILITY;
	}

	playerHpBarLocation.x = 27.f;
	playerHpBarLocation.y = 11.5f;
	playerLocation.x = 0.f;
	playerLocation.y = 0.f;

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
	playerLocation.x = player->GetCenterScreenLocation().x;
	playerLocation.y = player->GetMinScreenLocation().y;

	selectCount = player->GetStockCount();

	playerWeaponDurability[selectCount] = player->GetWeaponDurability(player->GetStockCount()) / 2;

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

	PlayerEquipmentWeapon();

	Button();
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
		DrawGraph(20 + (i * 50), 38, ResourceManager::GetImage("UI/stock"), TRUE);

		if (stockIcon[i] == Weapon::None)
		{

		}
		else if (stockIcon[i] == Weapon::LargeSword)
		{
			DrawGraph(30 + (i * 50), 48, ResourceManager::GetImage("UI/largeSword"), TRUE);
		}
		else if (stockIcon[i] == Weapon::Dagger)
		{
			DrawGraph(30 + (i * 50), 48, ResourceManager::GetImage("UI/dagger"), TRUE);
			SetFontSize(14);
			DrawFormatString(30 + (i * 50) + 23, 66, 0xffffff, "%d", playerDaggerCnt[i] + 1);
			SetFontSize(16);
		}
		else if (stockIcon[i] == Weapon::Rapier)
		{
			DrawGraph(30 + (i * 50), 48, ResourceManager::GetImage("UI/rapier"), TRUE);
		}
	}

	decisionFlg ?
		DrawGraph(20 + (selectCount * 50), 38, ResourceManager::GetImage("UI/kariSelect"), TRUE) :
		DrawGraph(20 + (selectCount * 50), 38, ResourceManager::GetImage("UI/selectStock"), TRUE);
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

void UI::PlayerEquipmentWeapon() const
{
	if (decisionFlg)
	{
		if (stockIcon[selectCount] == Weapon::LargeSword)
		{
			DrawGraphF(playerLocation.x - 16.f, playerLocation.y - 55.f, ResourceManager::GetImage("UI/largeSword"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + 50.f) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/barBackground"), FALSE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + playerWeaponDurability[selectCount]) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/durabilityBar"), TRUE);
		}
		else if (stockIcon[selectCount] == Weapon::Dagger)
		{
			DrawGraphF(playerLocation.x - 16.f, playerLocation.y - 55.f, ResourceManager::GetImage("UI/dagger"), TRUE);
			DrawFormatStringF(playerLocation.x - 5.f, playerLocation.y - 20.f, 0xffffff, "%d", playerDaggerCnt[selectCount] + 1);
		}
		else if (stockIcon[selectCount] == Weapon::Rapier)
		{
			DrawGraphF(playerLocation.x - 16.f, playerLocation.y - 55.f, ResourceManager::GetImage("UI/rapier"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + 50.f) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/barBackground"), FALSE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + playerWeaponDurability[selectCount]) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/durabilityBar"), TRUE);
		}
	}
}

void UI::Button() const
{
	//Button
	DrawGraph(SCREEN_WIDTH - 180, SCREEN_HEIGHT - 180, ResourceManager::GetImage("UI/ButtonA"), TRUE);
	DrawGraph(SCREEN_WIDTH - 180, SCREEN_HEIGHT - 120, ResourceManager::GetImage("UI/ButtonB"), TRUE);
	DrawGraph(SCREEN_WIDTH - 230, SCREEN_HEIGHT - 60, ResourceManager::GetImage("UI/ButtonX"), TRUE);
	DrawGraph(SCREEN_WIDTH - 180, SCREEN_HEIGHT - 60, ResourceManager::GetImage("UI/ButtonY"), TRUE);
	//String
	DrawGraph(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 65, ResourceManager::GetImage("UI/Attack"), TRUE);
	DrawGraph(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 185, ResourceManager::GetImage("UI/Jump"), TRUE);
	DrawGraph(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 125, ResourceManager::GetImage("UI/Steal"), TRUE);
	//LR
	DrawGraph(0, 75, ResourceManager::GetImage("UI/ButtonLB"), TRUE);
	DrawGraph(225, 75, ResourceManager::GetImage("UI/ButtonRB"), TRUE);
}
