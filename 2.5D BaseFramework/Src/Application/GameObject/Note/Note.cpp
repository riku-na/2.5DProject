#include "Note.h"
#include "../../Scene/GameScene/GameScene.h"

Note::Note(std::weak_ptr<GameScene> _owner, double _timing, float _speed, Math::Vector2 _pos)
	:m_owner(_owner)
	, m_timing(_timing)
	, m_speed(_speed)
	, m_isJudge(false)
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

			float t = -(std::cos(3.141592 * (1.0f - (leftTime / 2.0f))) - 1) / 2;
			m_cubePos = sPos * (1 - t) + ePos * t;

			m_mWorld = Math::Matrix::CreateTranslation(m_cubePos);
		}
	}
}

void Note::DrawUnLit()
{
	if(-1.0 <= leftTime)
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, Math::Color{ 0,1,0,1 });
}

void Note::DrawBright()
{
}

void Note::DrawSprite()
{


	if (0 <= leftTime && leftTime <= NoteDispTime)
	{
		Math::Color col = { 1,1,1,1.0f - (float)leftTime };
		Math::Color white = { 1,1,1,1 };

		KdShaderManager::Instance().m_spriteShader.DrawCircle(m_pos.x, m_pos.y, 70, &col, false);

		KdShaderManager::Instance().m_spriteShader.DrawCircle(m_pos.x, m_pos.y, 70 * (1.0f - leftTime), &white, false);
	}
}
