#include "pch.h"
#include "Game\GameObject\Box.h"
#include <random>
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\Common\Utilities.h"
#include "Game\Collider\CollisionManager.h"

float Box::MOVABLE_AREA_SIZE = 10.0f;


Box::Box()
	: GameObject("Box")
	, m_flag(false)
{
	std::random_device seedGenerator;
	std::mt19937 randomGenerator(seedGenerator());

	std::uniform_real_distribution<float> randPosition(-MOVABLE_AREA_SIZE / 2, MOVABLE_AREA_SIZE / 2);
	float px = randPosition(randomGenerator);
	float pz = randPosition(randomGenerator);
	m_position = DirectX::SimpleMath::Vector3(px, 0.0f, pz);

	std::uniform_real_distribution<float> randVelocity(-0.2f, 0.2f);
	float vx = randVelocity(randomGenerator);
	m_velocity = DirectX::SimpleMath::Vector3(vx, 0.0f, 0.0f);

	std::uniform_int_distribution<> randColor(0, 255);
	float r = static_cast<float>(randColor(randomGenerator)) / 255;
	float g = static_cast<float>(randColor(randomGenerator)) / 255;
	float b = static_cast<float>(randColor(randomGenerator)) / 255;
	float a = 1.0f;
	m_color = DirectX::SimpleMath::Color(r, g, b, a);

	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	m_geometricPrimitive = DirectX::GeometricPrimitive::CreateBox(deviceResources->GetD3DDeviceContext(), m_scale);

	//m_collider = std::make_unique<BoxCollider>(this, m_scale);
}



Box::~Box()
{
}



void Box::Update(float elapsedTime)
{

}



void Box::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	DirectX::SimpleMath::Color color = m_color;
	if (m_flag)
	{
		color = DirectX::Colors::Black;
	}
	m_geometricPrimitive->Draw(world, viewMatrix, projectionMatrix, color);
}



void Box::OnCollision(GameObject* object)
{
	if (object->GetTag() != GetTag())
	{
		m_flag = true;
	}
}