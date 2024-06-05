#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene, public std::enable_shared_from_this<GameScene>
{
public :

	GameScene() { Init(); }
	~GameScene() {}

	const Math::Vector2& GetPlayAreaSize()const { return PlayAreaSize; }

	const float& GetHighSpeed()const { return m_highSpeed; }

private:
	

	bool m_isPlaying = false;
	double m_gameTime = 0;

	float m_highSpeed = 30.0f;

	void Event() override;
	void Init() override;

	static constexpr Math::Vector2 PlayAreaSize{16,8};

	bool isInitGame = false;
};
