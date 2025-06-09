#pragma once
#include <DxLib.h>

class Base_GameObject
{
private:
	VECTOR m_position;

protected:
	void SetPosition(const VECTOR& _position) { m_position = _position; }
	VECTOR GetPosition() const { return m_position; }

public:




};