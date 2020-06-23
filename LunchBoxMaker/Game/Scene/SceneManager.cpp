
#include "Game\Scene\SceneManager.h"
#include "Game\Scene\BaseScene.h"

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;

	return &instance;
}

SceneManager::SceneManager()
{
	m_pScene = nullptr;
}

SceneManager::~SceneManager()
{
	delete m_pScene;
}

void SceneManager::RequestState(Scene scene)
{

}

void SceneManager::ChangeState(Scene scene)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Finalize();
		delete m_pScene;
		m_pScene = nullptr;
	}

	switch (scene)
	{
	case Scene::LOGO:
		m_pScene = new LogoScene();
		m_pScene->Initialize();
		break;
	case Scene::TITLE:
		m_pScene = new TitleScene();
		m_pScene->Initialize();
		break;
	case Scene::PLAY:
		m_pScene = new PlayScene();
		m_pScene->Initialize();
		break;
	case Scene::RESULT:
		m_pScene = new ResultScene();
		m_pScene->Initialize();
		break;
		break;
	default:
		break;
	}
}

void SceneManager::Update(float elapsedTime)
{
	m_pScene->Update(elapsedTime);
}

void SceneManager::Render()
{
	m_pScene->Render();
}

void SceneManager::Finalize()
{
	m_pScene->Finalize();
}

void SceneManager::Create()
{

}