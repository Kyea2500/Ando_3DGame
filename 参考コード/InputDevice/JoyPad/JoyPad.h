#pragma once
#include <DxLib.h>

// �{�^���ԍ��i�ʏ�̃{�^���j
enum class PadButton
{
	A = 0,
	B,
	X,
	Y,
	LB,
	RB,
	BACK,
	START,
	STICKBL,
	STICKBR
};

// POV�����i�\���L�[�j
enum class PadPOVDirection
{
	UP = 0,
	RIGHT = 9000,
	DOWN = 18000,
	LEFT = 27000,
	NONE = -1
};


class JoyPad
{
private:
	// �W���C�p�b�h�̏��
	DINPUT_JOYSTATE m_joyPad;

	DINPUT_JOYSTATE m_prevJoyPad; // �O��̏��

	// �E�X�e�B�b�N�̍\����
	struct RightStick
	{
		const DINPUT_JOYSTATE& joyState;

		float X() const { return joyState.Rx / 32767.0f; }
		float Y() const { return joyState.Ry / 32767.0f; }
		float Z() const { return joyState.Rz / 32767.0f; }
	};

	// ���X�e�B�b�N�̍\����
	struct LeftStick
	{
		const DINPUT_JOYSTATE& joyState;

		float X() const { return joyState.X / 32767.0f; }
		float Y() const { return joyState.Y / 32767.0f; }
		float Z() const { return joyState.Z / 32767.0f; }
	};

	// �{�^������я\���L�[
	struct Button
	{
		const DINPUT_JOYSTATE& joyState;
		const DINPUT_JOYSTATE& prevJoyState;
	
		// �ʏ�{�^��
		bool A() const { if (joyState.Buttons[static_cast<int>(PadButton::A)]) return true;  else return false; }
		bool B() const { if (joyState.Buttons[static_cast<int>(PadButton::B)]) return true;  else return false; }
		bool X() const { if (joyState.Buttons[static_cast<int>(PadButton::X)]) return true;  else return false; }
		bool Y() const { if (joyState.Buttons[static_cast<int>(PadButton::Y)]) return true;  else return false; }
		bool LB() const { if (joyState.Buttons[static_cast<int>(PadButton::LB)]) return true;  else return false; }	
		bool RB() const { if (joyState.Buttons[static_cast<int>(PadButton::RB)]) return true;  else return false; }
		bool BACK() const { if (joyState.Buttons[static_cast<int>(PadButton::BACK)]) return true;  else return false; }
		bool START() const { if (joyState.Buttons[static_cast<int>(PadButton::START)]) return true;  else return false; }
		bool STICKBL() const { if (joyState.Buttons[static_cast<int>(PadButton::STICKBL)]) return true;  else return false; }
		bool STICKBR() const { if (joyState.Buttons[static_cast<int>(PadButton::STICKBR)]) return true;  else return false; }
	
		// �ʏ�{�^���̏u�Ԕ���
		bool A_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::A)] && joyState.Buttons[static_cast<int>(PadButton::A)]; }
		bool B_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::B)] && joyState.Buttons[static_cast<int>(PadButton::B)]; }
		bool X_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::X)] && joyState.Buttons[static_cast<int>(PadButton::X)]; }
		bool Y_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::Y)] && joyState.Buttons[static_cast<int>(PadButton::Y)]; }
		bool LB_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::LB)] && joyState.Buttons[static_cast<int>(PadButton::LB)]; }
		bool RB_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::RB)] && joyState.Buttons[static_cast<int>(PadButton::RB)]; }
		bool BACK_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::BACK)] && joyState.Buttons[static_cast<int>(PadButton::BACK)]; }
		bool START_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::START)] && joyState.Buttons[static_cast<int>(PadButton::START)]; }
		bool STICKBL_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::STICKBL)] && joyState.Buttons[static_cast<int>(PadButton::STICKBL)]; }
		bool STICKBR_Pressed() const { return !prevJoyState.Buttons[static_cast<int>(PadButton::STICKBR)] && joyState.Buttons[static_cast<int>(PadButton::STICKBR)]; }

		
		// �\���L�[
		struct CrossKey
		{
			const DINPUT_JOYSTATE& joyState;
			const DINPUT_JOYSTATE& prevJoyState;

			bool UP() const { return joyState.POV[0] == static_cast<int>(PadPOVDirection::UP); }
			bool RIGHT() const { return joyState.POV[0] == static_cast<int>(PadPOVDirection::RIGHT); }
			bool DOWN() const { return joyState.POV[0] == static_cast<int>(PadPOVDirection::DOWN); }
			bool LEFT() const { return joyState.POV[0] == static_cast<int>(PadPOVDirection::LEFT); }
			bool NONE() const { return joyState.POV[0] == static_cast<int>(PadPOVDirection::NONE); }

			bool UP_Pressed() const { return !prevJoyState.POV[0] == static_cast<int>(PadPOVDirection::UP) && joyState.POV[0] == static_cast<int>(PadPOVDirection::UP); }
			bool RIGHT_Pressed() const { return !prevJoyState.POV[0] == static_cast<int>(PadPOVDirection::RIGHT) && joyState.POV[0] == static_cast<int>(PadPOVDirection::RIGHT); }
			bool DOWN_Pressed() const { return !prevJoyState.POV[0] == static_cast<int>(PadPOVDirection::DOWN) && joyState.POV[0] == static_cast<int>(PadPOVDirection::DOWN); }
			bool LEFT_Pressed() const { return !prevJoyState.POV[0] == static_cast<int>(PadPOVDirection::LEFT) && joyState.POV[0] == static_cast<int>(PadPOVDirection::LEFT); }
			bool NONE_Pressed() const { return !prevJoyState.POV[0] == static_cast<int>(PadPOVDirection::NONE) && joyState.POV[0] == static_cast<int>(PadPOVDirection::NONE); }
		};

		CrossKey GetCrossKey() const { return CrossKey{ joyState, prevJoyState }; }
	};

public:
	JoyPad();
	~JoyPad();

	// �X�V
	void JoyPadUpdate();

	// �X�e�B�b�N
	RightStick GetRightStick() const { return RightStick{ m_joyPad }; }
	LeftStick GetLeftStick() const { return LeftStick{ m_joyPad }; }

	// �{�^���E�\���L�[
	Button GetButton() const { return Button{ m_joyPad, m_prevJoyPad }; }
};
