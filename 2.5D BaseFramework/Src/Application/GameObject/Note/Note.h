#pragma once

class GameScene;

class Note :public KdGameObject
{
public:
	Note(std::weak_ptr<GameScene> _owner,double _timing,float _speed,Math::Vector2 _pos);
	~Note()override;
	
	void Update()override;

	void DrawUnLit()override;
	void DrawBright()override;

	void DrawSprite()override;

private:
	std::weak_ptr<GameScene> m_owner;

	std::shared_ptr<KdModelData> m_model;

	const double m_timing;
	const float m_speed;
	Math::Vector3 m_pos;

	Math::Vector3 m_cubePos;

	double leftTime;

	bool m_isJudge = false;

	static constexpr float NoteDispTime = 1.0f;

	const Math::Vector3 sPos ;
	const Math::Vector3 ePos ;
};