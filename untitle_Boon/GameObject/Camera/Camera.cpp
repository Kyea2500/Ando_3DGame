#include "Camera.h"
#include "DxLib.h"

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
{// �J�����̈ʒu�ƌ������X�V
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
	SetupCamera_Perspective(m_Angle);

	// �J�����̈ʒu���X�V
	m_Position = VAdd(m_Position, VGet(0, 0, 1)); // ��Ƃ��đO���Ɉړ�
	m_Target = VAdd(m_Target, VGet(0, 0, 1)); // �^�[�Q�b�g���O���Ɉړ�
}
