#include"UI.h"
#include"DxLib.h"
#include"../Actor/Character/Player/Player.h"
#include"ResourceManager.h"

UI::UI()
{
	playerHpBarImage.emplace("bar", ResourceManager::GetImage("UI/bar"));
	playerHpBarImage.emplace("barBackground", ResourceManager::GetImage("UI/barBackground"));
	playerHpBarImage.emplace("healthBar", ResourceManager::GetImage("UI/healthBar"));

	for (int i = 0; i < 5; i++)
	{
		stockIcon[i] = Weapon::None;
	}

	playerHpBarLocation.x = 27.f;
	playerHpBarLocation.y = 11.5f;

	selectCount = 0;

	stockImage = ResourceManager::GetImage("UI/stock");
	selectImage[0] = ResourceManager::GetImage("UI/selectStock");
	selectImage[1] = ResourceManager::GetImage("UI/kariSelect");
	largeSwordIcon = ResourceManager::GetImage("UI/LargeSwordStockImage");
	daggerIcon = ResourceManager::GetImage("UI/DaggerStockImage");
	rapierIcon = ResourceManager::GetImage("UI/RapierStockImage");
	
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
		playerHpBarImage.find("barBackground")->second, FALSE);
	DrawExtendGraphF
	(playerHpBarLocation.x, playerHpBarLocation.y,
		playerHpBarLocation.x + playerHp, playerHpBarLocation.y + 21.f,
		playerHpBarImage.find("healthBar")->second, TRUE);
	DrawGraphF(0.f, 2.f, playerHpBarImage.find("bar")->second, TRUE);
}

void UI::PlayerStock() const
{
	for (int i = 0; i < 5; i++)
	{
		DrawGraph(10 + (i * 50), 38, stockImage, TRUE);

		if (stockIcon[i] == Weapon::None)
		{

		}
		else if (stockIcon[i] == Weapon::LargeSword)
		{
			DrawGraph(20 + (i * 50), 48, largeSwordIcon, TRUE);
		}
		else if (stockIcon[i] == Weapon::Dagger)
		{
			DrawGraph(20 + (i * 50), 48, daggerIcon, TRUE);
		}
		else if (stockIcon[i] == Weapon::Rapier)
		{
			DrawGraph(20 + (i * 50), 48, rapierIcon, TRUE);
		}
	}

	decisionFlg ?
		DrawGraph(10 + (selectCount * 50), 38, selectImage[1], TRUE) :
		DrawGraph(10 + (selectCount * 50), 38, selectImage[0], TRUE);
}
