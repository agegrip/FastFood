//
// SphereCollider.cpp
//
#include "Game\Collider\SphereCollider.h"



SphereCollider::SphereCollider(GameObject* owner, float radius)
	: Collider(owner)
	, m_radius(radius)
{
}


void SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
}


float SphereCollider::GetRadius() const
{
	return m_radius;
}
