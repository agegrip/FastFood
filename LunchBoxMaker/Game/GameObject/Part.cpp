#include "Part.h"
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\Common\Utilities.h"
#include "Game\Collider\CollisionManager.h"

const float Part::MOVE_SPEED = 0.2f;
float Part::MOVABLE_AREA_SIZE = 10.0f;

Part::Part(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth)
	:GameObject("Part")
	,m_velocity(azimuth*MOVE_SPEED)
	,m_origin(position)
	,m_flag(false)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateSphere(deviceContext, 0.3f);

	m_position = position;
	m_collider = std::make_unique<BoxCollider>(this);
}

Part::~Part()
{
}

void Part::Update(float elapsedTime)
{
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

void Part::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_geometricPrimitive->Draw(world, viewMatrix, projectionMatrix, DirectX::Colors::Red);
}

void Part::OnCollision(GameObject* object)
{
	if (object->GetTag() != GetTag())
	{
		m_flag = true;
	}
}