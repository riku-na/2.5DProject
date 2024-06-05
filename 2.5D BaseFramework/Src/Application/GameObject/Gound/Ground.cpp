#include "Ground.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../../main.h"

Ground::Ground(std::weak_ptr<GameScene> _owner)
	:m_owner(_owner)
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Ground.gltf");

	m_pos = { 0,-10,0 };
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

Ground::~Ground()
{
}

void Ground::Update()
{
	std::shared_ptr<GameScene> _owner = m_owner.lock();
	if (_owner)
	{
		m_pos.z -= _owner->GetHighSpeed() * Application::Instance().GetDeltaTime();

		if (m_pos.z < -20)
			m_pos.z += 20;
	}

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Ground::DrawUnLit()
{
	for (int i = -1; i < 2; i++)
		for (int j = 0; j < 7; j++)
			KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld * Math::Matrix::CreateTranslation(20 * i, 0, 20 * j), Math::Color{ 1,1,1,1 });
}

void Ground::DrawBright()
{
	for (int i = -1; i < 2; i++)
		for (int j = 0; j < 7; j++)
			KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld * Math::Matrix::CreateTranslation(20 * i, 0, 20 * j), Math::Color{ 0,0,1,1 }, Math::Vector3{ 0,0,1 });
}
