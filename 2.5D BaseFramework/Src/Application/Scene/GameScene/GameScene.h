#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene, public std::enable_shared_from_this<GameScene>
{
public:

	GameScene() { Init(); }
	~GameScene() {}

	const Math::Vector2& GetPlayAreaSize()const { return PlayAreaSize; }

	const float& GetHighSpeed()const { return m_highSpeed; }

	const double& GetGameTime()const { return m_gameTime; }

private:
	enum class NoteType
	{
		Note=0,
		Flick=1,
		Item=2,
		DamageShot=3,
	};

	struct NoteObject
	{
		NoteType m_objType;
		double m_timing;
		float m_speed;
		Math::Vector2 m_pos;

		NoteObject(NoteType _type, double _timing, float _speed,Math::Vector2 _pos)
		{
			m_objType = _type;
			m_timing = _timing;
			m_speed = _speed;
			m_pos = _pos;
		}
	};
	std::vector<std::unique_ptr<NoteObject>> m_notes;

	bool m_isPlaying = false;
	double m_gameTime = 0;

	float m_highSpeed = 100.0f;

	void Event() override;
	void Init() override;

	void StartGame();

	void PauseGame();
	void UnPauseGame();

	void LoadChart();

	static constexpr Math::Vector2 PlayAreaSize{ 16,8 };

	bool isInitGame = false;
	bool isStartGame = false;


	bool enterKeyFlag = false;
	bool spaceKeyFlag = false;
};
