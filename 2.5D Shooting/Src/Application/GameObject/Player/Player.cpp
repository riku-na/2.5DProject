#include "Player.h"
#include "../../main.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../../main.h"

Player::Player(std::weak_ptr<GameScene> _owner)
	:m_owner(_owner)
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Player/ship.gltf");
	m_mWorld = Math::Matrix::Identity;
	m_pos = { 0,0,0 };

	std::function<void(void)> f = [&] {isDraw = false; };
	ImGuiFunctionButton::GetInstance().RegisterFunction((const char*)u8"非表示", f);

	f = [&] {isDraw = true; };
	ImGuiFunctionButton::GetInstance().RegisterFunction((const char*)u8"表示", f);

	isDraw = true;
}

Player::~Player()
{
}

void Player::Update()
{

	POINT _mousePos = Application::Instance().GetMousePos(false);

	static bool spaceKey = false;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!spaceKey)
		{
			spaceKey = true;

			KdEffekseerManager::GetInstance().Play("Flash.efkefc", m_pos, -0.7f, 2.5f, false);
		}
	}
	else
		spaceKey = false;

	LogWnd::GetInstance().AddLog((const char*)u8"PlayerPos{%.2f,%.2f}", m_pos.x, m_pos.y);

	//移動
	std::shared_ptr<GameScene> _owner = m_owner.lock();
	if (_owner)
	{
		Math::Vector3 _moveVector{ 0,0,0 };

		if (GetAsyncKeyState('W') & 0x8000)
		{
			_moveVector.y += 1;

			xRad -= TurningSpeedX * Application::Instance().GetDeltaTime();

			if (xRad < -MaxTurningRadianX)
				xRad = -MaxTurningRadianX;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			_moveVector.y -= 1;

			xRad += TurningSpeedX * Application::Instance().GetDeltaTime();

			if (xRad > MaxTurningRadianX)
				xRad = MaxTurningRadianX;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			_moveVector.x += 1;

			zRad -= TurningSpeedZ * Application::Instance().GetDeltaTime();

			if (zRad < -MaxTurningRadianZ)
				zRad = -MaxTurningRadianZ;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			_moveVector.x -= 1;

			zRad += TurningSpeedZ * Application::Instance().GetDeltaTime();

			if (zRad > MaxTurningRadianZ)
				zRad = MaxTurningRadianZ;
		}

		if (!(GetAsyncKeyState('A') & 0x8000) && !(GetAsyncKeyState('D') & 0x8000))
		{
			if (zRad > 0)
				zRad -= TurningSpeedZ * Application::Instance().GetDeltaTime();

			if (zRad < 0)
				zRad += TurningSpeedZ * Application::Instance().GetDeltaTime();

			if (-TurningSpeedZ * Application::Instance().GetDeltaTime() <= zRad && zRad <= TurningSpeedZ * Application::Instance().GetDeltaTime())
				zRad = 0;
		}

		if (!(GetAsyncKeyState('W') & 0x8000) && !(GetAsyncKeyState('S') & 0x8000))
		{
			if (xRad > 0)
				xRad -= TurningSpeedX * Application::Instance().GetDeltaTime();

			if (xRad < 0)
				xRad += TurningSpeedX * Application::Instance().GetDeltaTime();

			if (-TurningSpeedX * Application::Instance().GetDeltaTime() <= xRad && xRad <= TurningSpeedX * Application::Instance().GetDeltaTime())
				xRad = 0;
		}


		_moveVector.Normalize();

		m_pos += _moveVector * MoveSpeed * Application::Instance().GetDeltaTime();

		//範囲制限
		if (m_pos.x > MoveArea.x)
			m_pos.x = MoveArea.x;

		if (m_pos.x < -MoveArea.x)
			m_pos.x = -MoveArea.x;

		if (m_pos.y > MoveArea.y)
			m_pos.y = MoveArea.y;

		if (m_pos.y < -MoveArea.y)
			m_pos.y = -MoveArea.y;

		//カメラ移動
		_owner->GetCamera()->SetCameraMatrix(Math::Matrix::CreateTranslation(m_pos.x * 0.7, m_pos.y * 0.7, -20));
	}

	static float x;
	ImGuiSlider::GetInstance().RegisterSliderFloat("dir", -1, 1, &x);

	Math::Quaternion q = Math::Quaternion::FromToRotation(Math::Vector3{ 0,0,0 }, Math::Vector3{x,0,1});


	m_mWorld = Math::Matrix::CreateFromQuaternion(q) * Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, m_pos.z);
}

void Player::DrawUnLit()
{
	if (isDraw)
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawBright()
{
	if (isDraw)
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld, Math::Color{ 0,1,0,1 }, Math::Vector3{ 10,10,10 });
}
