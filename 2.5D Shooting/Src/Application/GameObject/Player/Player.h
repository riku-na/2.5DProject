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

	const Math::Vector3& GetPosition()const { return m_pos; }

private:
	std::weak_ptr<GameScene>m_owner;

	Math::Vector3 m_pos;
	float xRad = 0;
	float zRad = 0;
	std::shared_ptr<KdModelData> m_model;

	static constexpr float MoveSpeed = 40;
	static constexpr Math::Vector2 MoveArea{ 32,18 };

	static constexpr float TurningSpeedX = DirectX::XMConvertToRadians(90);
	static constexpr float TurningSpeedZ = DirectX::XMConvertToRadians(150);
	static constexpr float MaxTurningRadianX = DirectX::XMConvertToRadians(15);
	static constexpr float MaxTurningRadianZ = DirectX::XMConvertToRadians(30);

	bool isDraw = true;
};