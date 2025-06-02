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
	// カメラの位置と向きを設定
	SetCameraNearFar(m_Near, m_Far);
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
	SetupCamera_Perspective(m_Angle);
}

void Camera::Update()
{// カメラの位置と向きを更新
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
	SetupCamera_Perspective(m_Angle);

	// カメラの位置を更新
	m_Position = VAdd(m_Position, VGet(0, 0, 1)); // 例として前方に移動
	m_Target = VAdd(m_Target, VGet(0, 0, 1)); // ターゲットも前方に移動
}
