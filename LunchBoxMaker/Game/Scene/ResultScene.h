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
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// Text�|�W�V����
	DirectX::SimpleMath::Vector2 m_pos;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_state;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//�X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	//�f�o�C�X���\�[�X
	std::unique_ptr<DX::DeviceResources> m_deviceResources;
	// ���[���h
	DirectX::SimpleMath::Matrix m_skydomeworld;
	DirectX::SimpleMath::Matrix m_Floorworld;
};