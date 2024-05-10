#include"SceneManager/SceneManager.h"

//プログラムの開始
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	try
	{
		SceneManager sceenManager;

		sceenManager.Initialize();

		sceenManager.Update();

		sceenManager.Finalize();
	}
	catch (const char* errorLog)
	{
		OutputDebugString(_T(errorLog));

		return -1;
	}

	return 0;
}