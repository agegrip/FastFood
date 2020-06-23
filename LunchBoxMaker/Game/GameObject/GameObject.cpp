#include "pch.h"
#include "Game\GameObject\GameObject.h"


GameObject::GameObject(const std::string& tag)
	: m_isValid(true)
	, m_tag(tag)
	, m_position(0.0f,0.0f,0.0f)
	, m_rotation(0.0f,0.0f,0.0f)
	, m_scale(1.0f,1.0f,1.0f)
{
}


GameObject::~GameObject()
{
}

void GameObject::Invalidate()
{
	m_isValid = false;
}



void GameObject::OnCollision(GameObject * object)
{
}



void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}