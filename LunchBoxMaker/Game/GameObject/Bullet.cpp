//
// Bullet.cpp
//
#include "Bullet.h"
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\Common\Utilities.h"
#include "Game\Collider\CollisionManager.h"

const float Bullet::MOVE_SPEED = 0.2f;
float Bullet::MOVABLE_AREA_SIZE = 5.0f;

Bullet::Bullet(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth, const std::string& objectname)
	:GameObject(objectname)
	,m_velocity(azimuth * MOVE_SPEED)
	,m_origin(position)
	,m_flag(false)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateSphere(deviceContext, 0.3f);

	m_position = position;
	m_collider = std::make_unique<SphereCollider>(this, m_scale.x / 5);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float elapsedTime)
{
	m_position += m_velocity;
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

void Bullet::Render(const DirectX::SimpleMath::Matrix & viewMatrix,const DirectX::SimpleMath::Matrix & projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_geometricPrimitive->Draw(world, viewMatrix, projectionMatrix, DirectX::Colors::Red);
}

void Bullet::OnCollision(GameObject * object)
{
	if (object->GetTag() != GetTag())
	{
		m_flag = true;
	}
}

