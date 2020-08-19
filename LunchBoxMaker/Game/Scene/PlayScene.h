#pragma once
#include "DirectXTK\CommonStates.h"
#include "DirectXTK\SpriteBatch.h"
#include "DirectXTK\SpriteFont.h"
#include "DirectXTK\SimpleMath.h"
#include "DirectXTK\Keyboard.h"
#include "DirectXTK\Mouse.h"
#include "DirectXTK\Model.h"
#include "Game\Scene\BaseScene.h"
#include "Game\Common\DeviceResources.h"
#include "Game\Common\StepTimer.h"
#include "Game\Common\FixCamera.h"
#include "Game\GameObject\Player.h"
#include "Game\GameObject\Enemy.h"
#include "Game\GameObject\EnemyGenerator.h"
#include "Game\GameObject\Food.h"
#include "Game\GameObject\FoodGenerator.h"
#include "Game\GameObject\Chair.h"

class GameObjectManager;
class GridFloor;
class CollisionManager;

class PlayScene:public BaseScene
{
public:
	PlayScene();
	~PlayScene();
	void Initialize()override;
	void Update(float elapsedTime)override;
	void Render()override;
	void Finalize()override;
	// MouseWorld
	Matrix CreateMatrix_Screen2World(int screen_w, int screen_h, Matrix view, Matrix projection);
private:
	// FixCameraの取得
	FixCamera*										 m_fixcamera;
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// Textポジション
	DirectX::SimpleMath::Vector2					 m_pos;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>			 m_state;
	// 射影行列
	DirectX::SimpleMath::Matrix						 m_projection;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>			 m_spriteBatch;
	//スプライトフォント
	std::unique_ptr<DirectX::SpriteFont>			 m_spriteFont;
	//デバイスリソース
	std::unique_ptr<DX::DeviceResources>			 m_deviceResources;
	// 射影行列
	DirectX::SimpleMath::Matrix						 m_skydomeworld;
	DirectX::SimpleMath::Matrix						 m_Floorworld;
	// グリッド床
	std::unique_ptr<GridFloor>                       m_pGridFloor;
	// プレイヤー
	Player*											 m_pPlayer;
	// エネミー
	Enemy*											 m_pEnemy;
	// エネミー生成
	EnemyGenerator*									 m_pEnemyGenerator;
	// 食べ物
	Food*											 m_pFood;
	//食べ物生成
	FoodGenerator*									 m_pFoodGenerator;
	// プレイヤーポジション
	DirectX::SimpleMath::Vector3					 m_pPlayerPos;

};