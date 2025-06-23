#pragma once
#include "../Base/GameObject.h"

class Player : public GameObject
{
private:
	void UpdateJump();
	void UpdateMove();
	bool isJumping() const;

private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Velocity> m_velocity;

	// �v���C���[�̈ړ����x
	VECTOR m_pos = m_transform->GetPosition(); // ���݂̈ʒu���擾
	VECTOR m_vec = m_velocity->GetVelocity(); // ���݂̑��x���擾
	float speed;

	// �v���C���[�̃��f���n���h��
	int m_modelHandle;	// ���f���n���h��

	// �v���C���[�̈ړ�����
	bool m_isMoveRight;		// true�Ȃ�E�Ɉړ�		false�Ȃ獶�Ɉړ�
	bool m_isMoveLeft;		// true�Ȃ獶�Ɉړ�		false�Ȃ�E�Ɉړ�

	// �v���C���[�̈ړ����
	bool m_isMove;			// true�Ȃ�ړ���		false�Ȃ�ړ����Ă��Ȃ�

	// �v���C���[�̃W�����v���
	//bool m_isJump;		    // true�Ȃ�W�����v��		false�Ȃ�W�����v���Ă��Ȃ�
	int m_isJump;			// 0:���W�����v, 1:1�i�ڃW�����v, 2:2�i�ڃW�����v

	// �v���C���[���󒆂ɂ��邩
	bool m_isSky;		// true�Ȃ�󒆂ɂ���	false�Ȃ�n��ɂ���
public:
	Player();
	
	void Init();
	void SetModel(int model) { m_modelHandle = model; }
	void Update();
	VECTOR GetPos() const { return m_transform->GetPosition(); }
	VECTOR GetColPos() const;
	float GetColRadius() const;
	float GetColRadiusSign() const;
	void Draw();
	void Final();

};

