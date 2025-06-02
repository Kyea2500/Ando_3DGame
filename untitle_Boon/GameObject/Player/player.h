#pragma once
#include "DxLib.h"
class player
{
public:
	// �R���X�g���N�^
	player();
	// �f�X�g���N�^
	~player();
	// ����������
	void Init();
	void SetModel(int model) { m_modelHandle = model; }
	// �I������
	void End();
	// �X�V����
	void Update();
	VECTOR GetPos() const { return m_pos; }
	// �`�揈��
	void Draw();

private:
	void UpdateJump();
	void UpdateMove();

private:
	// �v���C���[�̍��W
	VECTOR m_pos;
	
	// �v���C���[�̈ړ����x
	float speed;

	// �v���C���[�̃��f���n���h��
	int m_modelHandle;	// ���f���n���h��
	
	// �v���C���[�̈ړ�����
	bool m_isMoveRight;		// true�Ȃ�E�Ɉړ�		false�Ȃ獶�Ɉړ�
	bool m_isMoveLeft;		// true�Ȃ獶�Ɉړ�		false�Ȃ�E�Ɉړ�

	// �v���C���[�̈ړ����
	bool m_isMove;			// true�Ȃ�ړ���		false�Ȃ�ړ����Ă��Ȃ�

	// �v���C���[�̃W�����v���
	bool m_isJump;		    // true�Ȃ�W�����v��		false�Ȃ�W�����v���Ă��Ȃ�

	// �v���C���[���󒆂ɂ��邩
	bool m_isSky;		// true�Ȃ�󒆂ɂ���	false�Ȃ�n��ɂ���

};