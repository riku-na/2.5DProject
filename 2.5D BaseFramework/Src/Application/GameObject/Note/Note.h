#pragma once

class GameScene;

class Note :public KdGameObject
{
public:
	Note(std::weak_ptr<GameScene> _owner,double _timing,float _speed,Math::Vector2 _pos);
	~Note();
	
	void Update()override;

	void DrawUnLit()override;
	void DrawSprite()override;

private:
	std::weak_ptr<GameScene> m_owner;

	const double m_timing;
	const float m_speed;
	Math::Vector3 m_pos;

	bool m_isJudge = false;

	static constexpr float NoteDispTime = 0.5f;
};