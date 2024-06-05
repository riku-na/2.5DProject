#pragma once

class GameScene;

class Ground :public KdGameObject
{
public:
	Ground(std::weak_ptr<GameScene> _owner);
	~Ground();

	void Update()override;

	void DrawUnLit()override;
	void DrawBright()override;

private:
	std::weak_ptr<GameScene>m_owner;

	std::shared_ptr<KdModelData> m_model;

	Math::Vector3 m_pos;
};