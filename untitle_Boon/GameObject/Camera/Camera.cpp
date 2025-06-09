#include "Camera.h"
#include "DxLib.h"
#include "../../InputDevice/Pad/Pad.h"

Camera::Camera():
	m_Near(10.0f),
	m_Far(2000.0f),
	m_Angle(48.0f * DX_PI_F / 180.0f),
	m_Position(VGet(0, 300, -1000)),
	m_Target(VGet(0, 100, 0)),
	m_UpVector(VGet(0, 1, 0))
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	// �J�����̈ʒu�ƌ�����ݒ�
	SetCameraNearFar(m_Near, m_Far);
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
	SetupCamera_Perspective(m_Angle);
}

void Camera::Update()
{
	if (Pad::IsPress(PAD_INPUT_5)) // �E�ɌX����{�^���������ꂽ��
	{
		Lean_to_the_Right();
	}

	if (Pad::IsPress(PAD_INPUT_6)) // ���ɌX����{�^���������ꂽ��
	{
		Lean_to_the_Left();
	}
	// �J�����̈ʒu�ƌ������X�V
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
	SetupCamera_Perspective(m_Angle);
}

void Camera::Lean_to_the_Right()
{
	// �J�������E�ɉ�]������
	m_Target = VAdd(m_Target, VGet(10.0f, 0.0f, 0.0f)); // �^�[�Q�b�g���E�Ɉړ�
	m_Position = VAdd(m_Position, VGet(-10.0f, 1.0f, -10.0f)); // �J�����̈ʒu���E�Ɉړ�
}

void Camera::Lean_to_the_Left()
{
	// �J���������ɉ�]������
	m_Target = VAdd(m_Target, VGet(-10.0f, 0.0f, 0.0f)); // �^�[�Q�b�g�����Ɉړ�
	m_Position = VAdd(m_Position, VGet(10.0f, -1.0f, 10.0f)); // �J�����̈ʒu�����Ɉړ�
}