#pragma once

#include "Game\Collider\Collider.h"

class SphereCollider : public Collider
{
private:
	float m_radius;


public:
	SphereCollider(GameObject* owner, float radius);

public:
	~SphereCollider() = default;


public:
	float GetRadius() const;
	void  SetRadius(float radius);
};