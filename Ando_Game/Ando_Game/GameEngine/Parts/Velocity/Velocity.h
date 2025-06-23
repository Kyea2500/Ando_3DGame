#pragma once
#include <DxLib.h>
class Velocity
{
private:
	VECTOR m_velocity; // 速度ベクトル
public:

	void SetVelocity(const VECTOR& velocity) { m_velocity = velocity; }
	VECTOR GetVelocity() const { return m_velocity; }
	void AddVelocity(const VECTOR& delta) { m_velocity = VAdd(m_velocity, delta); }
	void ClearVelocity() { m_velocity = VGet(0.0f, 0.0f, 0.0f); }
};


