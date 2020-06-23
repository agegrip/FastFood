#pragma once
#include "DirectXTK\GeometricPrimitive.h"
#include "DirectXTK\SimpleMath.h"
#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Player : public GameObject
{
public:
	Player(const DirectX::SimpleMath::Vector3& position,float fireInterval);
	~Player();
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;
	void Fire();
private:
	float m_elapsedTime;
	float m_fireInterval;
	bool  m_isLoading;
	float m_horizontalAngle;
	std::unique_ptr<DirectX::GeometricPrimitive> m_playerGeometric;
};