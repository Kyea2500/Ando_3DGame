#include "player.h"
#include "DxLib.h"
#include "../../InputDevice/game.h"
#include "../../InputDevice/Pad/Pad.h"


namespace
{
	// �v���C���[�̈ړ����x
	constexpr float kPlayerSpeed = 5.0f;

	// �v���C���[�̓����蔻�蔼�a
	constexpr int kPlayerRadius = 150;

	// �v���C���[�̓����蔻��
	constexpr int kPlayerColor = 0xffffff;
	// �v���C���[�̏d��
	constexpr float kGravity = -0.5f; // �d�͂̒l

	// �v���C���[�̃W�����v��
	constexpr float kJumpPower = 16.0f;

	// �v���C���[�̈ړ������x
	constexpr float kMoveAccel = 1.0f;
	// �ړ�������
	constexpr float kMoveDecRate = 0.80f;

}
player::player()
	: m_pos(VGet(0.0f, 0.0f,0.0f)), // �v���C���[�̏������W��ݒ�
	m_vec(VGet(0.0f, 0.0f, 0.0f)), // �v���C���[�̈ړ��x�N�g����������
	speed(kPlayerSpeed), // �v���C���[�̈ړ����x��ݒ�
	m_modelHandle(-1), // �v���C���[�̃��f���n���h����������
	m_isMoveRight(false), // �v���C���[�̈ړ�������������
	m_isMoveLeft(false), // �v���C���[�̈ړ�������������
	m_isMove(false), // �v���C���[�̈ړ���Ԃ�������
	m_isJump(false), // �v���C���[�̃W�����v��Ԃ�������
	m_isSky(false)	 // �v���C���[���n��ɂ��邩�󒆂ɂ��邩��������
{
}

player::~player()
{
}

void player::Init()
{
}

void player::End()
{
}

void player::Update()
{
	m_pos = VAdd(m_pos, m_vec);
	m_vec.x *= kMoveDecRate;
	m_vec.z *= kMoveDecRate;

	if (isJumping())
	{
		m_vec.y += kGravity;
	}
	else
	{
		m_vec.y = 0.0f;
		m_pos.y = 0.0f;
	}
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
	DrawSphere3D(VGet(m_pos.x, m_pos.y,m_pos.z), kPlayerRadius,20.0f, kPlayerColor, kPlayerColor,FALSE);

	MV1DrawModel(m_modelHandle); // ���f���̕`��
	
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
			m_vec.y = 20.0f; // ��Ɉړ�
		}
	}
}

void player::UpdateMove()
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

	// �ړ���Ԃ��X�V
	MV1SetPosition(m_modelHandle, m_pos);
}

bool player::isJumping() const
{
	return  (m_pos.y > 0.0f);
}

