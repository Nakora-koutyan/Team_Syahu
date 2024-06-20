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
	playerAttackCoolTime = 0.f;

	decisionFlg = false;
}

UI::~UI()
{

}

void UI::Update(const Player* player)
{
	this->playerHp = player->GetHp() * 3.f;
	this->playerAttackCoolTime = 50.f - player->GetAttackCoolTime();
	if (playerAttackCoolTime < 0)playerAttackCoolTime = 0;
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

	PlayerAttackCoolTimeBar();

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
	//i*[50]は画像サイズ
	for (int i = 0; i < 5; i++)
	{
		DrawGraph(50 + (i * 50), 38, ResourceManager::GetImage("UI/stock"), TRUE);

		if (stockIcon[i] == Weapon::None)
		{

		}
		else if (stockIcon[i] == Weapon::LargeSword)
		{
			DrawGraph(60 + (i * 50), 48, ResourceManager::GetImage("UI/largeSword"), TRUE);
		}
		else if (stockIcon[i] == Weapon::Dagger)
		{
			DrawGraph(60 + (i * 50), 48, ResourceManager::GetImage("UI/dagger"), TRUE);
			SetFontSize(14);
			DrawFormatString(60 + (i * 50) + 23, 66, 0xffffff, "%d", playerDaggerCnt[i] + 1);
			SetFontSize(16);
		}
		else if (stockIcon[i] == Weapon::Rapier)
		{
			DrawGraph(60 + (i * 50), 48, ResourceManager::GetImage("UI/rapier"), TRUE);
		}
	}

	decisionFlg ?
		DrawGraph(50 + (selectCount * 50), 38, ResourceManager::GetImage("UI/kariSelect"), TRUE) :
		DrawGraph(50 + (selectCount * 50), 38, ResourceManager::GetImage("UI/selectStock"), TRUE);
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
	DrawExtendGraphF
	(location.x - 20.f, location.y - 20.f,
		(location.x + hp) - 20.f, (location.y + 11.f) - 20.f,
		ResourceManager::GetImage("UI/barFramEnemy"), TRUE);
}

void UI::PlayerEquipmentWeapon() const
{
	if (decisionFlg)
	{
		if (stockIcon[selectCount] == Weapon::LargeSword)
		{
			DrawGraphF(playerLocation.x - 25.f, playerLocation.y - 80.f, ResourceManager::GetImage("UI/stock"), TRUE);
			DrawGraphF(playerLocation.x - 16.f, playerLocation.y - 71.f, ResourceManager::GetImage("UI/largeSword"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + 50.f) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/barBackground"), FALSE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + playerWeaponDurability[selectCount]) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/durabilityBar"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + 50.f) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/barFram"), TRUE);
		}
		else if (stockIcon[selectCount] == Weapon::Dagger)
		{
			DrawGraphF(playerLocation.x - 25.f, playerLocation.y - 80.f, ResourceManager::GetImage("UI/stock"), TRUE);
			DrawGraphF(playerLocation.x - 16.f, playerLocation.y - 71.f, ResourceManager::GetImage("UI/dagger"), TRUE);
			DrawFormatStringF(playerLocation.x - 5.f, playerLocation.y - 18.f, 0xffffff, "%d", playerDaggerCnt[selectCount] + 1);
		}
		else if (stockIcon[selectCount] == Weapon::Rapier)
		{
			DrawGraphF(playerLocation.x - 25.f, playerLocation.y - 80.f, ResourceManager::GetImage("UI/stock"), TRUE);
			DrawGraphF(playerLocation.x - 16.f, playerLocation.y - 71.f, ResourceManager::GetImage("UI/rapier"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + 50.f) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/barBackground"), FALSE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + playerWeaponDurability[selectCount]) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/durabilityBar"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - 25.f, playerLocation.y - 18.f,
				(playerLocation.x + 50.f) - 25.f, (playerLocation.y + 11.f) - 18.f,
				ResourceManager::GetImage("UI/barFram"), TRUE);

		}
	}
}

void UI::PlayerAttackCoolTimeBar() const
{
	if (decisionFlg)
	{
		DrawExtendGraphF
		(playerLocation.x - 25.f, playerLocation.y - 29.f,
			(playerLocation.x + 50.f) - 25.f, (playerLocation.y + 11.f) - 29.f,
			ResourceManager::GetImage("UI/barBackground"), FALSE);
		DrawExtendGraphF
		(playerLocation.x - 25.f, playerLocation.y - 29.f,
			(playerLocation.x + playerAttackCoolTime) - 25.f, (playerLocation.y + 11.f) - 29.f, 
			ResourceManager::GetImage("UI/attackCoolTimeBar"), TRUE);
		DrawExtendGraphF
		(playerLocation.x - 25.f, playerLocation.y - 29.f,
			(playerLocation.x + 50.f) - 25.f, (playerLocation.y +11.f) - 29.f,
			ResourceManager::GetImage("UI/barFram"), TRUE);
	}
}

void UI::Button() const
{
	//ボタン
	DrawGraph(SCREEN_WIDTH - 160, SCREEN_HEIGHT - 160, ResourceManager::GetImage("UI/ButtonA"), TRUE);
	DrawGraph(SCREEN_WIDTH - 160, SCREEN_HEIGHT - 100, ResourceManager::GetImage("UI/ButtonB"), TRUE);
	DrawGraph(SCREEN_WIDTH - 210, SCREEN_HEIGHT - 40, ResourceManager::GetImage("UI/ButtonX"), TRUE);
	DrawGraph(SCREEN_WIDTH - 160, SCREEN_HEIGHT - 40, ResourceManager::GetImage("UI/ButtonY"), TRUE);
	//文字
	DrawGraph(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 65, ResourceManager::GetImage("UI/Attack"), TRUE);
	DrawGraph(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 185, ResourceManager::GetImage("UI/Jump"), TRUE);
	DrawGraph(SCREEN_WIDTH - 120, SCREEN_HEIGHT - 125, ResourceManager::GetImage("UI/Steal"), TRUE);
	//LR
	DrawGraph(13, 55, ResourceManager::GetImage("UI/ButtonLB"), TRUE);
	DrawGraph(305, 55, ResourceManager::GetImage("UI/ButtonRB"), TRUE);
}
