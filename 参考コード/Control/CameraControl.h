#pragma once
#include "../../Base/Component.h"
#include "../../Physics/Transform/Transform.h"



class CameraControl : public Component
{
private:
	//================================================
	// �ϐ��錾(�Q��ptr)
	//================================================
	std::shared_ptr<Transform>& m_transform;

	//================================================
	// �ϐ��錾(VECTOR)
	//================================================
	VECTOR m_target;

	//================================================
	// �ϐ��錾(float)
	//================================================
	float m_sinParam;			//sin�p�����[�^
	float m_cosParam;			//cos�p�����[�^
	float m_horizontalAngle;	//�����A���O��
	float m_verticalAngle;		//�����A���O��
	
public:
	CameraControl(std::shared_ptr<Transform>& _transform);

	void Init() override;
	void Update() override;
	void Draw() override {};
	void Final() override {};


	//===============================================
	// �Z�b�g�Q�b�g�֐�
	//===============================================
	std::shared_ptr<Transform>& GetTransForm() const { return m_transform; }

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

