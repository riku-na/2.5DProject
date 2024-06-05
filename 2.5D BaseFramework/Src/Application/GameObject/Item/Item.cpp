#include "Item.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../../main.h"

Item::Item(std::weak_ptr<GameScene> _owner)
	:m_owner(_owner)
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Item/Item.gltf");

	m_pos = { 0,0,20 };
	m_mWorld = Math::Matrix::Identity;
}

Item::~Item()
{
}

void Item::Update()
{
	std::shared_ptr<GameScene> _owner = m_owner.lock();
	if (_owner)
	{
		m_pos.z -= _owner->GetHighSpeed() * Application::Instance().GetDeltaTime();
	}
}

void Item::DrawUnLit()
{
}
