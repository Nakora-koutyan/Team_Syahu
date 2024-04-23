#pragma once
#include "../Collision/Box/BoxCollision.h"
class Map : public BoxCollision
{
private:

public:
	Map();
	~Map();
	void Update();
	void Draw()const;
};

