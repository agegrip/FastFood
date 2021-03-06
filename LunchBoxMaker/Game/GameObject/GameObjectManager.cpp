#include "pch.h"
#include "Game\GameObject\GameObjectManager.h"
#include "Game\GameObject\GameObject.h"


GameObjectManager::GameObjectManager()
	: m_objects()
	, m_objectQueue()
{
}


GameObjectManager::~GameObjectManager()
{
}


void GameObjectManager::Update(float elapsedTime)
{
	DestroyObjects();

	if (!m_objectQueue.empty())
	{
		AcceptObjects();
	}

	UpdateObjects(elapsedTime);
}


void GameObjectManager::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	for (GameObjectPtr& object : m_objects)
	{
		object->Render(viewMatrix, projectionMatrix);
	}
}



void GameObjectManager::Add(GameObjectPtr&& object)
{
	m_objectQueue.push_back(std::move(object));
}



std::vector<GameObject*> GameObjectManager::Find(const std::string & tag) const
{
	std::vector<GameObject*> result;

	for (const GameObjectPtr& object : m_objects)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	for (const GameObjectPtr& object : m_objectQueue)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	return result;
}



std::vector<GameObject*> GameObjectManager::Find(std::function<bool(GameObject*)> predicate) const
{
	std::vector<GameObject*> result;

	for (const GameObjectPtr& object : m_objects)
	{
		if (predicate(object.get()))
		{
			result.push_back(object.get());
		}
	}

	for (const GameObjectPtr& object : m_objectQueue)
	{
		if (predicate(object.get()))
		{
			result.push_back(object.get());
		}
	}

	return result;
}



void GameObjectManager::UpdateObjects(float elapsedTime)
{
	// ภ1 ออforถ
	for (GameObjectPtr& object : m_objects)
	{
		object->Update(elapsedTime);
	}


	// ภ2 Ce[^
	//GameObjectList::iterator it  = m_objects.begin();
	//GameObjectList::iterator end = m_objects.end();
	//while (it != end)
	//{
	//	(*it)->Update(elapsedTime);
	//	++it;
	//}


	// ภ3 _ฎ
	//std::for_each(
	//	m_objects.begin(),
	//	m_objects.end(),
	//	[&](GameObjectPtr& object) { object->Update(elapsedTime); }
	//);
}



void GameObjectManager::AcceptObjects()
{
	// ภ1 ออforถ
	//for (GameObjectPtr& object : m_objectQueue)
	//{
	//	m_objects.push_back(std::move(object));
	//}
	//m_objectQueue.clear();


	// ภ2 Ce[^
	//GameObjectList::iterator it  = m_objectQueue.begin();
	//GameObjectList::iterator end = m_objectQueue.end();
	//while (it != end)
	//{
	//	m_objects.push_back(std::move(*it));
	//	++it;
	//}
	//m_objectQueue.clear();


	// ภ3 vfฬฺฎ
	m_objects.splice(m_objects.end(), m_objectQueue);
}



void GameObjectManager::DestroyObjects()
{
	// ภ1 Ce[^
	//GameObjectList::iterator it  = m_objects.begin();
	//while (it != m_objects.end())
	//{
	//	if ((*it)->IsInvalid())
	//	{
	//		it = m_objects.erase(it);
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}


	// ภ2 ๐๊vท้Sฤฬvf๐ํ
	m_objects.remove_if(std::mem_fn(&GameObject::IsInvalid));


	// ภ3 _ฎ
	//m_objects.remove_if([](const GameObjectPtr& object) { return object->IsInvalid(); });
}