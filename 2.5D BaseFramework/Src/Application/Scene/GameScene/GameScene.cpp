#include "GameScene.h"
#include"../SceneManager.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	int fps=60;
	LogWnd::GetInstance().AddLog((const char*)u8"FPS:%d",fps);

}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
}
