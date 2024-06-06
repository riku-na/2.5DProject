#include "Note.h"
#include "../../Scene/GameScene/GameScene.h"

Note::Note(std::weak_ptr<GameScene> _owner, double _timing, float _speed, Math::Vector2 _pos)
	:m_owner(_owner)
	, m_timing(_timing)
	, m_speed(_speed)
	, m_isJudge(false)
{
	auto _gameScene = m_owner.lock();

	if (_gameScene)
	{
		_gameScene->GetCamera()->ConvertWorldToScreenDetail(Math::Vector3{_pos.x,_pos.y,0}, m_pos);
	}
}

Note::~Note()
{
}

void Note::Update()
{
}

void Note::DrawUnLit()
{
}

void Note::DrawSprite()
{
	auto _owner = m_owner.lock();

	if (_owner)
	{
		double _gameTime = _owner->GetGameTime();

		if (m_timing - _gameTime <= NoteDispTime&& m_timing - _gameTime >0)
		{
			Math::Color col = { 1,1,1,-0.5f+ (float)(m_timing - _gameTime) };
			KdShaderManager::Instance().m_spriteShader.DrawCircle(m_pos.x, m_pos.y, 30, &col, true);
		}
	}
}
