#pragma once

class GameScene;

class BackGround :public KdGameObject
{
public:
	BackGround();
	~BackGround();

	void Update()override;

	void DrawUnLit()override;

private:
	std::shared_ptr<KdModelData> m_model;
};