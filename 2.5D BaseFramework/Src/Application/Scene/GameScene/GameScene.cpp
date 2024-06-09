#include "GameScene.h"
#include"../SceneManager.h"
#include "../../main.h"
#include "../../GameObject/Player/Player.h"
#include "../../GameObject/Gound/Ground.h"
#include "../../GameObject/BackGround/BackGround.h"
#include <string>
#include <fstream>
#include "../../GameObject/Note/Note.h"
#include "../../GameObject/Item/Item.h"
#include "../../GameObject/Flick/Flick.h"

void GameScene::Event()
{
	if (!isInitGame)
	{
		isInitGame = true;

		AddObject(std::make_shared<Player>(shared_from_this()));

		AddObject(std::make_shared<Ground>(shared_from_this()));

		AddObject(std::make_shared<BackGround>());

		//AddObject(std::make_shared<Flick>(shared_from_this(), 0,0, Math::Vector2{0,0}));

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
		if (!enterKeyFlag)
		{
			enterKeyFlag = true;
			UnPauseGame();
		}
	}
	else
		enterKeyFlag = false;

	//ゲームストップ
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!spaceKeyFlag)
		{
			spaceKeyFlag = true;
			if (!isStartGame)
			{
				isStartGame = true;

				StartGame();
			}
			else
			{
				PauseGame();
			}
		}
	}
	else
		spaceKeyFlag = false;

	if (m_isPlaying)
	{
		m_gameTime += Application::Instance().GetDeltaTime();

	
	}

	LogWnd::GetInstance().AddLog((const char*)u8"GameTime:%lf", m_gameTime);

}

void GameScene::Init()
{
	m_camera = std::make_shared<KdCamera>();
	m_camera->SetCameraMatrix(Math::Matrix::CreateTranslation(0, 0, -20));

	KdEffekseerManager::GetInstance().Create(1280, 720);
	KdEffekseerManager::GetInstance().SetCamera(m_camera);

	isInitGame = false;
	isStartGame = false;
}

void GameScene::PauseGame()
{
	m_isPlaying = false;
}

void GameScene::UnPauseGame()
{
	m_isPlaying = true;
}

void GameScene::StartGame()
{
	m_isPlaying = true;

	LoadChart();

	auto it = m_notes.begin();
	while (it != m_notes.end())
	{
		switch ((*it)->m_objType)
		{
		case NoteType::Note:
			AddObject(std::make_shared<Note>(shared_from_this(), (*it)->m_timing, (*it)->m_speed, (*it)->m_pos));
			break;

		case NoteType::Item:
			AddObject(std::make_shared<Item>(shared_from_this(), (*it)->m_timing, (*it)->m_speed, (*it)->m_pos));
			break;

		case NoteType::Flick:
			AddObject(std::make_shared<Flick>(shared_from_this(), (*it)->m_timing, (*it)->m_speed, (*it)->m_pos));
			break;
		}
		it++;
	}
}

void GameScene::LoadChart()
{
	std::ifstream file("Asset/Data/Chart/test.csv");
	std::string line;


	if (file.is_open())
	{
		while (getline(file, line))
		{
			std::stringstream ss(line);
			std::string value;

			NoteType _objType;
			double _timing;
			float _speed;
			Math::Vector2 _pos;

			int count = 0;

			while (getline(ss, value, ','))
			{
				if (count == 0)
				{
					switch (stoi(value))
					{
					case 0:
						_objType=NoteType::Note;
						break;

					case 1:
						_objType = NoteType::Flick;
						break;

					case 2:
						_objType = NoteType::Item;
						break;

					case 3:
						_objType = NoteType::DamageShot;
						break;
					}
				}
				else if (count == 1)
				{
					_timing = std::stod(value);
				}
				else if(count==2)
				{
					_speed = std::stof(value);
				}
				else if (count == 3)
				{
					_pos.x = std::stof(value);
				}
				else if (count == 4)
				{
					_pos.y = std::stof(value);
				}
				count++;
			}

			m_notes.push_back(std::make_unique<NoteObject>(_objType, _timing, _speed,_pos));
		}
		file.close();
	}
	else
	{
		//"ファイルを開けませんでした。"
	}
}
