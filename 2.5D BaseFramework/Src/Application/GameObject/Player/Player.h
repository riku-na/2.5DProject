#pragma once

class GameScene;

class Player :public KdGameObject
{
public:
	Player(std::weak_ptr<GameScene> _owner);
	~Player()override;

	void Update()override;

	void DrawUnLit()override;
	void DrawBright()override;

private:
	std::weak_ptr<GameScene>m_owner;

	Math::Vector3 m_pos;
	std::shared_ptr<KdModelData> m_model;

	bool isDraw = true;
};