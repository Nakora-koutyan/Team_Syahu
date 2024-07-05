#include"UI.h"
#include"../Actor/Character/Player/Player.h"
#include"../ResourceManager/ResourceManager.h"

UI::UI()
{
	for (int i = 0; i < maxIcon; i++)
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
	//プレイヤーの最大HPは100で画像サイズは300なので3倍する
	const float playerHpBarDenormalization = player->GetHp() * 3.f;
	this->playerHp = playerHpBarDenormalization;
	const float attackCoolTimeImageSize = 50.f;
	this->playerAttackCoolTime = attackCoolTimeImageSize - player->GetAttackCoolTime();
	if (playerAttackCoolTime < 0)playerAttackCoolTime = 0;
	playerLocation.x = player->GetCenterScreenLocation().x;
	playerLocation.y = player->GetMinScreenLocation().y;

	selectCount = player->GetStockCount();

	//耐久値は100で画像は50なので1/2倍する
	const int playerWeaponDurabilityDenormalization = player->GetWeaponDurability(player->GetStockCount()) / 2;
	playerWeaponDurability[selectCount] = playerWeaponDurabilityDenormalization;

	for (int i = 0; i < maxIcon; i++)
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
	const float hpBarImageSizeX = 300.f;
	const float hpBarImageSizeY = 21.f;

	DrawExtendGraphF
	(playerHpBarLocation.x, playerHpBarLocation.y,
		playerHpBarLocation.x + hpBarImageSizeX, playerHpBarLocation.y + hpBarImageSizeY,
		ResourceManager::GetImage("UI/barBackground"), FALSE);
	DrawExtendGraphF
	(playerHpBarLocation.x, playerHpBarLocation.y,
		playerHpBarLocation.x + playerHp, playerHpBarLocation.y + hpBarImageSizeY,
		ResourceManager::GetImage("UI/healthBar"), TRUE);
	DrawGraphF(0.f, 2.f, ResourceManager::GetImage("UI/bar"), TRUE);
}

void UI::PlayerStock() const
{
	const int stockIconImageSize = 50;

	for (int i = 0; i < maxIcon; i++)
	{
		DrawGraph(50 + (i * stockIconImageSize), 38, 
			ResourceManager::GetImage("UI/stock"), TRUE);

		if (stockIcon[i] == Weapon::None)
		{

		}
		else if (stockIcon[i] == Weapon::LargeSword)
		{
			DrawGraph(60 + (i * stockIconImageSize), 48, 
				ResourceManager::GetImage("UI/largeSword"), TRUE);
		}
		else if (stockIcon[i] == Weapon::Dagger)
		{
			DrawGraph(60 + (i * stockIconImageSize), 48, 
				ResourceManager::GetImage("UI/dagger"), TRUE);
			SetFontSize(14);
			const int shiftDisplay = 23;
			const int shiftElement = 1;
			DrawFormatString(60 + (i * stockIconImageSize) + shiftDisplay, 66, 0xffffff, 
				"%d", playerDaggerCnt[i] + shiftElement);
			SetFontSize(16);
		}
		else if (stockIcon[i] == Weapon::Rapier)
		{
			DrawGraph(60 + (i * stockIconImageSize), 48, 
				ResourceManager::GetImage("UI/rapier"), TRUE);
		}
	}

	decisionFlg ?
		DrawGraph(50 + (selectCount * stockIconImageSize), 38, 
			ResourceManager::GetImage("UI/kariSelect"), TRUE) :
		DrawGraph(50 + (selectCount * stockIconImageSize), 38, 
			ResourceManager::GetImage("UI/selectStock"), TRUE);
}

void UI::EnemyHPBar(const Vector2D location, const float hp) const
{
	const float hpBarImageSizeX = 100.f;
	const float hpBarImageSizeY = 11.f;
	const float hpBarImageShift = 20.f;

	DrawExtendGraphF
	(location.x - hpBarImageShift, location.y - hpBarImageShift,
		(location.x + hpBarImageSizeX) - hpBarImageShift, 
		(location.y + hpBarImageSizeY) - hpBarImageShift,
		ResourceManager::GetImage("UI/barBackground"), FALSE);
	DrawExtendGraphF
	(location.x - hpBarImageShift, location.y - hpBarImageShift,
		(location.x + hp) - hpBarImageShift, (location.y + hpBarImageSizeY) - hpBarImageShift,
		ResourceManager::GetImage("UI/healthBar"), TRUE);
	DrawExtendGraphF
	(location.x - hpBarImageShift, location.y - hpBarImageShift,
		(location.x + hp) - hpBarImageShift, (location.y + hpBarImageSizeY) - hpBarImageShift,
		ResourceManager::GetImage("UI/barFramEnemy"), TRUE);
}

