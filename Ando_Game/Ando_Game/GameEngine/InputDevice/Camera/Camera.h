#pragma once
#include"../../Parts/Transform/transform.h"
#include<memory>
class Camera
{
private:
	std::shared_ptr<Transform> m_transform; // カメラの変形情報を保持するTransformオブジェクト
	VECTOR m_target; // カメラの注視点
	float m_sinParam; // 水平角度のサイン値
	float m_cosParam; // 水平角度のコサイン値
	float m_horizontalAngle; // 水平角度
	float m_verticalAngle; // 垂直角度

public:
	Camera(std::shared_ptr<Transform>& _transform);

	void Init(); // 初期化関数
	void End(); // 終了関数
	void Update(); // 更新関数
	void Draw(); // 描画関数

	void SetTarget(const VECTOR& _target) { m_target = _target; }
	VECTOR GetTarget() const { return m_target; }
	
	void SetSinParam(const float& _sinParam) { m_sinParam = _sinParam; }
	float GetSinParam() const { return m_sinParam; }
	
	void SetCosParam(const float& _cosParam) { m_cosParam = _cosParam; }
	float GetCosParam() const { return m_cosParam; }
	
	void SetHAngle(const float& _hAngle) { m_horizontalAngle = _hAngle; }
	float GetHAngle() const { return m_horizontalAngle; }
	
	void SetVAngle(const float& _vAngle) { m_verticalAngle = _vAngle; }
	float GetVAngle() const { return m_verticalAngle; }
};
