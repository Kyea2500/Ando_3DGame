#pragma once

namespace Pad
{
	// �v���g�^�C�v�錾

	/// <summary>
	/// �p�b�h�̓��͏�ԍX�V����
	/// 1�t���[����1��̂݌Ăяo��
	/// </summary>
	void Update();

	/// <summary>
	/// Press����̎擾
	/// </summary>
	/// <param name="button">������s�������{�^��</param>
	/// <returns>������Ă�����true,������Ă��Ȃ�������false</returns>
	bool IsPress(int button);

	/// <summary>
	/// Trigger����(�����ꂽ�u��)�̎擾
	/// </summary>
	/// <param name="button">������s�������{�^��</param>
	/// <returns>�{�^���������ꂽ�u��true,����ȊO��false</returns>
	bool IsTrigger(int button);

	void GetRightStickX()
	{
		// �E�X�e�B�b�N��X�����͂��擾
		// �����Ɏ�����ǉ�

	}
	void GetRightStickY() 
	{
		// �E�X�e�B�b�N��Y�����͂��擾
		// �����Ɏ�����ǉ�
	}
}

