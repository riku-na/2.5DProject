#include "GameScene.h"
#include"../SceneManager.h"
#include "../../main.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	LogWnd::GetInstance().AddLog((const char*)u8"DeltaTime:%lf", Application::Instance().GetDeltaTime());

}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
}
