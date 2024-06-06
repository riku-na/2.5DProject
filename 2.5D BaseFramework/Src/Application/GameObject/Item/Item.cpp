#include "Item.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../../main.h"

Item::Item(std::weak_ptr<GameScene> _owner, double _timing, float _speed, Math::Vector2 _pos)
	 : m_owner(_owner)
	, m_timing(_timing)
	, m_speed(_speed)
	, m_isGet(false)
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Item/Item.gltf");

	m_pos = { _pos.x,_pos.y,200 };
	m_mWorld = Math::Matrix::Identity;
}

Item::~Item()
{
}

void Item::Update()
{
	auto _owner = m_owner.lock();

	if (_owner)
	{
		double _gameTime = _owner->GetGameTime();

		{
			m_pos.z = _owner->GetHighSpeed()* (m_timing - _gameTime);
		}
	}

	m_mWorld = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, m_pos.z);
}

void Item::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld,Math::Color(1,1,1,1.0f));
}

void Item::DrawBright()
{
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, Math::Matrix::CreateTranslation(0,0,0),Math::Color(1,1,0,0.5f),Math::Vector3(0,0,0));
}
