	#include "JoyPad.h"
#include <iostream>

JoyPad::JoyPad()
{
	memset(&m_joyPad, 0, sizeof(m_joyPad));//ゼロ初期化
	m_prevJoyPad = m_joyPad;
}

JoyPad::~JoyPad()
{
}

void JoyPad::JoyPadUpdate()
{
	m_prevJoyPad = m_joyPad; // 前回の状態を保存

	// 入力状態を取得
	if(GetJoypadDirectInputState(DX_INPUT_PAD1, &m_joyPad) != 0)
	{
		// エラー処理
		std::cerr << "Error: Failed to get joypad state." << std::endl;
#ifdef _DEBUG
#endif // _DEBUG
		return;
	}

#ifdef _DEBUG
#endif // _DEBUG
	std::cout << "使用中のパッド:" << GetJoypadNum() << std::endl;
	
	// 押されたボタンを判定して出力
	Button button = GetButton();
	if (button.A_Pressed()) std::cout <<  "Aボタンが押されました" << std::endl;
	else if (button.B_Pressed()) std::cout <<  "Bボタンが押されました" << std::endl;
	else if (button.X_Pressed()) std::cout <<  "Xボタンが押されました" << std::endl;
	else if (button.Y_Pressed()) std::cout <<  "Yボタンが押されました" << std::endl;
	else if (button.LB_Pressed()) std::cout << "LBボタンが押されました" << std::endl;
	else if (button.RB_Pressed()) std::cout << "RBボタンが押されました" << std::endl;
	else if (button.BACK_Pressed()) std::cout << "BACKボタンが押されました" << std::endl;
	else if (button.START_Pressed()) std::cout << "STARTボタンが押されました" << std::endl;
	else if (button.STICKBL_Pressed()) std::cout << "STICKBLボタンが押されました" << std::endl;
	else if (button.STICKBR_Pressed()) std::cout << "STICKBRボタンが押されました" << std::endl;
	else if (button.GetCrossKey().UP_Pressed()) std::cout << "上ボタンが押されました" << std::endl;
	else if (button.GetCrossKey().DOWN_Pressed()) std::cout << "下ボタンが押されました" << std::endl;
	else if (button.GetCrossKey().LEFT_Pressed()) std::cout << "左ボタンが押されました" << std::endl;
	else if (button.GetCrossKey().RIGHT_Pressed()) std::cout << "右ボタンが押されました" << std::endl;
	else std::cout << "何も押されていません" << std::endl;

}

