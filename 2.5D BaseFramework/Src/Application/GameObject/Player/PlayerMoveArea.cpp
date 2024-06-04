#include "PlayerMoveArea.h"

PlayerMoveArea::PlayerMoveArea()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Player/wall.gltf");
	m_mWorld = Math::Matrix::CreateScale(15, 15, 15);

	//当たり判定用のコライダーを作成
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollision", m_model, KdCollider::TypeEvent);
}

PlayerMoveArea::~PlayerMoveArea()
{
}

void PlayerMoveArea::DrawUnLit()
{
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
