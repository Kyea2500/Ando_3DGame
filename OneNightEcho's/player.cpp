#include "player.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"

namespace
{
	// �v���C���[�̏������W
	constexpr float kInitialPosX = 320.0f;
	constexpr float kInitialPosY = 240.0f;
	// �v���C���[�̈ړ����x
	constexpr float kPlayerSpeed = 20.0f;

	// �v���C���[�̔��a
	constexpr int kPlayerRadius = 20;

	// �v���C���[�̐F
	constexpr int kPlayerColor = 0xff2525; // �ԐF

	// �v���C���[�̍U����
	constexpr int kPlayerAttackPower = 2; // �U����
	// �v���C���[�̍U���͈�(���a)
	constexpr int kPlayerAttackRange = 10; // �U���͈�
	// �v���C���[�̍U�����x
	constexpr float kPlayerAttackSpeed = 15.0f; // �U�����x
}
player::player()
	: m_pos(0.0f, 0.0f), // �v���C���[�̏������W��ݒ�
	speed(kPlayerSpeed), // �v���C���[�̈ړ����x��ݒ�
	m_isMoveRight(false), // �v���C���[�̈ړ�������������
	m_isMoveLeft(false), // �v���C���[�̈ړ�������������
	m_isFaceRight(false), // �v���C���[���E�������Ă��邩��������
	m_isFaceLeft(false), // �v���C���[�����������Ă��邩��������
	m_isMove(false), // �v���C���[�̈ړ���Ԃ�������
	m_isJump(false), // �v���C���[�̃W�����v��Ԃ�������
	m_isSky(false), // �v���C���[���n��ɂ��邩�󒆂ɂ��邩��������
	m_isAttack(false), // �v���C���[�̍U����Ԃ�������
	m_isShot(false), // �v���C���[�̎ˌ���Ԃ�������
	m_attackPower(kPlayerAttackPower), // �v���C���[�̍U���͂�������
	m_attackRange(kPlayerAttackRange), // �v���C���[�̍U���͈͂�������
	m_attackSpeed(kPlayerAttackSpeed) // �v���C���[�̍U�����x��������
{
}

player::~player()
{
}

void player::Init()
{

	// �v���C���[�̏������W��ݒ�
	m_pos.x = kInitialPosX; // ��ʂ̒����ɔz�u
	m_pos.y = kInitialPosY; // ��ʂ̒����ɔz�u
	// �v���C���[�̏���������
	// ���̑��̏���������������΂����ɒǉ�
}

void player::End()
{
}

void player::Update()
{
	// ���͏�Ԃ̍X�V
	Pad::Update();
	// �v���C���[�̍X�V����
	UpdateJump();
	UpdateMove();
}

void player::Draw()
{
	// �`�揈��
	// �v���C���[�̕`�揈��
	DrawCircle(m_pos.x, m_pos.y, kPlayerRadius, kPlayerColor, FALSE); // �Ԃ��~��`��
	// �v���C���[���ǂ����������Ă���̂�
	if (m_isFaceRight)
	{
		// �E�������Ă���
		DrawString(m_pos.x- kPlayerRadius/2, m_pos.y- kPlayerRadius/2, "�E", GetColor(255, 255, 255));
	}
	else if (m_isFaceLeft)
	{
		// ���������Ă���
		DrawString(m_pos.x- kPlayerRadius/2, m_pos.y- kPlayerRadius/2, "��", GetColor(255, 255, 255));
	}

}

void player::UpdateJump()
{
	m_isJump = false; // �W�����v���łȂ��ꍇ
	m_isSky = false; // �n��ɂ���ꍇ

	// �W�����v�̏���
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// �W�����v�{�^���������ꂽ��
		if (!m_isJump) // �W�����v���łȂ��ꍇ
		{
			m_isJump = true; // �W�����v���ɂ���
			m_isSky = true; // �󒆂ɂ����Ԃɂ���
			m_pos.y -= 10.0f; // ��Ɉړ�
		}
	}
}

void player::UpdateMove()
{
	// �v���C���[�̈ړ�����
	// �ړ��x�N�g����������
	Vec2 move(0.0f, 0.0f);

	// �v���C���[�̈ړ������̌�����������
	m_isMoveRight = false;
	m_isMoveLeft = false;
 
	// �㉺���E�̓��͂ɉ����Ĉړ��x�N�g�����X�V
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		// ��Ɉړ�
		move.y -= speed;
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		// ���Ɉړ�
		move.y += speed;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// ���Ɉړ�
		move.x -= speed;
		// ���������Ă���
		m_isMoveLeft = true;
		m_isMoveRight = false;
		m_isFaceLeft = true;
		m_isFaceRight = false;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// �E�Ɉړ�
		move.x += speed;
		// �E�������Ă���
		m_isMoveRight = true;
		m_isMoveLeft = false;
		m_isFaceRight = true;
		m_isFaceLeft = false;
	}
	// �ړ��x�N�g���𐳋K��
	if (move.Length() > 0.0f)
	{
		move.Normalize();
	}

	// �v���C���[�̈ʒu���X�V
	m_pos += move;

	// ��ʊO�ɏo�Ȃ��悤�ɐ����i�I�v�V�����j
	// �E����
	if (m_pos.x < kPlayerRadius) m_pos.x = kPlayerRadius;
	// ������
	if (m_pos.x > Game::kScreenWidth- kPlayerRadius) m_pos.x = Game::kScreenWidth- kPlayerRadius;
	// �����
	if (m_pos.y < kPlayerRadius) m_pos.y = kPlayerRadius;
	// ������
	if (m_pos.y > Game::kScreenHeight + kPlayerRadius) m_pos.y = Game::kScreenHeight + kPlayerRadius;

}

void player::UpdateAttack()
{
	m_isAttack = false; // �U�����łȂ��ꍇ
	// �U���̏���
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// �U���{�^���������ꂽ��
		// �U�����������s
		m_isAttack = true; // �U�����ɂ���
		m_isShot = true; // �ˌ����ɂ���
	}

	if (m_isShot)
	{
		DrawCircle(m_pos.x, m_pos.y, kPlayerRadius, kPlayerColor, FALSE); // �Ԃ��~��`��
	}
}