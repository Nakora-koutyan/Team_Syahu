#include"UI.h"
#include"DxLib.h"
#include"../Actor/Character/Player/Player.h"

UI::UI()
{
	//画像フォルダまでのパス
	std::string imageFilePath = "Resource/Images/UI/";
	//画像のファイルパス
	std::string filePath = "";
	//拡張子
	std::string extension = ".png";

	filePath = imageFilePath + "bar" + extension;
	playerHpBarImage.emplace("bar", LoadGraph(filePath.c_str()));
	if (playerHpBarImage["bar"] == -1)throw;

	filePath = imageFilePath + "bar_background" + extension;
	playerHpBarImage.emplace("bar_background", LoadGraph(filePath.c_str()));
	if (playerHpBarImage["bar_background"] == -1)throw;

	filePath = imageFilePath + "health_bar" + extension;
	playerHpBarImage.emplace("health_bar", LoadGraph(filePath.c_str()));
	if (playerHpBarImage["health_bar"] == -1)throw;

	for (int i = 0; i < 5; i++)
	{
		stockIcon[i] = Weapon::None;
	}

	playerHpBarLocation.x = 27.f;
	playerHpBarLocation.y = 11.5f;

	selectCount = 0;

	filePath = imageFilePath + "stock" + extension;
	stockImage = LoadGraph(filePath.c_str());
	if (stockImage == -1)throw;

	filePath = imageFilePath + "selectStock" + extension;
	selectImage[0] = LoadGraph(filePath.c_str());
	if (selectImage[0] == -1)throw;

	filePath = imageFilePath + "kariSelect" + extension;
	selectImage[1] = LoadGraph(filePath.c_str());
	if (selectImage[1] == -1)throw;

	filePath = imageFilePath + "LargeSwordStockImage" + extension;
	largeSwordIcon = LoadGraph(filePath.c_str());
	if (largeSwordIcon == -1)throw;	
	
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
		playerHpBarImage.find("bar_background")->second, FALSE);
	DrawExtendGraphF
	(playerHpBarLocation.x, playerHpBarLocation.y,
		playerHpBarLocation.x + playerHp, playerHpBarLocation.y + 21.f,
		playerHpBarImage.find("health_bar")->second, TRUE);
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

		}
		else if (stockIcon[i] == Weapon::Rapier)
		{

		}
	}

	decisionFlg ?
		DrawGraph(10 + (selectCount * 50), 38, selectImage[1], TRUE) :
		DrawGraph(10 + (selectCount * 50), 38, selectImage[0], TRUE);
}
