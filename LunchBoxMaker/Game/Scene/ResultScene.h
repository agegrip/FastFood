#pragma once
#include "Game\Scene\BaseScene.h"
#include "Game\Common\DeviceResources.h"
#include "Game\Common\StepTimer.h"
#include "DirectXTK\CommonStates.h"
#include "DirectXTK\SpriteBatch.h"
#include "DirectXTK\SpriteFont.h"
#include "DirectXTK\SimpleMath.h"
#include "DirectXTK\Keyboard.h"
#include "DirectXTK\Model.h"

class ResultScene:public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	void Initialize()override;
	void Update(float elapsedTime)override;
	void Render()override;
	void Finalize()override;
private:
	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// Textポジション
	DirectX::SimpleMath::Vector2 m_pos;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_state;
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	//デバイスリソース
	std::unique_ptr<DX::DeviceResources> m_deviceResources;
	// ワールド
	DirectX::SimpleMath::Matrix m_skydomeworld;
	DirectX::SimpleMath::Matrix m_Floorworld;
};