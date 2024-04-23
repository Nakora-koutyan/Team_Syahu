#include "Map.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Camera/Camera.h"

Map::Map() {
	location.x = 1000.f;
	location.y = 1300.f;

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