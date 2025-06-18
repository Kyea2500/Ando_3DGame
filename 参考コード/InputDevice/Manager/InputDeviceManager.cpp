#include "InputDeviceManager.h"
#include <iostream>

InputDeviceManager::InputDeviceManager()
{
	m_joyPad = std::make_shared<JoyPad>();
}

InputDeviceManager::~InputDeviceManager()
{
}

void InputDeviceManager::InputDeviceUpdate()
{
    if (m_joyPad)
    {
        std::cout << "Calling JoyPadUpdate()" << std::endl;
        m_joyPad->JoyPadUpdate(); // JoyPad ‚Ìó‘Ô‚ğXV
    }
    else
    {
        std::cout << "JoyPad instance is null!" << std::endl;
    }
}
