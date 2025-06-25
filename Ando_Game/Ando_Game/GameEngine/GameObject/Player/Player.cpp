#include "Player.h"
#include"../../InputDevice/Pad/Pad.h"

namespace
{
	// プレイヤーの移動速度
	constexpr float kPlayerSpeed = 5.0f;

	// プレイヤーの当たり判定半径
	constexpr float kColRadius = 85.0f;

	// プレイヤーが立札を読むための当たり判定半径
	constexpr float kColRadiusSign = 250.0f; // 立札の当たり判定半径

	// プレイヤーの当たり判定
	constexpr int kPlayerColor = 16;
	// プレイヤーの重力
	constexpr float kGravity = -0.5f; // 重力の値

	// プレイヤーのジャンプ力
	constexpr float kJumpPower = 22.0f;

	// プレイヤーの移動加速度
	constexpr float kMoveAccel = 0.80f;
	// 移動減速率
	constexpr float kMoveDecRate = 0.70f;

}

Player::Player() :speed(0.0f),
m_transform(std::make_shared<Transform>()),
m_velocity(std::make_shared<Velocity>()),
m_modelHandle(-1),
m_isMoveRight(false),
m_isMoveLeft(false),
m_isMove(false),
m_isJump(0),
m_isSky(false)
{
	
}

void Player::Init()
{
	m_transform->SetPosition({ 0.f, 0.f, 0.f });
	m_velocity->SetVelocity({ 0.f, 0.f, 0.f });
}

void Player::Update()
{
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, DX_PI_F, 0.0f));
	// 当たり判定の描画
	DrawSphere3D(
		GetColPos(),
		GetColRadius(),
		kPlayerColor,
		0xffffff,
		0xffffff,
		false);
	// 立札を読むための当たり判定
	DrawSphere3D(
		GetColPos(),
		GetColRadiusSign(),
		kPlayerColor,
		0x00ff00,
		0x00ff00,
		false);
	// ジャンプの更新
	UpdateJump();
	// 移動の更新
	UpdateMove();
	// プレイヤーの位置を更新
	MV1SetPosition(m_modelHandle,m_transform->GetPosition());
}

VECTOR Player::GetColPos() const
{
	return VECTOR();
}

float Player::GetColRadius() const
{
	return 0.0f;
}

float Player::GetColRadiusSign() const
{
	return 0.0f;
}

void Player::Draw()
{
	// プレイヤーのモデルを描画する
	MV1DrawModel(m_modelHandle);
}

void Player::Final()
{
}

void Player::UpdateJump()
{
	if (Pad::IsTrigger(PAD_INPUT_1)) // ジャンプボタンが押されたら
	{
		if (m_isJump < 2) // 1段目または2段目のジャンプ中でない場合
		{
			m_isJump++; // ジャンプ状態を更新
			m_isSky = true; // 空中にいる状態にする
			m_vec.y = kJumpPower; // ジャンプ力を適用
		}

	}
	else if (!isJumping()) // ジャンプ中でない場合
	{
		m_isJump = 0; // ジャンプ状態をリセット
		m_isSky = false; // 空中状態を解除
		m_vec.y += kGravity; // 重力を適用
	}
}

void Player::UpdateMove()
{
	// プレイヤーの移動処理

// プレイヤーの移動方向の向きを初期化
	m_isMoveRight = false;
	m_isMoveLeft = false;

	// 上下左右の入力に応じて移動ベクトルを更新
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		// 上に移動
		m_vec.z += speed;
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		// 下に移動
		m_vec.z -= speed;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// 左に移動
		m_vec.x -= speed;
		// 左を向いている
		m_isMoveLeft = true;
		m_isMoveRight = false;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// 右に移動
		m_vec.x += speed;
		// 右を向いている
		m_isMoveRight = true;
		m_isMoveLeft = false;
	}
	// 位置を更新
	m_pos = VecAdd(m_pos, m_vec);
}

bool Player::isJumping() const
{
	return false;
}
