#include "Player.h"
#include <memory>
#include "DirectXTK\Keyboard.h"
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\GameObject\GameObjectManager.h"
#include "Game\GameObject\Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(const DirectX::SimpleMath::Vector3& position,float fireInterval)
	:GameObject("Player")
	,m_playerGeometric()
	,m_fireInterval(fireInterval)
	,m_elapsedTime(0.f)
	,m_horizontalAngle(-90.0f)
	,m_isLoading(false)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	// ポジション
	m_position = position;
	// ジオメトリ
	m_playerGeometric = DirectX::GeometricPrimitive::CreateBox(deviceContext, DirectX::SimpleMath::Vector3(1.0f, 2.0f, 1.0f));

	
}

Player::~Player()
{
}

void Player::Update(float elapsedTime)
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	m_horizontalAngle = mouseState.x;
	if (m_isLoading)
	{
		m_elapsedTime += elapsedTime;
		if (m_elapsedTime > m_fireInterval)
		{
			m_isLoading = false;
		}
	}
	if (!m_isLoading)
	{
		if (mouseState.leftButton)
		{
			Fire();
		}
	}
}

void Player::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_playerGeometric->Draw(world, viewMatrix, projectionMatrix);
}

void Player::Fire()
 {
	float rad = DirectX::XMConvertToRadians(m_horizontalAngle);
	DirectX::SimpleMath::Vector3 direction(cos(rad), 0.f, sin(rad));
	std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(m_position, direction);
	GameContext<GameObjectManager>::Get()->Add(std::move(bullet));
	m_elapsedTime = 0.f;
	m_isLoading = true;
}