//======================================================
// File Name	: Chair.h
// Summary		: 椅子オブジェクト
// Date			: 2020/6/29
// Author		: Ryo Irino
//======================================================
#pragma once
#include "DirectXTK\GeometricPrimitive.h"
#include "DirectXTK\SimpleMath.h"
#include "GameObject.h"
#include "Game\Collider\BoxCollider.h"

class Chair : public GameObject
{
public:
	Chair(const DirectX::SimpleMath::Vector3 position);
	~Chair();
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;

	void OnCollision(GameObject* object) override;
private:
	DirectX::SimpleMath::Vector3				 m_position;
	std::unique_ptr<DirectX::GeometricPrimitive> m_chairgeometric;
	std::unique_ptr<BoxCollider>				 m_collider;	
};