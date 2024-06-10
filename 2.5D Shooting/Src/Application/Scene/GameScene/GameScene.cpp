#include "GameScene.h"
#include"../SceneManager.h"
#include "../../main.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Gound/Ground.h"
#include "../../GameObject/BackGround/BackGround.h"
#include <string>
#include <fstream>


void GameScene::Event()
{
	if (!isInitGame)
	{
		isInitGame = true;

		AddObject(std::make_shared<Player>(shared_from_this()));

		AddObject(std::make_shared<Ground>(shared_from_this()));

		AddObject(std::make_shared<BackGround>());
	}


	//タイトル遷移
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	

}

void GameScene::Init()
{
	m_camera = std::make_shared<KdCamera>();
	m_camera->SetCameraMatrix(Math::Matrix::CreateTranslation(0, 0, -20));

	KdEffekseerManager::GetInstance().Create(1280, 720);
	KdEffekseerManager::GetInstance().SetCamera(m_camera);

	isInitGame = false;
}

