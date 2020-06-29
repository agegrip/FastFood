//
// CollisionManager.cpp
//
#include "pch.h"

#include "Game\Collider\CollisionManager.h"

#include <typeinfo>

#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CapsuleCollider.h"
#include "Game\Common\Utilities.h"




CollisionManager::CollisionManager()
	: m_colliders()
{
}



CollisionManager::~CollisionManager()
{
}



void CollisionManager::DetectCollision()
{
	int numObjects = static_cast<int>(m_colliders.size());

	for (int i = 0; i < numObjects - 1; i++)
	{
		for (int j = i + 1; j < numObjects; j++)
		{
			if (IsCollided(m_colliders[i], m_colliders[j]))
			{
				m_colliders[i]->OnCollision(m_colliders[j]);
				m_colliders[j]->OnCollision(m_colliders[i]);
			}
		}
	}

	m_colliders.clear();
}



void CollisionManager::Add(Collider* collider)
{
	m_colliders.push_back(collider);
}

bool CollisionManager::IsCollided(const Collider* collider1, const Collider* collider2) const
{
	static const size_t TYPE_SPHERE = typeid(SphereCollider).hash_code();
	static const size_t TYPE_BOX = typeid(BoxCollider).hash_code();

	size_t collider1Type = typeid(*collider1).hash_code();
	size_t collider2Type = typeid(*collider2).hash_code();


	if ((collider1Type == TYPE_SPHERE) && (collider2Type == TYPE_SPHERE))
	{
		return IsCollided(dynamic_cast<const SphereCollider*>(collider1), dynamic_cast<const SphereCollider*>(collider2));
	}

	if ((collider1Type == TYPE_BOX) && (collider2Type == TYPE_BOX))
	{
		return IsCollided(dynamic_cast<const BoxCollider*>(collider1), dynamic_cast<const BoxCollider*>(collider2));
	}

	if ((collider1Type == TYPE_SPHERE) && (collider2Type == TYPE_BOX))
	{
		return IsCollided(dynamic_cast<const SphereCollider*>(collider1), dynamic_cast<const BoxCollider*>(collider2));
	}

	if ((collider1Type == TYPE_BOX) && (collider2Type == TYPE_SPHERE))
	{
		return IsCollided(dynamic_cast<const BoxCollider*>(collider1), dynamic_cast<const SphereCollider*>(collider2));
	}

	return false;
}



bool CollisionManager::IsCollided(const SphereCollider* collider1, const SphereCollider* collider2) const
{
	// 中心間の距離の平方を計算
	DirectX::SimpleMath::Vector3 d = collider1->GetPosition() - collider2->GetPosition();
	float dist2 = d.Dot(d);
	// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
	float radiusSum = collider1->GetRadius() - collider2->GetRadius();
	return dist2 <= radiusSum * radiusSum;
}



bool CollisionManager::IsCollided(const BoxCollider* collider1, const BoxCollider* collider2) const
{
	if (fabsf(collider1->GetPosition().x - collider2->GetPosition().x) > (collider1->GetSize().x + collider2->GetSize().x)) return false;
	if (fabsf(collider1->GetPosition().y - collider2->GetPosition().y) > (collider1->GetSize().y + collider2->GetSize().y)) return false;
	if (fabsf(collider1->GetPosition().z - collider2->GetPosition().z) > (collider1->GetSize().z + collider2->GetSize().z)) return false;
	return true;
}



bool CollisionManager::IsCollided(const SphereCollider* collider1, const BoxCollider* collider2) const
{
	if (fabsf(collider1->GetPosition().x - collider2->GetPosition().x) > (collider1->GetRadius() + collider2->GetSize().x)) return false;
	if (fabsf(collider1->GetPosition().y - collider2->GetPosition().y) > (collider1->GetRadius() + collider2->GetSize().y)) return false;
	if (fabsf(collider1->GetPosition().z - collider2->GetPosition().z) > (collider1->GetRadius() + collider2->GetSize().z)) return false;
	return true;
}



bool CollisionManager::IsCollided(const BoxCollider* collider1, const SphereCollider* collider2) const
{
	return IsCollided(collider2, collider1);
}

bool CollisionManager::IsCollided(const CapsuleCollider* collider1, const CapsuleCollider* collider2) const
{
	float s, t;
	DirectX::SimpleMath::Vector3 c1, c2;
	// カプセルの中心の線分間の距離の平方を計算
	float dist2 = ClosestPtSegmentSegment(collider1->GetStart(), collider1->GetEnd(), collider2->GetStart(), collider2->GetEnd(), s, t, c1, c2);
	float radius = collider1->GetRadius() + collider2->GetRadius();
	return dist2 <= radius * radius;
}

bool CollisionManager::IsCollided(const CapsuleCollider * collider1, const SphereCollider * collider2) const
{
	return IsCollided(collider2, collider1);
}

bool CollisionManager::IsCollided(const SphereCollider * collider1, const CapsuleCollider * collider2) const
{
	// 球の中心とカプセルの中心の線分との距離の平方を計算
	float dist2 = SqDistPointSegment(collider2->GetStart(), collider2->GetEnd(), collider1->GetPosition());
	float radius = collider1->GetRadius() + collider2->GetRadius();
	return dist2 <= radius * radius;
}

float SqDistPointBox(const DirectX::SimpleMath::Vector3 & p, const BoxCollider * b)
{
	float point[3] = { p.x, p.y, p.z };
	float min[3] = { b->GetPosition().x - b->GetSize().x,b->GetPosition().y - b->GetSize().y , b->GetPosition().z - b->GetSize().z };
	float max[3] = { b->GetPosition().x + b->GetSize().x,b->GetPosition().y + b->GetSize().y , b->GetPosition().z + b->GetSize().z };

	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		float v = point[i];
		if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
	}
	return sqDist;
}