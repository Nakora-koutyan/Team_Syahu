#pragma once
#include "../Collision/Box/BoxCollision.h"
class Map : public BoxCollision
{
private:
	Vector2D Location_1, Location_2;

public:
	Map();
	~Map();
	void Update();
	void Draw()const;
};

