#pragma once

class GameScene;

class Flick :public KdGameObject
{
public:
	Flick(std::weak_ptr<GameScene> _owner, double _timing, float _speed, Math::Vector2 _pos);
	~Flick()override;

	void Update()override;

	void DrawUnLit()override;
	void DrawBright()override;

private:
	std::weak_ptr<GameScene> m_owner;

	std::shared_ptr<KdSquarePolygon> m_ScrollPolygon;
	std::shared_ptr<KdSquarePolygon> m_FramePolygon;
	Math::Vector3 m_pos;

	const double m_timing;
	const float m_speed;

	double leftTime;
};