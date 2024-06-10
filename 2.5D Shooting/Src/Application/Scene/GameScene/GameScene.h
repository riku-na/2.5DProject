#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene, public std::enable_shared_from_this<GameScene>
{
public:

	GameScene() { Init(); }
	~GameScene() {}
private:
	void Event() override;
	void Init() override;

	bool isInitGame = false;
};
