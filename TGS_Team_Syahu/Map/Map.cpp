#include "Map.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Camera/Camera.h"

Map::Map() {
	Location_1.x = 1000;
	Location_1.y = 520;
	Location_2.x = 1100;
	Location_2.y = 620;

	location.x = 1000.f;
	location.y = 520.f;

	area.width = 100.f;
	area.height = 100.f;
};

Map::~Map() {

};

void Map::Update() {
		//location.x += vector.x;
	screenLocation = Camera::ConvertScreenPosition(location);
};

void Map::Draw()const {

	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		GetMaxScreenLocation().x, GetMaxScreenLocation().y,
		0xffffff , FALSE
	);
};