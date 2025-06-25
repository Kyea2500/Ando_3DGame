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
	// カメラの終了処理は特に必要ない
}

void Camera::Update()
{
	if (m_verticalAngle < -89.0f) m_verticalAngle = -89.0f; // 垂直角度の制限
	if (m_verticalAngle > 89.0f) m_verticalAngle = 89.0f;
	m_sinParam = std::sin(m_horizontalAngle / 180.0f * DX_PI_F);
	m_cosParam = std::cos(m_horizontalAngle / 180.0f * DX_PI_F);
	VECTOR cameraPosition;
	cameraPosition.x = m_target.x + m_cosParam * 10.0f; // カメラ位置の計算
	cameraPosition.y = m_target.y + m_sinParam * 10.0f;
	cameraPosition.z = m_target.z - 10.0f;
	m_transform->SetPosition(cameraPosition); // カメラの位置を更新
	SetCameraPositionAndTarget_UpVecY(cameraPosition, m_target); // カメラの注視点を設定
}

void Camera::Draw()
{
	// カメラの描画処理は不要
}
