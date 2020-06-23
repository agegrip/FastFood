#pragma once

#include "DirectXTK\SimpleMath.h"


class GameObject;


class Collider
{
protected:
	GameObject*                  m_owner;
	DirectX::SimpleMath::Vector3 m_offset;


public:
	Collider(GameObject* owner);

public:
	virtual ~Collider() = default;


public:
	void OnCollision(const Collider* object);

	const DirectX::SimpleMath::Vector3 GetPosition() const;
	const DirectX::SimpleMath::Vector3 GetOffset() const;

	void  SetOffset(const DirectX::SimpleMath::Vector3& offset);
};