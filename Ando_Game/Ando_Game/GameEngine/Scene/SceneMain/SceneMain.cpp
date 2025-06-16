#include "SceneMain.h"
#include "DxLib.h"
#include "../../GameObject/Player/Player.h"

SceneMain::SceneMain()
	:m_playerHandle(-1), // �v���C���[�̃n���h���������� 
	m_pPlayer(nullptr), // �v���C���[�̃|�C���^��������
	m_pEnemy(nullptr)    // �G�̃|�C���^��������
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// ���f����ǂݍ���
	m_playerHandle = MV1LoadModel("data/model/Player.mv1");
	// m_enemyHandle = MV1LoadModel("data/model/Enemy.mv1"); // �G�̃��f����ǂݍ��ށi�K�v�Ȃ�R�����g�A�E�g���O���j

	// �v���C���[�̏�����
	m_pPlayer = std::make_shared<Player>();
	m_pPlayer->SetModel(m_playerHandle); // ���f���n���h����ݒ�
	m_pPlayer->Init();
	// �G�̏�����
	// m_pEnemy = std::make_shared<enemy>();
	// m_pEnemy->SetModel(m_enemyHandle); // �G�̃��f���n���h����ݒ�
	// m_pEnemy->Init(); // �G�̏�����

	// �J�����̏�����
	//m_pCamera = std::make_shared<Camera>();
	//m_pCamera->Init(); // �J�����̏�����


}

void SceneMain::End()
{
	MV1DeleteModel(m_playerHandle);
	//	MV1DeleteModel(m_enemyHandle);
}

void SceneMain::Update()
{
	// �v���C���[�̍X�V����
	m_pPlayer->Update();
	// �J�����̍X�V����
	//m_pCamera->Update(); // �J�����̍X�V
	//
	// �G�̍X�V����
	// m_pEnemy->Update(); // �G�̍X�V�i�K�v�Ȃ�R�����g�A�E�g���O���j
}

void SceneMain::Draw()
{
	DrawGrid();
	// �v���C���[�̕`�揈��
	m_pPlayer->Draw();
	// �G�̕`�揈��
	// m_pEnemy->Draw(); // �G�̕`��i�K�v�Ȃ�R�����g�A�E�g���O���j


}

void SceneMain::DrawGrid() const
{
	for (int z = -500; z <= 500; z += 100)
	{
		DrawLine3D(VGet(-500, 0, z), VGet(500, 0, z), 0xff0000);
	}
	for (int x = -500; x <= 500; x += 100)
	{
		DrawLine3D(VGet(x, 0, -500), VGet(x, 0, 500), 0x0000ff);
	}
}
