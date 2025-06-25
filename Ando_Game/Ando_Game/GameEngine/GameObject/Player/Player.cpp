#include "Player.h"
#include"../../InputDevice/Pad/Pad.h"

namespace
{
	// �v���C���[�̈ړ����x
	constexpr float kPlayerSpeed = 5.0f;

	// �v���C���[�̓����蔻�蔼�a
	constexpr float kColRadius = 85.0f;

	// �v���C���[�����D��ǂނ��߂̓����蔻�蔼�a
	constexpr float kColRadiusSign = 250.0f; // ���D�̓����蔻�蔼�a

	// �v���C���[�̓����蔻��
	constexpr int kPlayerColor = 16;
	// �v���C���[�̏d��
	constexpr float kGravity = -0.5f; // �d�͂̒l

	// �v���C���[�̃W�����v��
	constexpr float kJumpPower = 22.0f;

	// �v���C���[�̈ړ������x
	constexpr float kMoveAccel = 0.80f;
	// �ړ�������
	constexpr float kMoveDecRate = 0.70f;

}

Player::Player() :speed(0.0f),
m_transform(std::make_shared<Transform>()),
m_velocity(std::make_shared<Velocity>()),
m_modelHandle(-1),
m_isMoveRight(false),
m_isMoveLeft(false),
m_isMove(false),
m_isJump(0),
m_isSky(false)
{
	
}

void Player::Init()
{
	m_transform->SetPosition({ 0.f, 0.f, 0.f });
	m_velocity->SetVelocity({ 0.f, 0.f, 0.f });
}

void Player::Update()
{
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, DX_PI_F, 0.0f));
	// �����蔻��̕`��
	DrawSphere3D(
		GetColPos(),
		GetColRadius(),
		kPlayerColor,
		0xffffff,
		0xffffff,
		false);
	// ���D��ǂނ��߂̓����蔻��
	DrawSphere3D(
		GetColPos(),
		GetColRadiusSign(),
		kPlayerColor,
		0x00ff00,
		0x00ff00,
		false);
	// �W�����v�̍X�V
	UpdateJump();
	// �ړ��̍X�V
	UpdateMove();
	// �v���C���[�̈ʒu���X�V
	MV1SetPosition(m_modelHandle,m_transform->GetPosition());
}

VECTOR Player::GetColPos() const
{
	return VECTOR();
}

float Player::GetColRadius() const
{
	return 0.0f;
}

float Player::GetColRadiusSign() const
{
	return 0.0f;
}

void Player::Draw()
{
	// �v���C���[�̃��f����`�悷��
	MV1DrawModel(m_modelHandle);
}

void Player::Final()
{
}

void Player::UpdateJump()
{
	if (Pad::IsTrigger(PAD_INPUT_1)) // �W�����v�{�^���������ꂽ��
	{
		if (m_isJump < 2) // 1�i�ڂ܂���2�i�ڂ̃W�����v���łȂ��ꍇ
		{
			m_isJump++; // �W�����v��Ԃ��X�V
			m_isSky = true; // �󒆂ɂ����Ԃɂ���
			m_vec.y = kJumpPower; // �W�����v�͂�K�p
		}

	}
	else if (!isJumping()) // �W�����v���łȂ��ꍇ
	{
		m_isJump = 0; // �W�����v��Ԃ����Z�b�g
		m_isSky = false; // �󒆏�Ԃ�����
		m_vec.y += kGravity; // �d�͂�K�p
	}
}

void Player::UpdateMove()
{
	// �v���C���[�̈ړ�����

// �v���C���[�̈ړ������̌�����������
	m_isMoveRight = false;
	m_isMoveLeft = false;

	// �㉺���E�̓��͂ɉ����Ĉړ��x�N�g�����X�V
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		// ��Ɉړ�
		m_vec.z += speed;
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		// ���Ɉړ�
		m_vec.z -= speed;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// ���Ɉړ�
		m_vec.x -= speed;
		// ���������Ă���
		m_isMoveLeft = true;
		m_isMoveRight = false;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// �E�Ɉړ�
		m_vec.x += speed;
		// �E�������Ă���
		m_isMoveRight = true;
		m_isMoveLeft = false;
	}
	// �ʒu���X�V
	m_pos = VecAdd(m_pos, m_vec);
}

bool Player::isJumping() const
{
	return false;
}
