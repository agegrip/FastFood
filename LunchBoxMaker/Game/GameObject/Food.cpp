//======================================================
// File Name	: Food.cpp
// Summary		: 食品オブジェクト
// Date			: 2020/7/01
// Author		: Ryo Irino
//======================================================
#include "Food.h"
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\Common\Utilities.h"
#include "Game\Collider\CollisionManager.h"

const float Food::MOVE_SPEED = 0.05f;
float Food::MOVABLE_AREA_SIZE = 10.0f;

Food::Food(const DirectX::SimpleMath::Vector3& position)
	:GameObject("Food")
	, m_origin(position)
	, m_flag(false)
	, m_velocity(DirectX::SimpleMath::Vector3(MOVE_SPEED, 0, 0))
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateSphere(deviceContext, 0.3f);
	m_position = position;
	m_collider = std::make_unique<SphereCollider>(this, m_scale.x / 5);
}

Food::~Food()
{
}

void Food::Update(float elapsedTime)
{
	m_position.x -= MOVE_SPEED;
	m_position.x = Clamp(m_position.x, -MOVABLE_AREA_SIZE / 2, MOVABLE_AREA_SIZE / 2);
	m_position.z = Clamp(m_position.z, -MOVABLE_AREA_SIZE / 2, MOVABLE_AREA_SIZE / 2);
	GameContext<CollisionManager>::Get()->Add(m_collider.get());
	if ((m_position.z < -MOVABLE_AREA_SIZE / 2) || (m_position.z > MOVABLE_AREA_SIZE / 2))
	{
		Destroy(this);
	}
	if ((m_position.x < -MOVABLE_AREA_SIZE / 2) || (m_position.x > MOVABLE_AREA_SIZE / 2))
	{
		Destroy(this);
	}
	if (m_flag)
	{
		Destroy(this);
	}
}

void Food::Render(const DirectX::SimpleMath::Matrix & viewMatrix, const DirectX::SimpleMath::Matrix & projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_geometricPrimitive->Draw(world, viewMatrix, projectionMatrix, DirectX::Colors::Red);

}

void Food::OnCollision(GameObject * object)
{
	if (object->GetTag() != GetTag())
	{
		m_flag = true;
	}
}
