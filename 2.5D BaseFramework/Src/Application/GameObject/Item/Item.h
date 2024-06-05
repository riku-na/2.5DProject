#pragma once

class GameScene;

class Item :public KdGameObject
{
public :
	Item(std::weak_ptr<GameScene> _owner);
	~Item()override;

	void Update()override;
	void DrawUnLit()override;

private:
	std::weak_ptr<GameScene>m_owner;

	std::shared_ptr<KdModelData>m_model;
	Math::Vector3 m_pos;
};