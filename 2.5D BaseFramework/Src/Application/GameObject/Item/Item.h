#pragma once

class GameScene;

class Item :public KdGameObject
{
public :
	Item(std::weak_ptr<GameScene> _owner, double _timing, float _speed, Math::Vector2 _pos);
	~Item()override;

	void Update()override;

	void DrawUnLit()override;
	void DrawBright()override;

private:
	std::weak_ptr<GameScene> m_owner;

	const double m_timing;
	const float m_speed;
	Math::Vector3 m_pos;

	bool m_isGet = false;

	std::shared_ptr<KdModelData>m_model;
};