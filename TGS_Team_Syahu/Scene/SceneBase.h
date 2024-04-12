#pragma once
#include"DxLib.h"

class SceneBase 
{
public:
	//デストラクタ
	virtual ~SceneBase() {};

	//更新
	virtual SceneBase* Update() = 0;

	//描画
	virtual void Draw()const = 0;
};