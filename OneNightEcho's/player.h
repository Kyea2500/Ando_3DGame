#pragma once
#include "Vec2.h"
class player
{
public:
	// �R���X�g���N�^
	player();
	// �f�X�g���N�^
	~player();
	// ����������
	void Init();
	// �I������
	void End();
	// �X�V����
	void Update();
	// �`�揈��
	void Draw();

private:
	void UpdateJump();
	void UpdateMove();
	void UpdateAttack();
private:
	// �v���C���[�̍��W
	Vec2 m_pos;
	
	// �v���C���[�̈ړ����x
	float speed;
	
	// �v���C���[�̈ړ�����
	bool m_isMoveRight;		// true�Ȃ�E�Ɉړ�		false�Ȃ獶�Ɉړ�
	bool m_isMoveLeft;		// true�Ȃ獶�Ɉړ�		false�Ȃ�E�Ɉړ�

	// �v���C���[���Ō�Ɍ�����������\��
	bool m_isFaceRight;		// true�Ȃ�E�������Ă���	false�Ȃ獶�������Ă���
	bool m_isFaceLeft;		// true�Ȃ獶�������Ă���	false�Ȃ�E�������Ă���

	// �v���C���[�̈ړ����
	bool m_isMove;			// true�Ȃ�ړ���		false�Ȃ�ړ����Ă��Ȃ�

	// �v���C���[�̃W�����v���
	bool m_isJump;		    // true�Ȃ�W�����v��		false�Ȃ�W�����v���Ă��Ȃ�

	// �v���C���[���󒆂ɂ��邩
	bool m_isSky;		// true�Ȃ�󒆂ɂ���	false�Ȃ�n��ɂ���
	
	// �v���C���[�̍U�����
	bool m_isAttack;	// true�Ȃ�U����		false�Ȃ�U�����Ă��Ȃ�
	bool m_isShot;	// true�Ȃ�ˌ���		false�Ȃ�ˌ����Ă��Ȃ�

	// �e�̍��W
	Vec2 m_bulletPos;	// �e�̍��W

	// �v���C���[�̍U����
	int m_attackPower;	// �U����
	// �v���C���[�̍U���͈�
	int m_attackRange;	// �U���͈�
	// �v���C���[�̍U�����x
	float m_attackSpeed;	// �U�����x
};