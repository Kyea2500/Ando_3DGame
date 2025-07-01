#pragma once
#include "DxLib.h" // DXライブラリのヘッダーファイルをインクルード
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();

	void UpdateCamera(VECTOR playerPos);

private:
	void Lean_to_the_Right();
	void Lean_to_the_Left();
private:
	float m_Near;  // カメラの近くの距離
	float m_Far;   // カメラの遠くの距離
	float m_Angle; // カメラの視野角
	VECTOR m_Position; // カメラの位置
	VECTOR m_Target;   // カメラの向き
	VECTOR m_UpVector; // 上方向ベクトル
	DINPUT_JOYSTATE input;
};

