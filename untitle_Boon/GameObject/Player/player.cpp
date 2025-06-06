#include "player.h"
#include "DxLib.h"
#include "../../InputDevice/game.h"
#include "../../InputDevice/Pad/Pad.h"


namespace
{
	// プレイヤーの移動速度
	constexpr float kPlayerSpeed = 5.0f;

	// プレイヤーの当たり判定半径
	constexpr int kPlayerRadius = 150;

	// プレイヤーの当たり判定
	constexpr int kPlayerColor = 0xffffff;
	// プレイヤーの重力
	constexpr float kGravity = -0.5f; // 重力の値

	// プレイヤーのジャンプ力
	constexpr float kJumpPower = 16.0f;

	// プレイヤーの移動加速度
	constexpr float kMoveAccel = 1.0f;
	// 移動減速率
	constexpr float kMoveDecRate = 0.80f;

}
player::player()
	: m_pos(VGet(0.0f, 0.0f,0.0f)), // プレイヤーの初期座標を設定
	m_vec(VGet(0.0f, 0.0f, 0.0f)), // プレイヤーの移動ベクトルを初期化
	speed(kPlayerSpeed), // プレイヤーの移動速度を設定
	m_modelHandle(-1), // プレイヤーのモデルハンドルを初期化
	m_isMoveRight(false), // プレイヤーの移動方向を初期化
	m_isMoveLeft(false), // プレイヤーの移動方向を初期化
	m_isMove(false), // プレイヤーの移動状態を初期化
	m_isJump(false), // プレイヤーのジャンプ状態を初期化
	m_isSky(false)	 // プレイヤーが地上にいるか空中にいるかを初期化
{
}

player::~player()
{
}

void player::Init()
{
}

void player::End()
{
}

void player::Update()
{
	m_pos = VAdd(m_pos, m_vec);
	m_vec.x *= kMoveDecRate;
	m_vec.z *= kMoveDecRate;

	if (isJumping())
	{
		m_vec.y += kGravity;
	}
	else
	{
		m_vec.y = 0.0f;
		m_pos.y = 0.0f;
	}
	// 入力状態の更新
	Pad::Update();
	// プレイヤーの更新処理
	UpdateJump();
	UpdateMove();
}

void player::Draw()
{
	// 描画処理
	// プレイヤーの描画処理
	DrawSphere3D(VGet(m_pos.x, m_pos.y,m_pos.z), kPlayerRadius,20.0f, kPlayerColor, kPlayerColor,FALSE);

	MV1DrawModel(m_modelHandle); // モデルの描画
	
}

void player::UpdateJump()
{
	m_isJump = false; // ジャンプ中でない場合
	m_isSky = false; // 地上にいる場合

	// ジャンプの処理
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// ジャンプボタンが押されたら
		if (!m_isJump) // ジャンプ中でない場合
		{
			m_isJump = true; // ジャンプ中にする
			m_isSky = true; // 空中にいる状態にする
			m_vec.y = 20.0f; // 上に移動
		}
	}
}

void player::UpdateMove()
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

	// 移動状態を更新
	MV1SetPosition(m_modelHandle, m_pos);
}

bool player::isJumping() const
{
	return  (m_pos.y > 0.0f);
}

