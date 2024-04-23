#include "StageBlock.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Camera/Camera.h"

StageBlock::StageBlock() {
	location.x = 1000.f;
	location.y = 1240.f;

	area.width = 100.f;
	area.height = 100.f;
};

StageBlock::~StageBlock() {

};

void StageBlock::Update() {
	screenLocation = Camera::ConvertScreenPosition(location);

};

void StageBlock::Draw()const {

	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		GetMaxScreenLocation().x, GetMaxScreenLocation().y,
		0xffffff , FALSE
	);
};