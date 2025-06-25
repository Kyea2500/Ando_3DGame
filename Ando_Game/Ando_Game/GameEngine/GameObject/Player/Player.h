#pragma once
#include "../Base/GameObject.h"
#include "../../Vector3/Vector3.h"
#include "../../Parts/Transform/transform.h"
#include "../../Parts/Velocity/Velocity.h"

class Player : public GameObject
{
private:
	void UpdateJump();
	void UpdateMove();
	bool isJumping() const;

private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Velocity> m_velocity;

	// プレイヤーの移動速度
	Vector3 m_pos;
	Vector3 m_vec;
	float speed;

	// プレイヤーのモデルハンドル
	int m_modelHandle;	// モデルハンドル

	// プレイヤーの移動方向
	bool m_isMoveRight;		// trueなら右に移動		falseなら左に移動
	bool m_isMoveLeft;		// trueなら左に移動		falseなら右に移動

	// プレイヤーの移動状態
	bool m_isMove;			// trueなら移動中		falseなら移動していない

	// プレイヤーのジャンプ状態
	//bool m_isJump;		    // trueならジャンプ中		falseならジャンプしていない
	int m_isJump;			// 0:未ジャンプ, 1:1段目ジャンプ, 2:2段目ジャンプ

	// プレイヤーが空中にいるか
	bool m_isSky;		// trueなら空中にいる	falseなら地上にいる
public:
	Player();
	
	void Init();
	void SetModel(int model) { m_modelHandle = model; }
	void Update();
	VECTOR GetPos() const { return m_transform->GetPosition(); }
	VECTOR GetColPos() const;
	float GetColRadius() const;
	float GetColRadiusSign() const;
	void Draw();
	void Final();
	
};

