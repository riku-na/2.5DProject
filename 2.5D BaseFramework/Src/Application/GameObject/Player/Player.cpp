#include "Player.h"
#include "../../main.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/GameScene/GameScene.h"
#include "PlayerMoveArea.h"

Player::Player(std::weak_ptr<GameScene> _owner)
	:m_owner(_owner)
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Player/box.gltf");
	m_mWorld = Math::Matrix::Identity;
	m_pos = {};

	//移動用の判定壁生成
	auto _nowScene = m_owner.lock();
	if (_nowScene)
	{
		_nowScene->AddObject(std::make_shared<PlayerMoveArea>());
	}

	std::function<void(void)> f = [&] {isDraw = false; };
	ImGuiFunctionButton::GetInstance().RegisterFunction((const char*)u8"非表示",f);

	 f = [&] {isDraw = true; };
	ImGuiFunctionButton::GetInstance().RegisterFunction((const char*)u8"表示", f);
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

	auto _owner = m_owner.lock();
	if (_owner)
	{
		//レイ情報計算
		KdCollider::RayInfo ray;
		_owner->GetCamera()->GenerateRayInfoFromClientPos(_mousePos, ray.m_pos, ray.m_dir, ray.m_range);

		//当たり判定をしたいタイプを設定
		ray.m_type = KdCollider::TypeEvent;

		//レイに当たったオブジェクト情報を格納するリスト
		std::list<KdCollider::CollisionResult> retRayList;

		//レイと当たり判定
		for (auto& obj : _owner->GetObjList())
		{
			obj->Intersects(ray, &retRayList);
		}

		//レイに当たったリストから一番近いオブジェクトを検出
		float maxOverLap = 0;	//はみ出たレイの長さ
		Math::Vector3 hitPos;	//レイが遮断された座標
		bool isHit = false;		//当たっていたらtrue
		for (auto& ret : retRayList)
		{
			//レイを遮断し、オーバーした長さが一番長いものを探す
			if (maxOverLap < ret.m_overlapDistance)
			{
				maxOverLap = ret.m_overlapDistance;
				hitPos = ret.m_hitPos;
				isHit = true;
			}
		}

		if (isHit)
		{
			//地面に当たっている
			m_pos.x = hitPos.x;
			m_pos.y = hitPos.y;

			//範囲制限
			const Math::Vector2 PlayAreaSize = _owner->GetPlayAreaSize();
			if (m_pos.x > PlayAreaSize.x)
				m_pos.x = PlayAreaSize.x;

			if (m_pos.x < -PlayAreaSize.x)
				m_pos.x = -PlayAreaSize.x;

			if (m_pos.y > PlayAreaSize.y)
				m_pos.y = PlayAreaSize.y;

			if (m_pos.y < -PlayAreaSize.y)
				m_pos.y = -PlayAreaSize.y;
		}
	}

	LogWnd::GetInstance().AddLog((const char*)u8"PlayerPos{%.2f,%.2f}", m_pos.x, m_pos.y);

	m_mWorld = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, m_pos.z);
}

void Player::DrawUnLit()
{
	if (isDraw)
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawBright()
{
	if (isDraw)
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
