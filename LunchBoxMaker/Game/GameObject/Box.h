#pragma once

#include "DirectXTK\GeometricPrimitive.h"
#include "DirectXTK\SimpleMath.h"
#include <memory>

#include "Game\GameObject\GameObject.h"
#include "Game\Collider\BoxCollider.h"

class Box : public GameObject
{
private:
	static float MOVABLE_AREA_SIZE;

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	DirectX::SimpleMath::Color                   m_color;
	DirectX::SimpleMath::Vector3                 m_velocity;

	std::unique_ptr<BoxCollider>                 m_collider;
	bool                                         m_flag;
public:
	Box();

public:
	~Box();


public:
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;

	void OnCollision(GameObject* object) override;
};

