#pragma once

#include "Game\Collider\Collider.h"

class BoxCollider : public Collider
{
private:
	DirectX::SimpleMath::Vector3 m_size;


public:
	BoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

public:
	~BoxCollider() = default;


public:
	void SetSize(const DirectX::SimpleMath::Vector3& size);
	const DirectX::SimpleMath::Vector3& GetSize() const;
};