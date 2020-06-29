//
// CapsuleCollider.h
//
#pragma once

#include "Game\Collider\Collider.h"

class CapsuleCollider : public Collider
{
private:
	DirectX::SimpleMath::Vector3 m_start;
	DirectX::SimpleMath::Vector3 m_end;
	float m_radius;
public:
	CapsuleCollider(GameObject* owner, float radius, DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end);
	~CapsuleCollider() = default;

public:
	float GetRadius() const;
	void SetRadius(float radius);
	DirectX::SimpleMath::Vector3 GetStart() const;
	void SetStart(DirectX::SimpleMath::Vector3 start);
	DirectX::SimpleMath::Vector3 GetEnd() const;
	void SetEnd(DirectX::SimpleMath::Vector3 end);
};
