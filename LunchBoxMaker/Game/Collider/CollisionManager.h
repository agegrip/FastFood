#pragma once
#include "DirectXTK\SimpleMath.h"
#include <vector>

class Collider;
class SphereCollider;
class BoxCollider;
class CapsuleCollider;

class CollisionManager final
{
	using ColliderList = std::vector<Collider*>;

private:
	ColliderList m_colliders;


public:
	CollisionManager();

public:
	~CollisionManager();

public:
	void Add(Collider* collider);
	void DetectCollision();
private:
	bool IsCollided(const Collider*       collider1, const Collider*       collider2) const;
	bool IsCollided(const SphereCollider* collider1, const SphereCollider* collider2) const;
	bool IsCollided(const BoxCollider*    collider1, const BoxCollider*    collider2) const;
	bool IsCollided(const SphereCollider* collider1, const BoxCollider*    collider2) const;
	bool IsCollided(const BoxCollider*    collider1, const SphereCollider* collider2) const;
	bool IsCollided(const CapsuleCollider* collider1, const CapsuleCollider* collider2) const;
	bool IsCollided(const CapsuleCollider* collider1, const SphereCollider* collider2) const;
	bool IsCollided(const SphereCollider* collider1, const CapsuleCollider* collider2) const;
private:
	// c��ab�Ԃ̋����̕���
	static float SqDistPointSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
	{
		DirectX::SimpleMath::Vector3 ab = b - a;
		DirectX::SimpleMath::Vector3 ac = c - a;
		DirectX::SimpleMath::Vector3 bc = c - b;
		float e = ac.Dot(ab);
		if (e <= 0.0f) return ac.Dot(ac);
		float f = ab.Dot(ab);
		if (e >= f) return bc.Dot(bc);
		return ac.Dot(ac) - e * e / f;
	}

	// �N�����v�֐�
	static inline float Clamp(float n, float max, float min)
	{
		if (n < min) return min;
		if (n > max) return max;
		return n;
	}

	// �Q�̐����̍ŒZ�����̕�����Ԃ��֐�
	static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1
		, DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2
		, float &s, float &t
		, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2)
	{
		DirectX::SimpleMath::Vector3 d1 = q1 - p1;
		DirectX::SimpleMath::Vector3 d2 = q2 - p2;
		DirectX::SimpleMath::Vector3 r = p1 - p2;
		float a = d1.Dot(d1);
		float e = d2.Dot(d2);
		float f = d2.Dot(r);

		if (a <= FLT_EPSILON && e <= FLT_EPSILON)
		{
			s = t = 0.0f;
			c1 = p1;
			c2 = p2;
			return (c1 - c2).Dot(c1 - c2);
		}
		if (a <= FLT_EPSILON)
		{
			s = 0.0f;
			t = f / e;
			t = Clamp(t, 0.0f, 1.0f);
		}
		else
		{
			float c = d1.Dot(r);
			if (e <= FLT_EPSILON)
			{
				t = 0.0f;
				s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else
			{
				float b = d1.Dot(d2);
				float denom = a * e - b * b;
				if (denom != 0.0f)
				{
					s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
				}
				else
				{
					s = 0.0f;
				}
				float tnom = (b * s + f);
				if (tnom < 0.0f)
				{
					t = 0.0f;
					s = Clamp(-c / a, 0.0f, 1.0f);
				}
				else if (tnom > e)
				{
					t = 1.0f;
					s = Clamp((b - c) / a, 0.0f, 1.0f);
				}
				else
				{
					t = tnom / e;
				}
			}
		}
		c1 = p1 + d1 * s;
		c2 = p2 + d2 * t;
		return (c1 - c2).Dot(c1 - c2);
	}
};

// �_�ƃ{�b�N�X�̊Ԃ̍ŒZ�����̕������v�Z����֐�
static float SqDistPointBox(const DirectX::SimpleMath::Vector3& p, const BoxCollider* b);

// �O�p�`�̍\���́i�����ƎO�p�`�̌�������p�j
struct Triangle
{
	// �O�p�`�̕��ʕ�����
	DirectX::SimpleMath::Plane p;
	// ��BC�̕��ʕ������i�d�S���W�̒��_a�ɑ΂���d��u��^����j
	DirectX::SimpleMath::Plane edgePlaneBC;
	// ��CA�̕��ʕ������i�d�S���W�̒��_b�ɑ΂���d��v��^����j
	DirectX::SimpleMath::Plane edgePlaneCA;

	// �R���X�g���N�^���ŏՓ˔�����y�����邽�߂ɑO�����Ōv�Z���Ă���
	Triangle(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
	{
		DirectX::SimpleMath::Vector3 n = (c - a).Cross(b - a);
		p = DirectX::SimpleMath::Plane(a, n);
		DirectX::SimpleMath::Plane pp = DirectX::SimpleMath::Plane(b, n);
		edgePlaneBC = DirectX::SimpleMath::Plane(b, n.Cross(b - c));
		edgePlaneCA = DirectX::SimpleMath::Plane(c, n.Cross(c - a));
		p.Normalize(); edgePlaneBC.Normalize(); edgePlaneCA.Normalize();
		float bc_scale = 1.0f / (a.Dot(edgePlaneBC.Normal()) + edgePlaneBC.D());
		float ca_scale = 1.0f / (b.Dot(edgePlaneCA.Normal()) + edgePlaneCA.D());
		edgePlaneBC.x *= bc_scale; edgePlaneBC.y *= bc_scale; edgePlaneBC.z *= bc_scale; edgePlaneBC.w *= bc_scale;
		edgePlaneCA.x *= ca_scale; edgePlaneCA.y *= ca_scale; edgePlaneCA.z *= ca_scale; edgePlaneCA.w *= ca_scale;
	}
};

// ���������_�̌덷�œ�����ʂ�����̂ŏ����]�T������
#define EPSILON 1.0e-06F

static bool IntersectSegmentTriangle(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 q, Triangle tri, DirectX::SimpleMath::Vector3* s)
{
	float distp = p.Dot(tri.p.Normal()) + tri.p.D();
	if (distp < 0.0f) return false;
	float distq = q.Dot(tri.p.Normal()) + tri.p.D();
	if (distq >= 0.0f) return false;
	float denom = distp - distq;
	float t = distp / denom;
	*s = p + t * (q - p);
	float u = s->Dot(tri.edgePlaneBC.Normal()) + tri.edgePlaneBC.D();
	if (fabsf(u) < EPSILON) u = 0.0f;
	if (u < 0.0f || u > 1.0f) return false;
	float v = s->Dot(tri.edgePlaneCA.Normal()) + tri.edgePlaneCA.D();
	if (fabsf(v) < EPSILON) v = 0.0f;
	if (v < 0.0f) return false;
	float w = 1.0f - u - v;
	if (fabsf(w) < EPSILON) w = 0.0f;
	if (w < 0.0f) return false;
	return true;
}