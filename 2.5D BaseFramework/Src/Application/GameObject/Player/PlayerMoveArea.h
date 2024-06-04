#pragma once

class PlayerMoveArea :public KdGameObject
{
public:
	PlayerMoveArea();
	~PlayerMoveArea()override;

	void DrawUnLit()override;
private:
	std::shared_ptr<KdModelData> m_model;
};