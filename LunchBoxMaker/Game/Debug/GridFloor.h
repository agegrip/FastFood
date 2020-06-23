//======================================================
// File Name	: GridFloor.h
// Summary		: �f�o�b�O�O���b�h��
// Date			: 2019/4/25
// Author		: Takafumi Ban
//======================================================
#pragma once

#include "DirectXTK\CommonStates.h"
#include "DirectXTK\PrimitiveBatch.h"
#include "DirectXTK\Effects.h"
#include "DirectXTK\VertexTypes.h"
#include "DirectXTK\SimpleMath.h"

// �f�o�b�O�O���b�h���N���X
class GridFloor
{
	// �G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// �R�����X�e�[�g�ւ̃|�C���^
	DirectX::CommonStates* m_states;

	// ���̈�ӂ̃T�C�Y
	float m_size;

	// ������
	int m_divs;

public:
	// �R���X�g���N�^
	GridFloor(ID3D11Device* device, ID3D11DeviceContext* context, DirectX::CommonStates* states, float size, int divs);

	// �f�X�g���N�^
	~GridFloor();

	// �`��
	void draw(ID3D11DeviceContext* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::GXMVECTOR color = DirectX::Colors::Gray);
};



