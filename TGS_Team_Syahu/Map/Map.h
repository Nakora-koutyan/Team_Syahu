#pragma once
#include "../Collision/Box/BoxCollision.h"
class Map : public BoxCollision
{
private:

public:
	//コンストラクタ
	Map();

	//デストラクタ
	~Map();

	//更新
	void Update();

	//描画
	void Draw()const;
};

