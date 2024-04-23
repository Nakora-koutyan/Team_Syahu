#include "Map.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Player/Player.h"

Map::Map() {
	

	location.x = 1000;
	location.y = 1300;

	area.height = 100;
	area.width = 100;
};

Map::~Map() {

};

void Map::Update() {
		//location.x += vector.x;
};

void Map::Draw()const {

	DrawBoxAA
	(
		GetMinScreenLocation().x, GetMinScreenLocation().y,
		GetMaxScreenLocation().x, GetMaxScreenLocation().y,
		0xffffff , FALSE
	);
};