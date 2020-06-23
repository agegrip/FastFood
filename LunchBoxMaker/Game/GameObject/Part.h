#pragma once
#include "DirectXTK\GeometricPrimitive.h"
#include "DirectXTK\SimpleMath.h"
#include "GameObject.h"
#include "Game\Collider\BoxCollider.h"

class Bullet : public GameObject
{
public:
	static const float MOVE_SPEED;
	static float MOVABLE_AREA_SIZE;
public:
	Bullet(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth);
	~Bullet();
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;
	void OnCollision(GameObject* object) override;
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	DirectX::SimpleMath::Vector3				 m_velocity;
	DirectX::SimpleMath::Vector3				 m_origin;
	std::unique_ptr<BoxCollider>				 m_collider;
	bool										 m_flag;
};