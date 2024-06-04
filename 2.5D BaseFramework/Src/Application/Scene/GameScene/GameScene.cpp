#include "GameScene.h"
#include"../SceneManager.h"
#include "../../main.h"
#include "../../GameObject/Player/Player.h"

void GameScene::Event()
{
	if (!isInitGame)
	{
		isInitGame = true;

		AddObject(std::make_shared<Player>(shared_from_this()));

	}
	

	//タイトル遷移
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	//ゲーム進行
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		m_isPlaying = true;
	}

	//ゲームストップ
	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_isPlaying = false;
	}

	if (m_isPlaying)
	{
		m_gameTime += Application::Instance().GetDeltaTime();
	}

	LogWnd::GetInstance().AddLog((const char*)u8"GameTime:%lf", m_gameTime);

}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetCameraMatrix(Math::Matrix::CreateTranslation(0,0,-20));
}
