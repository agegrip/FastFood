//
// CapsuleCollider
//
#include "Game\Collider\CapsuleCollider.h"

CapsuleCollider::CapsuleCollider(GameObject * owner, float radius, DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end)
	: Collider(owner)
	, m_radius(radius)
	, m_start(start)
	, m_end(end)
{
}

float CapsuleCollider::GetRadius() const
{
	return m_radius;
}

void CapsuleCollider::SetRadius(float radius)
{
	m_radius = radius;
}

DirectX::SimpleMath::Vector3 CapsuleCollider::GetStart() const
{
	return m_start;
}

void CapsuleCollider::SetStart(DirectX::SimpleMath::Vector3 start)
{
	m_start = start;
}

DirectX::SimpleMath::Vector3 CapsuleCollider::GetEnd() const
{
	return m_end;
}

void CapsuleCollider::SetEnd(DirectX::SimpleMath::Vector3 end)
{
	m_end = end;
}