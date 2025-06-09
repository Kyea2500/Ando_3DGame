#include "player.h"
#include "DxLib.h"
#include "../../InputDevice/game.h"
#include "../../InputDevice/Pad/Pad.h"


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
player::player()
	: m_pos(VGet(0.0f, 0.0f,0.0f)), // プレイヤーの初期座標を設定
	m_vec(VGet(0.0f, 0.0f, 0.0f)), // プレイヤーの移動ベクトルを初期化
	speed(kPlayerSpeed), // プレイヤーの移動速度を設定
	m_modelHandle(-1), // プレイヤーのモデルハンドルを初期化
	m_isMoveRight(false), // プレイヤーの移動方向を初期化
	m_isMoveLeft(false), // プレイヤーの移動方向を初期化
	m_isMove(false), // プレイヤーの移動状態を初期化
	m_isJump(0), // プレイヤーのジャンプ状態を初期化
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

VECTOR player::GetColPos() const
{
	VECTOR result = m_pos;
	result.y += 80.0f;
	return result;
}

float player::GetColRadius() const
{
	return  kColRadius;
}

float player::GetColRadiusSign() const
{
	return kColRadiusSign;
}

void player::Draw()
{
	// 描画処理
	// プレイヤーの描画処理
	MV1DrawModel(m_modelHandle); // モデルの描画
	// 最初からこちらを向いているので
	// プレイヤーは常にカメラに背を向ける
	
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
	
}

void player::UpdateJump()
{


	//// ジャンプの処理
	//if (Pad::IsTrigger(PAD_INPUT_1))
	//{
	//	// ジャンプボタンが押されたら
	//	if (!m_isJump) // ジャンプ中でない場合
	//	{
	//		m_isJump = true; // ジャンプ中にする
	//		m_isSky = true; // 空中にいる状態にする
	//		m_vec.y = 20.0f; // 上に移動
	//	}
	//}
	// だが、この処理だと無限にジャンプをしてしまう。
	// ゲームの内容的に2段ジャンプまでにとどめたい
	// その前に、一旦１段ジャンプのみにし、その後に２段目を実装する。

	//if (!m_isJump && !m_isSky) // ジャンプ中で空中にいる場合
	//{
	//	// ジャンプの処理
	//	if (Pad::IsTrigger(PAD_INPUT_1))
	//	{
	//		// ジャンプボタンが押されたら
	//		if (!m_isJump) // ジャンプ中でない場合
	//		{
	//			m_isJump = true; // ジャンプ中にする
	//			m_isSky = true; // 空中にいる状態にする
	//			m_vec.y = 20.0f; // 上に移動
	//		}
	//		else
	//		{
	//			// すでにジャンプ中の場合は何もしない
	//		}
	//	}
	//}

	//else
	//{
	//	// ジャンプ中で空中にいる場合は重力を適用
	//	m_vec.y += kGravity; // 重力を適用
	//	if (m_pos.y <= 0.0f) // 地面に着地した場合
	//	{
	//		m_isJump = false; // ジャンプ状態を解除
	//		m_isSky = false; // 空中状態を解除
	//		m_pos.y = 0.0f; // 地面の高さに戻す
	//		m_vec.y = 0.0f; // 垂直方向の速度をリセット
	//	}
	//}
	// ↑これで１段のみのジャンプを実装できた
	// 次は２段ジャンプを実装する
	// 2段ジャンプを実装するためには、m_isJumpを2段目のジャンプ状態にする必要がある
	// そのために、m_isJumpをbool型からint型に変更し、0:未ジャンプ, 1:1段目ジャンプ, 2:2段目ジャンプとする
	// そして、1段目のジャンプ中に2段目のジャンプボタンを押すと、2段目のジャンプができるようにする
	// 2段目のジャンプは、1段目のジャンプ中にしかできないようにする

	// ジャンプの処理
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
		m_pos.y = 0.0f; // 地面の高さに戻す
		m_vec.y = 0.0f; // 垂直方向の速度をリセット
	}
	// ↑これで2段ジャンプを実装できた
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

