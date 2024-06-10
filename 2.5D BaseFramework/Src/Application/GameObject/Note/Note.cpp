#include "Note.h"
#include "../../Scene/GameScene/GameScene.h"

Note::Note(std::weak_ptr<GameScene> _owner, double _timing, float _speed, Math::Vector2 _pos)
	:m_owner(_owner)
	, m_timing(_timing)
	, m_speed(_speed)
	, m_isJudge(false)
	, m_defaultPos(_pos.x, _pos.y, 0)
	, sPos(Math::Vector3{ _pos.x,_pos.y,100 })
	, ePos(Math::Vector3{ _pos.x,_pos.y,5 })
{
	auto _gameScene = m_owner.lock();

	if (_gameScene)
	{
		_gameScene->GetCamera()->ConvertWorldToScreenDetail(Math::Vector3{ _pos.x,_pos.y,0 }, m_pos);
	}

	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Note/Note.gltf");

	m_cubePos = { 30,0,0 };
	m_mWorld = Math::Matrix::CreateTranslation(m_cubePos);

	target_Center = std::make_shared<KdSquarePolygon>();
	target_Center->SetMaterial("Asset/Textures/Target_Center.png");
	targetTex.Load("Asset/Textures/target_large.png");
}

Note::~Note()
{
}

void Note::Update()
{
	auto _owner = m_owner.lock();

	if (_owner)
	{
		double _gameTime = _owner->GetGameTime();

		leftTime = m_timing - _gameTime;
		if (0 <= leftTime && leftTime <= 2.0f)
		{

			/*float t = -(std::cos(3.141592 * (1.0f - (leftTime / 2.0f))) - 1) / 2;
			m_cubePos = sPos * (1 - t) + ePos * t;

			m_mWorld = Math::Matrix::CreateTranslation(m_cubePos);*/
		}

		Math::Vector3 _playerPos = _owner->GetPlayerPos();
		float dist = abs((m_defaultPos.x - _playerPos.x) * (m_defaultPos.x - _playerPos.x)) + abs((m_defaultPos.x - _playerPos.x) * (m_defaultPos.x - _playerPos.x));

		if (dist < RockRadius)
		{
			isRock = true;
		}
		else
		{
			isRock = false;
		}

		LogWnd::GetInstance().AddLog((const char*)u8"dist:%lf", dist);


	}
}

void Note::DrawUnLit()
{
	//if(-1.0 <= leftTime)
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, Math::Color{ 0,1,0,1 });
}

void Note::DrawBright()
{
}

void Note::DrawSprite()
{
	static float scale = 1.0f;
	ImGuiSlider::GetInstance().RegisterSlider("scale", 0.0f, 5.0f, &scale);



	if (-(PerfectTime) <= leftTime && leftTime <= NoteDispTime)
	{
		//Math::Color col = { 1,1,1,1.0f - (float)leftTime/NoteDispTime};
		Math::Color green = { 0,1,0,0.3 };
		Math::Color yellow = { 1,1,0,0.3 };
		Math::Color red = { 1,0,0,0.3 };

		Math::Color drawColor = green;

		float scale = 0.2;

		if (isRock)
		{
			if (abs(leftTime) < PerfectTime)
			{
				drawColor = red;
			}
			else
			{
				drawColor = yellow;
			}

			scale = 0.25;
		}
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(scale) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0));
		KdShaderManager::Instance().m_spriteShader.DrawTex(&targetTex, 0, 0, nullptr, &drawColor);

		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::CreateScale(scale * (1.0 - leftTime / NoteDispTime)) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0));
		drawColor.w = 1.0f - (float)leftTime / NoteDispTime;
		KdShaderManager::Instance().m_spriteShader.DrawTex(&targetTex, 0, 0, nullptr, &drawColor);

		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);

		//KdShaderManager::Instance().m_StandardShader.DrawPolygon(*target_Center, Math::Matrix::CreateTranslation());


	/*	KdShaderManager::Instance().m_spriteShader.DrawCircle(m_pos.x, m_pos.y, 70, &col, false);

		KdShaderManager::Instance().m_spriteShader.DrawCircle(m_pos.x, m_pos.y, 70 * (1.0f - leftTime), &white, false);*/
	}
}
