#include "BackGround.h"

BackGround::BackGround()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/BackGround/BackGround.gltf");

	m_mWorld = Math::Matrix::CreateScale(15,15,15)*Math::Matrix::CreateTranslation(0, 0, 120);
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
}

void BackGround::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
