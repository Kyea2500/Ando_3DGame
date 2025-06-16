#pragma once
#include "../JoyPad/JoyPad.h"
#include <memory>

class InputDeviceManager
{
private:

	//=======================================
	//	���̓f�o�C�X�̐錾
	//=======================================

	//�W���C�p�b�h
	std::shared_ptr<JoyPad> m_joyPad;

	/*���̓f�o�C�X�̃V���O���g����*/
	InputDeviceManager();
	~InputDeviceManager();

	InputDeviceManager(const InputDeviceManager&) = delete;
	InputDeviceManager& operator=(const InputDeviceManager&) = delete;


public:

	void InputDeviceUpdate();

	//=======================================
	//	�O���擾�֐�
	//=======================================
	
	//�C���X�^���X�擾�֐�
	static InputDeviceManager& GetInstance() {static InputDeviceManager instance; return instance; }

	//�W���C�p�b�h�擾�֐�
	static std::shared_ptr<JoyPad> GetJoyPad() { return GetInstance().m_joyPad; }
};

