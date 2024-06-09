#include "Flick.h"
#include "../../main.h"
#include "../../Scene/GameScene/GameScene.h"

Flick::Flick(std::weak_ptr<GameScene> _owner, double _timing, float _speed, Math::Vector2 _pos)
	:m_owner(_owner)
	,m_timing(_timing)
	,m_speed(_speed)
{
	m_ScrollPolygon = std::make_shared<KdSquarePolygon>();
	m_ScrollPolygon->SetMaterial("Asset/Textures/Test_BaseColor_transparent.png");
	m_ScrollPolygon->SetScale(Math::Vector2{ 30,30 });

	m_FramePolygon = std::make_shared<KdSquarePolygon>();
	m_FramePolygon->SetMaterial("Asset/Textures/Frame_BaseColor_transparent.png");
	m_FramePolygon->SetScale(Math::Vector2{ 30,30 });

	m_pos = Math::Vector3(-15, 5, 10);
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

Flick::~Flick()
{
}

void Flick::Update()
{
	
	static float _uvX = 0;
	static float _uvY = 0;

	auto _owner = m_owner.lock();
	if (_owner)
	{

		_uvX += Application::Instance().GetDeltaTime()*_owner->GetHighSpeed();
		_uvY -= Application::Instance().GetDeltaTime() * _owner->GetHighSpeed();
		LogWnd::GetInstance().AddLog((const char*)u8"UVX:%.2f,UVY:%.2f", _uvX, _uvY);

		m_ScrollPolygon->SetUVRect(Math::Rectangle{ (long)_uvX,(long)_uvY,512,512 });

		double _gameTime = _owner->GetGameTime();

		{
			m_pos.z = _owner->GetHighSpeed() * (m_timing - _gameTime);
		}

		////ワイヤーフレーム
		//std::vector<Math::Vector3> refPos;
		//m_ScrollPolygon->GetPositions(refPos);
		//for (int i = 0; i != refPos.size() - 1; i++)
		//{
		//	m_pDebugWire->AddDebugLine(refPos[i]+m_pos, refPos[i + 1]+m_pos, Math::Color{ 1,0,0,1 });
		//}
	}

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Flick::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_ScrollPolygon, m_mWorld, Math::Color{ 1,0.647,0,0.7f });
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_FramePolygon, m_mWorld, Math::Color{ 1,0.647,0,1.0f });
}

void Flick::DrawBright()
{
	//KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld, Math::Color{ 1,1,0,0.5f});
}
