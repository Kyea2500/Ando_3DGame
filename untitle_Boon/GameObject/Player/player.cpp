#include "player.h"
#include "DxLib.h"
#include "../../InputDevice/game.h"
#include "../../InputDevice/Pad/Pad.h"


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
player::player()
	: m_pos(VGet(0.0f, 0.0f,0.0f)), // �v���C���[�̏������W��ݒ�
	m_vec(VGet(0.0f, 0.0f, 0.0f)), // �v���C���[�̈ړ��x�N�g����������
	speed(kPlayerSpeed), // �v���C���[�̈ړ����x��ݒ�
	m_modelHandle(-1), // �v���C���[�̃��f���n���h����������
	m_isMoveRight(false), // �v���C���[�̈ړ�������������
	m_isMoveLeft(false), // �v���C���[�̈ړ�������������
	m_isMove(false), // �v���C���[�̈ړ���Ԃ�������
	m_isJump(0), // �v���C���[�̃W�����v��Ԃ�������
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

VECTOR player::GetColPos() const
{
	VECTOR result = m_pos;
	result.y += 80.0f;
	return result;
}

float player::GetColRadius() const
{
	return  kColRadius;
}

float player::GetColRadiusSign() const
{
	return kColRadiusSign;
}

void player::Draw()
{
	// �`�揈��
	// �v���C���[�̕`�揈��
	MV1DrawModel(m_modelHandle); // ���f���̕`��
	// �ŏ����炱����������Ă���̂�
	// �v���C���[�͏�ɃJ�����ɔw��������
	
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
	
}

void player::UpdateJump()
{


	//// �W�����v�̏���
	//if (Pad::IsTrigger(PAD_INPUT_1))
	//{
	//	// �W�����v�{�^���������ꂽ��
	//	if (!m_isJump) // �W�����v���łȂ��ꍇ
	//	{
	//		m_isJump = true; // �W�����v���ɂ���
	//		m_isSky = true; // �󒆂ɂ����Ԃɂ���
	//		m_vec.y = 20.0f; // ��Ɉړ�
	//	}
	//}
	// �����A���̏������Ɩ����ɃW�����v�����Ă��܂��B
	// �Q�[���̓��e�I��2�i�W�����v�܂łɂƂǂ߂���
	// ���̑O�ɁA��U�P�i�W�����v�݂̂ɂ��A���̌�ɂQ�i�ڂ���������B

	//if (!m_isJump && !m_isSky) // �W�����v���ŋ󒆂ɂ���ꍇ
	//{
	//	// �W�����v�̏���
	//	if (Pad::IsTrigger(PAD_INPUT_1))
	//	{
	//		// �W�����v�{�^���������ꂽ��
	//		if (!m_isJump) // �W�����v���łȂ��ꍇ
	//		{
	//			m_isJump = true; // �W�����v���ɂ���
	//			m_isSky = true; // �󒆂ɂ����Ԃɂ���
	//			m_vec.y = 20.0f; // ��Ɉړ�
	//		}
	//		else
	//		{
	//			// ���łɃW�����v���̏ꍇ�͉������Ȃ�
	//		}
	//	}
	//}

	//else
	//{
	//	// �W�����v���ŋ󒆂ɂ���ꍇ�͏d�͂�K�p
	//	m_vec.y += kGravity; // �d�͂�K�p
	//	if (m_pos.y <= 0.0f) // �n�ʂɒ��n�����ꍇ
	//	{
	//		m_isJump = false; // �W�����v��Ԃ�����
	//		m_isSky = false; // �󒆏�Ԃ�����
	//		m_pos.y = 0.0f; // �n�ʂ̍����ɖ߂�
	//		m_vec.y = 0.0f; // ���������̑��x�����Z�b�g
	//	}
	//}
	// ������łP�i�݂̂̃W�����v�������ł���
	// ���͂Q�i�W�����v����������
	// 2�i�W�����v���������邽�߂ɂ́Am_isJump��2�i�ڂ̃W�����v��Ԃɂ���K�v������
	// ���̂��߂ɁAm_isJump��bool�^����int�^�ɕύX���A0:���W�����v, 1:1�i�ڃW�����v, 2:2�i�ڃW�����v�Ƃ���
	// �����āA1�i�ڂ̃W�����v����2�i�ڂ̃W�����v�{�^���������ƁA2�i�ڂ̃W�����v���ł���悤�ɂ���
	// 2�i�ڂ̃W�����v�́A1�i�ڂ̃W�����v���ɂ����ł��Ȃ��悤�ɂ���

	// �W�����v�̏���
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
		m_pos.y = 0.0f; // �n�ʂ̍����ɖ߂�
		m_vec.y = 0.0f; // ���������̑��x�����Z�b�g
	}
	// �������2�i�W�����v�������ł���
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

