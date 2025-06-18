#pragma once
#include <DxLib.h>

class InputDeviceBase
{
public:

	virtual ~InputDeviceBase() {}
	virtual void Update() = 0;
	virtual bool GetButton(int _button) const = 0;
	virtual bool GetButtonDown(int _button) const = 0;
	virtual bool GetButtonUp(int _button) const = 0;
	virtual float GetAxisX() const = 0;
	virtual float GetAxisY() const = 0;
};

