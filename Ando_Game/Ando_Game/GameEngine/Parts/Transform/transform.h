#pragma once
#include <DxLib.h>

class Transform
{
private:
	VECTOR m_position;

public:
	void SetPosition(const VECTOR& _pos) { m_position = _pos; }
	VECTOR GetPosition() const { return m_position; }



};