#pragma once

#include "DirectXTK\GeometricPrimitive.h"
#include "DirectXTK\SimpleMath.h"
#include "Game\GameObject\GameObject.h"
#include "Game\Collider\BoxCollider.h"

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)override;
	void OnCollision(GameObject* object) override;
	void IsSitting();
private:
	float m_elapsedTime;
	std::unique_ptr<DirectX::GeometricPrimitive> m_enemyGeometric;
	std::unique_ptr<BoxCollider>				 m_collider;
	bool										 m_flag;
	bool										 m_siting;
};