//
// BoxCollider.cpp
//
#include "Game\Collider\BoxCollider.h"

BoxCollider::BoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size)
	: Collider(owner)
	, m_size(size)
{
}


void BoxCollider::SetSize(const DirectX::SimpleMath::Vector3& size)
{
	m_size = size;
}


const DirectX::SimpleMath::Vector3& BoxCollider::GetSize() const
{
	return m_size;
}
