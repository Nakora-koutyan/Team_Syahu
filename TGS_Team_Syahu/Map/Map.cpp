#include "Map.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Player/Player.h"

Map::Map() {
	Location_1.x = 1000;
	Location_1.y = 520;
	Location_2.x = 1100;
	Location_2.y = 620;
};

Map::~Map() {

};

void Map::Update() {
		//location.x += vector.x;
};

void Map::Draw()const {

	DrawBoxAA
	(
		Location_1.x, Location_1.y,
		Location_2.x, Location_2.y,
		0xffffff , FALSE
	);
};