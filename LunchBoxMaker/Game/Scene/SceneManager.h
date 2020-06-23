#pragma once
#include "Game\Scene\BaseScene.h"
#include "Game\Scene\LogoScene.h"
#include "Game\Scene\TitleScene.h"
#include "Game\Scene\PlayScene.h"
#include "Game\Scene\ResultScene.h"

// シーン遷移
class SceneManager
{
public:
	enum Scene
	{
		NONE = -1,

		LOGO,
		TITLE,
		PLAY,
		RESULT,

		NUM_SCENES
	};
public:
	static SceneManager* GetInstance(); // シーン管理オブジェクトの取得
	SceneManager();
	~SceneManager();
	void RequestState(Scene scene);
	void ChangeState(Scene scene);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
	void Create();
private:
	BaseScene* m_pScene;
	BaseScene* m_nextScene;
};