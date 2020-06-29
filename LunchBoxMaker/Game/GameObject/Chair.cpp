//======================================================
// File Name	: Chair.cpp
// Summary		: 椅子オブジェクト
// Date			: 2020/6/29
// Author		: Ryo Irino
//======================================================
#include "Chair.h"
#include <memory>
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\GameObject\GameObjectManager.h"
#include "Game\Collider\CollisionManager.h"

Chair::Chair(const DirectX::SimpleMath::Vector3 position)
	:GameObject("Chair")
	,m_chairgeometric()
	,m_position(position)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	// ジオメトリ作成
	m_chairgeometric = DirectX::GeometricPrimitive::CreateBox(deviceContext, DirectX::SimpleMath::Vector3(0.8f, 0.3f, 0.8f));
	// コライダー作成
	m_collider = std::make_unique<BoxCollider>(this, DirectX::SimpleMath::Vector3(0.8f, 0.3f, 0.8f));
}

Chair::~Chair()
{
}

void Chair::Update(float elapsedTime)
{
	GameContext<CollisionManager>::Get()->Add(m_collider.get());
}

void Chair::Render(const DirectX::SimpleMath::Matrix & viewMatrix, const DirectX::SimpleMath::Matrix & projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	m_chairgeometric->Draw(world, viewMatrix, projectionMatrix);
}

void Chair::OnCollision(GameObject * object)
{
}
