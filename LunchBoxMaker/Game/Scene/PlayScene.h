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
	// FixCamera�̎擾
	FixCamera*										 m_fixcamera;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// Text�|�W�V����
	DirectX::SimpleMath::Vector2					 m_pos;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>			 m_state;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix						 m_projection;
	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch>			 m_spriteBatch;
	//�X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont>			 m_spriteFont;
	//�f�o�C�X���\�[�X
	std::unique_ptr<DX::DeviceResources>			 m_deviceResources;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix						 m_skydomeworld;
	DirectX::SimpleMath::Matrix						 m_Floorworld;
	// �O���b�h��
	std::unique_ptr<GridFloor>                       m_pGridFloor;
	// �v���C���[
	Player*											 m_pPlayer;
	// �G�l�~�[
	Enemy*											 m_pEnemy;
	// �G�l�~�[����
	EnemyGenerator*									 m_pEnemyGenerator;
	// �H�ו�
	Food*											 m_pFood;
	//�H�ו�����
	FoodGenerator*									 m_pFoodGenerator;
	// �v���C���[�|�W�V����
	DirectX::SimpleMath::Vector3					 m_pPlayerPos;

};