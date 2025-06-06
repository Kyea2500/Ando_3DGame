#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

SceneMain::SceneMain()
	: m_pPlayer(nullptr), // �v���C���[�̃|�C���^��������
	m_pEnemy(nullptr)    // �G�̃|�C���^��������
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// �v���C���[�̏�����
	m_pPlayer = std::make_shared<player>();
	m_pPlayer->Init();
	// �G�̏�����
	m_pEnemy = std::make_shared<enemy>();
	m_pEnemy->Init();
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// ���͏�Ԃ̍X�V
	Pad::Update();
	// �v���C���[�̍X�V����
	m_pPlayer->Update();
	// �G�̍X�V����
	m_pEnemy->Update();
}

void SceneMain::Draw()
{
	// �v���C���[�̕`�揈��
	m_pPlayer->Draw();
	// �G�̕`�揈��
	m_pEnemy->Draw();
}
