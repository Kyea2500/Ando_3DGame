#pragma once
#include "DxLib.h" // DX���C�u�����̃w�b�_�[�t�@�C�����C���N���[�h
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
	float m_Near;  // �J�����̋߂��̋���
	float m_Far;   // �J�����̉����̋���
	float m_Angle; // �J�����̎���p
	VECTOR m_Position; // �J�����̈ʒu
	VECTOR m_Target;   // �J�����̌���
	VECTOR m_UpVector; // ������x�N�g��
	DINPUT_JOYSTATE input;
};

