#pragma once
#include "../JoyPad/JoyPad.h"
#include <memory>

class InputDeviceManager
{
private:

	//=======================================
	//	入力デバイスの宣言
	//=======================================

	//ジョイパッド
	std::shared_ptr<JoyPad> m_joyPad;

	/*入力デバイスのシングルトン化*/
	InputDeviceManager();
	~InputDeviceManager();

	InputDeviceManager(const InputDeviceManager&) = delete;
	InputDeviceManager& operator=(const InputDeviceManager&) = delete;


public:

	void InputDeviceUpdate();

	//=======================================
	//	外部取得関数
	//=======================================
	
	//インスタンス取得関数
	static InputDeviceManager& GetInstance() {static InputDeviceManager instance; return instance; }

	//ジョイパッド取得関数
	static std::shared_ptr<JoyPad> GetJoyPad() { return GetInstance().m_joyPad; }
};

