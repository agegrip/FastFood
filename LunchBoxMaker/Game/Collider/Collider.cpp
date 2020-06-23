#include "pch.h"

#include "Game\Collider\Collider.h"
#include "Game\GameObject\GameObject.h"


Collider::Collider(GameObject* owner)
	: m_owner(owner)
	, m_offset(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f))
{
}


void Collider::OnCollision(const Collider* object)
{
	m_owner->OnCollision(object->m_owner);
}


const DirectX::SimpleMath::Vector3 Collider::GetPosition() const
{
	return m_owner->GetPosition() + m_offset;
}


const DirectX::SimpleMath::Vector3 Collider::GetOffset() const
{
	return m_offset;
}


void Collider::SetOffset(const DirectX::SimpleMath::Vector3 & offset)
{
	m_offset = offset;
}