void UI::PlayerEquipmentWeapon() const
{
	if (decisionFlg)
	{			
		const float barImageShiftX = 25.f;
		const float barImageShiftY = 18.f;
		const float stockImageShiftX = 25.f;
		const float stockImageShiftY = 80.f;
		const float weaponImageShiftX = 16.f;
		const float weaponImageShiftY = 71.f;
		const float barImageSizeX = 50.f;
		const float barImageSizeY = 11.f;

		if (stockIcon[selectCount] == Weapon::LargeSword)
		{
			DrawGraphF(playerLocation.x - stockImageShiftX, playerLocation.y - stockImageShiftY, 
				ResourceManager::GetImage("UI/stock"), TRUE);
			DrawGraphF(playerLocation.x - weaponImageShiftX, playerLocation.y - weaponImageShiftY, 
				ResourceManager::GetImage("UI/largeSword"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
				(playerLocation.x + barImageSizeX) - barImageShiftX, 
				(playerLocation.y + barImageSizeY) - barImageShiftY,
				ResourceManager::GetImage("UI/barBackground"), FALSE);
			DrawExtendGraphF
			(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
				(playerLocation.x + playerWeaponDurability[selectCount]) - barImageShiftX, 
				(playerLocation.y + barImageSizeY) - barImageShiftY,
				ResourceManager::GetImage("UI/durabilityBar"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
				(playerLocation.x + barImageSizeX) - barImageShiftX, 
				(playerLocation.y + barImageSizeY) - barImageShiftY,
				ResourceManager::GetImage("UI/barFram"), TRUE);
		}
		else if (stockIcon[selectCount] == Weapon::Dagger)
		{
			DrawGraphF(playerLocation.x - stockImageShiftX, playerLocation.y - stockImageShiftY, 
				ResourceManager::GetImage("UI/stock"), TRUE);
			DrawGraphF(playerLocation.x - weaponImageShiftX, playerLocation.y - weaponImageShiftY, 
				ResourceManager::GetImage("UI/dagger"), TRUE);
			const float shiftDisplayX = 5.f;
			const float shiftDisplayY = 18.f;
			const int shiftElement = 1;
			DrawFormatStringF(playerLocation.x - shiftDisplayX, playerLocation.y - shiftDisplayY, 
				0xffffff, "%d", playerDaggerCnt[selectCount] + shiftElement);
		}
		else if (stockIcon[selectCount] == Weapon::Rapier)
		{
			DrawGraphF(playerLocation.x - stockImageShiftX, playerLocation.y - stockImageShiftY, 
				ResourceManager::GetImage("UI/stock"), TRUE);
			DrawGraphF(playerLocation.x - weaponImageShiftX, playerLocation.y - weaponImageShiftY, 
				ResourceManager::GetImage("UI/rapier"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
				(playerLocation.x + barImageSizeX) - barImageShiftX, 
				(playerLocation.y + barImageSizeY) - barImageShiftY,
				ResourceManager::GetImage("UI/barBackground"), FALSE);
			DrawExtendGraphF
			(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
				(playerLocation.x + playerWeaponDurability[selectCount]) - barImageShiftX, 
				(playerLocation.y + barImageSizeY) - barImageShiftY,
				ResourceManager::GetImage("UI/durabilityBar"), TRUE);
			DrawExtendGraphF
			(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
				(playerLocation.x + barImageSizeX) - barImageShiftX, 
				(playerLocation.y + barImageSizeY) - barImageShiftY,
				ResourceManager::GetImage("UI/barFram"), TRUE);

		}
	}
}

void UI::PlayerAttackCoolTimeBar() const
{
	if (decisionFlg)
	{
		const float barImageShiftX = 25.f;
		const float barImageShiftY = 29.f;
		const float barImageSizeX = 50.f;
		const float barImageSizeY = 11.f;

		DrawExtendGraphF
		(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
			(playerLocation.x + barImageSizeX) - barImageShiftX, 
			(playerLocation.y + barImageSizeY) - barImageShiftY,
			ResourceManager::GetImage("UI/barBackground"), FALSE);
		DrawExtendGraphF
		(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
			(playerLocation.x + playerAttackCoolTime) - barImageShiftX, 
			(playerLocation.y + barImageSizeY) - barImageShiftY,
			ResourceManager::GetImage("UI/attackCoolTimeBar"), TRUE);
		DrawExtendGraphF
		(playerLocation.x - barImageShiftX, playerLocation.y - barImageShiftY,
			(playerLocation.x + barImageSizeX) - barImageShiftX, 
			(playerLocation.y + barImageSizeY) - barImageShiftY,
			ResourceManager::GetImage("UI/barFram"), TRUE);
	}
}

void UI::Button() const
{
	int shiftDisplayX = 0;
	int shiftDisplayY = 0;

	//ボタン
	shiftDisplayX = 160;
	shiftDisplayY = 160;
	DrawGraph(SCREEN_WIDTH - shiftDisplayX, SCREEN_HEIGHT - shiftDisplayY, 
		ResourceManager::GetImage("UI/ButtonA"), TRUE);
	
	shiftDisplayY = 100;
	DrawGraph(SCREEN_WIDTH - shiftDisplayX, SCREEN_HEIGHT - shiftDisplayY, 
		ResourceManager::GetImage("UI/ButtonB"), TRUE);
	
	shiftDisplayY = 40;
	DrawGraph(SCREEN_WIDTH - shiftDisplayX, SCREEN_HEIGHT - shiftDisplayY, 
		ResourceManager::GetImage("UI/ButtonY"), TRUE);
	
	shiftDisplayX = 210;
	DrawGraph(SCREEN_WIDTH - shiftDisplayX, SCREEN_HEIGHT - shiftDisplayY, 
		ResourceManager::GetImage("UI/ButtonX"), TRUE);
	
	//文字
	shiftDisplayX = 120;
	shiftDisplayY = 65;
	DrawGraph(SCREEN_WIDTH - shiftDisplayX, SCREEN_HEIGHT - shiftDisplayY, 
		ResourceManager::GetImage("UI/Attack"), TRUE);
	
	shiftDisplayY = 185;
	DrawGraph(SCREEN_WIDTH - shiftDisplayX, SCREEN_HEIGHT - shiftDisplayY, 
		ResourceManager::GetImage("UI/Jump"), TRUE);
	
	shiftDisplayY = 125;
	DrawGraph(SCREEN_WIDTH - shiftDisplayX, SCREEN_HEIGHT - 125, 
		ResourceManager::GetImage("UI/Steal"), TRUE);
	
	//LR
	DrawGraph(13, 55, ResourceManager::GetImage("UI/ButtonLB"), TRUE);
	DrawGraph(305, 55, ResourceManager::GetImage("UI/ButtonRB"), TRUE);
}
