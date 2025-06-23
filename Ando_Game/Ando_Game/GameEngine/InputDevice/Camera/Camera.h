#pragma once
#include"../../Parts/Transform/transform.h"
#include<memory>
class Camera
{
private:
	std::shared_ptr<Transform> m_transform; // �J�����̕ό`����ێ�����Transform�I�u�W�F�N�g
	VECTOR m_target; // �J�����̒����_
	float m_sinParam; // �����p�x�̃T�C���l
	float m_cosParam; // �����p�x�̃R�T�C���l
	float m_horizontalAngle; // �����p�x
	float m_verticalAngle; // �����p�x

public:
	Camera(std::shared_ptr<Transform>& _transform);

	void Init(); // �������֐�
	void End(); // �I���֐�
	void Update(); // �X�V�֐�
	void Draw(); // �`��֐�

	void SetTarget(const VECTOR& _target) { m_target = _target; }
	VECTOR GetTarget() const { return m_target; }
	
	void SetSinParam(const float& _sinParam) { m_sinParam = _sinParam; }
	float GetSinParam() const { return m_sinParam; }
	
	void SetCosParam(const float& _cosParam) { m_cosParam = _cosParam; }
	float GetCosParam() const { return m_cosParam; }
	
	void SetHAngle(const float& _hAngle) { m_horizontalAngle = _hAngle; }
	float GetHAngle() const { return m_horizontalAngle; }
	
	void SetVAngle(const float& _vAngle) { m_verticalAngle = _vAngle; }
	float GetVAngle() const { return m_verticalAngle; }
};
