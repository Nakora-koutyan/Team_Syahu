#include "SceneManager.h"

SceneBase* SceenManager::Update()
{
	SceneBase* next_scene;
	try
	{
		next_scene = now_sceen->Update();
		if (next_scene != now_sceen)
		{
			delete now_sceen;
			now_sceen = next_scene;
		}
	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);

		//ファイルオープン
		fopen_s(&fp, "ErrLog.txt", "a");

		//エラーデータの書き込み
		fprintf_s(fp, "%02d年 %02d月 %02d日 %02d時 %02d分 %02d秒 : %sがありません。\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		fclose(fp);	

		return nullptr;
	}

	return now_sceen;
}

void SceenManager::Draw() const
{
	now_sceen->Draw();
}
