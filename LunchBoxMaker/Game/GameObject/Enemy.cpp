#include "Enemy.h"
#include <memory>
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\GameObject\GameObjectManager.h"
#include "Game\Collider\CollisionManager.h"

Enemy::Enemy(const DirectX::SimpleMath::Vector3& position)
	:GameObject("Enemy")
	,m_enemyGeometric()
	,m_elapsedTime()
	,m_flag(false)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	// オブジェクト位置
	m_position = position;
	// ジオメトリ作成
	m_enemyGeometric = DirectX::GeometricPrimitive::CreateBox(deviceContext, DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f));
	// コライダー作成
	m_collider = std::make_unique<BoxCollider>(this,DirectX::SimpleMath::Vector3(1.0f,1.0f,1.0f));
}

Enemy::~Enemy()
{

}

void Enemy::Update(float elapsedTime)
{
	GameContext<CollisionManager>::Get()->Add(m_collider.get());
	if (m_flag)
	{
		Destroy(this);
	}
}

void Enemy::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	m_enemyGeometric->Draw(world, viewMatrix, projectionMatrix);
}

void Enemy::OnCollision(GameObject* object)
{
	if (object->GetTag() != GetTag())
	{
		m_flag = true;
	}
}