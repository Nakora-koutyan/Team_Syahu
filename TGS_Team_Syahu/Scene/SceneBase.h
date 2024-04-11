#pragma once
#include"DxLib.h"

class SceneBase 
{
public:
	//デストラクタ
	virtual ~SceneBase() {};

	//描画以外の更新を実装する
	virtual SceneBase* Update() = 0;

	//描画に関することを実装する
	virtual void Draw()const = 0;
};