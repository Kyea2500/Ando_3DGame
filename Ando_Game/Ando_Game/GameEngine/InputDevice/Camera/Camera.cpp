#include "Camera.h"
#include "../../Parts/Transform/transform.h"
#include <cmath>
#include"../../InputDevice/Pad/Pad.h"

Camera::Camera(std::shared_ptr<Transform>& _transform)
	: m_transform(_transform)
	, m_target(VGet(0, 0, 0))
	, m_sinParam(0.0f)
	, m_cosParam(0.0f)
	, m_horizontalAngle(0.0f)
	, m_verticalAngle(0.0f)
{
}

void Camera::Init()
{
	m_target = VGet(0, 0, 0);
	m_horizontalAngle = 0.0f;
	m_verticalAngle = 0.0f;
	m_sinParam = std::sin(m_horizontalAngle / 180.0f * DX_PI_F);
	m_cosParam = std::cos(m_horizontalAngle / 180.0f * DX_PI_F);
	SetCameraNearFar(1.0f, 10000.0f);
}

void Camera::End()
{
	// �J�����̏I�������͓��ɕK�v�Ȃ�
}

void Camera::Update()
{
	if (m_verticalAngle < -89.0f) m_verticalAngle = -89.0f; // �����p�x�̐���
	if (m_verticalAngle > 89.0f) m_verticalAngle = 89.0f;
	m_sinParam = std::sin(m_horizontalAngle / 180.0f * DX_PI_F);
	m_cosParam = std::cos(m_horizontalAngle / 180.0f * DX_PI_F);
	VECTOR cameraPosition;
	cameraPosition.x = m_target.x + m_cosParam * 10.0f; // �J�����ʒu�̌v�Z
	cameraPosition.y = m_target.y + m_sinParam * 10.0f;
	cameraPosition.z = m_target.z - 10.0f;
	m_transform->SetPosition(cameraPosition); // �J�����̈ʒu���X�V
	SetCameraPositionAndTarget_UpVecY(cameraPosition, m_target); // �J�����̒����_��ݒ�
}

void Camera::Draw()
{
	// �J�����̕`�揈���͕s�v
}
