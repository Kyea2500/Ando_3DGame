	#include "JoyPad.h"
#include <iostream>

JoyPad::JoyPad()
{
	memset(&m_joyPad, 0, sizeof(m_joyPad));//�[��������
	m_prevJoyPad = m_joyPad;
}

JoyPad::~JoyPad()
{
}

void JoyPad::JoyPadUpdate()
{
	m_prevJoyPad = m_joyPad; // �O��̏�Ԃ�ۑ�

	// ���͏�Ԃ��擾
	if(GetJoypadDirectInputState(DX_INPUT_PAD1, &m_joyPad) != 0)
	{
		// �G���[����
		std::cerr << "Error: Failed to get joypad state." << std::endl;
#ifdef _DEBUG
#endif // _DEBUG
		return;
	}

#ifdef _DEBUG
#endif // _DEBUG
	std::cout << "�g�p���̃p�b�h:" << GetJoypadNum() << std::endl;
	
	// �����ꂽ�{�^���𔻒肵�ďo��
	Button button = GetButton();
	if (button.A_Pressed()) std::cout <<  "A�{�^����������܂���" << std::endl;
	else if (button.B_Pressed()) std::cout <<  "B�{�^����������܂���" << std::endl;
	else if (button.X_Pressed()) std::cout <<  "X�{�^����������܂���" << std::endl;
	else if (button.Y_Pressed()) std::cout <<  "Y�{�^����������܂���" << std::endl;
	else if (button.LB_Pressed()) std::cout << "LB�{�^����������܂���" << std::endl;
	else if (button.RB_Pressed()) std::cout << "RB�{�^����������܂���" << std::endl;
	else if (button.BACK_Pressed()) std::cout << "BACK�{�^����������܂���" << std::endl;
	else if (button.START_Pressed()) std::cout << "START�{�^����������܂���" << std::endl;
	else if (button.STICKBL_Pressed()) std::cout << "STICKBL�{�^����������܂���" << std::endl;
	else if (button.STICKBR_Pressed()) std::cout << "STICKBR�{�^����������܂���" << std::endl;
	else if (button.GetCrossKey().UP_Pressed()) std::cout << "��{�^����������܂���" << std::endl;
	else if (button.GetCrossKey().DOWN_Pressed()) std::cout << "���{�^����������܂���" << std::endl;
	else if (button.GetCrossKey().LEFT_Pressed()) std::cout << "���{�^����������܂���" << std::endl;
	else if (button.GetCrossKey().RIGHT_Pressed()) std::cout << "�E�{�^����������܂���" << std::endl;
	else std::cout << "����������Ă��܂���" << std::endl;

}

