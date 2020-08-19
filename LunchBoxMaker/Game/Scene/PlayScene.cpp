
#include "Game\Scene\PlayScene.h"

#include "Game\Scene\SceneManager.h"
#include "Game\Common\GameContext.h"
#include "Game\\GameObject\GameObjectManager.h"
#include "Game\Debug\GridFloor.h"
#include "Game\Collider\CollisionManager.h"

PlayScene::PlayScene()
	:m_pGridFloor()
	,m_pPlayerPos(0.f,0.f,5.f)
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
}

PlayScene::~PlayScene()
{
	if (m_fixcamera != nullptr)
	{
		delete m_fixcamera;
		m_fixcamera = nullptr;
	}
}

void PlayScene::Initialize()
{
	// �f�o�C�X���\�[�X�쐬
	DirectX::CommonStates* state = GameContext<DirectX::CommonStates>().Get();
	DX::DeviceResources*   deviceResources = GameContext<DX::DeviceResources>().Get();
	ID3D11Device*          device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();

	//�X�e�[�g�쐬
	m_state = std::make_unique<DirectX::CommonStates>(device);

	//�X�v���C�g�쐬
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);

	//�t�H���g�쐬
	m_spriteFont = std::make_unique <DirectX::SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");

	// �E�B���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);

	// FixCamera�쐬
	m_fixcamera = new FixCamera();

	m_fixcamera->Create(fovAngleY, aspectRatio, 0.1f, 100.0f);

	// GridFloor�쐬
	m_pGridFloor = std::make_unique<GridFloor>(device, deviceContext, state, 10.0f, 10);

	// �v���C���[�쐬
	std::unique_ptr<Player> pPlayer = std::make_unique<Player>(m_pPlayerPos,0.2f);
	m_pPlayer = pPlayer.get();
	GameContext<GameObjectManager>().Get()->Add(std::move(pPlayer));
	// �G�l�~�[�쐬
	std::unique_ptr<EnemyGenerator> pEnemyGenerator = std::make_unique<EnemyGenerator>(2.0f);
	m_pEnemyGenerator = pEnemyGenerator.get();
	GameContext<GameObjectManager>().Get()->Add(std::move(pEnemyGenerator));
	// �H�ו��쐬
	std::unique_ptr<FoodGenerator> pFoodGenerator = std::make_unique<FoodGenerator>(2.0f);
	m_pFoodGenerator = pFoodGenerator.get();
	GameContext<GameObjectManager>().Get()->Add(std::move(pFoodGenerator));
}

void PlayScene::Update(float elapsedTime)
{
	DirectX::Keyboard::State keystate = GameContext<DirectX::Keyboard>::Get()->GetState();
	DirectX::Mouse::State mouseState = GameContext<DirectX::Mouse>::Get()->GetState();
	//DirectX::SimpleMath::Vector3::Transform();
	if (mouseState.positionMode == DirectX::Mouse::MODE_RELATIVE) return;
	// �J�����̍X�V
	m_fixcamera->Update();
	// �Q�[���I�u�W�F�N�g�̍X�V
	GameContext<GameObjectManager>::Get()->Update(GameContext<DX::StepTimer>::Get()->GetElapsedSeconds());
	// �R���C�_�[�̍X�V
	GameContext<CollisionManager>::Get()->DetectCollision();

	if (keystate.X)
	{
		SceneManager* scene = GameContext<SceneManager>().Get();
		scene->ChangeState(SceneManager::RESULT);
	}
}

void PlayScene::Render()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();
	wchar_t text[50];
	swprintf(text, L"\nPlayScene\nPresing X Key", m_pos.x, m_pos.y);
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_state->NonPremultiplied());
	m_spriteFont->DrawString(m_spriteBatch.get(), text, DirectX::SimpleMath::Vector2(0, 0));
	
	// �Q�[���I�u�W�F�N�g�̕\��
	GameContext<GameObjectManager>::Get()->Render(m_fixcamera->getViewMatrix(), m_fixcamera->getProjectionMatrix());

	m_pGridFloor->draw(deviceResources->GetD3DDeviceContext(), m_fixcamera->getViewMatrix(), m_fixcamera->getProjectionMatrix());

	m_spriteBatch->End();
}

void PlayScene::Finalize()
{
	m_state.reset();
	m_spriteBatch.reset();
	m_spriteFont.reset();
}

Matrix PlayScene::CreateMatrix_Screen2World(int screen_w, int screen_h, Matrix view, Matrix projection)
{
	// �r���[�|�[�g�X�P�[�����O�s����쐬
	Matrix viewport;
	viewport._11 = screen_w / 2.0f;
	viewport._22 = -screen_h / 2.0f;
	viewport._41 = screen_w / 2.0f;
	viewport._42 = screen_h / 2.0f;
	// �t�s����쐬
	Matrix invS = viewport.Invert();
	Matrix invP = projection.Invert();
	Matrix invV = view.Invert();
	// �w�r���[�|�[�g�X�P�[�����O�s��̋t�s��x �~ �w�ˉe�s��̋t�s��x �~ �w�r���[�s��̋t�s��x
	return invS * invP * invV;
}