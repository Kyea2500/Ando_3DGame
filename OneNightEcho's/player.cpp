#include "player.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"

namespace
{
	// プレイヤーの初期座標
	constexpr float kInitialPosX = 320.0f;
	constexpr float kInitialPosY = 240.0f;
	// プレイヤーの移動速度
	constexpr float kPlayerSpeed = 20.0f;

	// プレイヤーの半径
	constexpr int kPlayerRadius = 20;

	// プレイヤーの色
	constexpr int kPlayerColor = 0xff2525; // 赤色

	// プレイヤーの攻撃力
	constexpr int kPlayerAttackPower = 2; // 攻撃力
	// プレイヤーの攻撃範囲(半径)
	constexpr int kPlayerAttackRange = 10; // 攻撃範囲
	// プレイヤーの攻撃速度
	constexpr float kPlayerAttackSpeed = 15.0f; // 攻撃速度
}
player::player()
	: m_pos(0.0f, 0.0f), // プレイヤーの初期座標を設定
	speed(kPlayerSpeed), // プレイヤーの移動速度を設定
	m_isMoveRight(false), // プレイヤーの移動方向を初期化
	m_isMoveLeft(false), // プレイヤーの移動方向を初期化
	m_isFaceRight(false), // プレイヤーが右を向いているかを初期化
	m_isFaceLeft(false), // プレイヤーが左を向いているかを初期化
	m_isMove(false), // プレイヤーの移動状態を初期化
	m_isJump(false), // プレイヤーのジャンプ状態を初期化
	m_isSky(false), // プレイヤーが地上にいるか空中にいるかを初期化
	m_isAttack(false), // プレイヤーの攻撃状態を初期化
	m_isShot(false), // プレイヤーの射撃状態を初期化
	m_attackPower(kPlayerAttackPower), // プレイヤーの攻撃力を初期化
	m_attackRange(kPlayerAttackRange), // プレイヤーの攻撃範囲を初期化
	m_attackSpeed(kPlayerAttackSpeed) // プレイヤーの攻撃速度を初期化
{
}

player::~player()
{
}

void player::Init()
{

	// プレイヤーの初期座標を設定
	m_pos.x = kInitialPosX; // 画面の中央に配置
	m_pos.y = kInitialPosY; // 画面の中央に配置
	// プレイヤーの初期化処理
	// その他の初期化処理があればここに追加
}

void player::End()
{
}

void player::Update()
{
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
	DrawCircle(m_pos.x, m_pos.y, kPlayerRadius, kPlayerColor, FALSE); // 赤い円を描画
	// プレイヤーがどっちを向いているのか
	if (m_isFaceRight)
	{
		// 右を向いている
		DrawString(m_pos.x- kPlayerRadius/2, m_pos.y- kPlayerRadius/2, "右", GetColor(255, 255, 255));
	}
	else if (m_isFaceLeft)
	{
		// 左を向いている
		DrawString(m_pos.x- kPlayerRadius/2, m_pos.y- kPlayerRadius/2, "左", GetColor(255, 255, 255));
	}

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
			m_pos.y -= 10.0f; // 上に移動
		}
	}
}

void player::UpdateMove()
{
	// プレイヤーの移動処理
	// 移動ベクトルを初期化
	Vec2 move(0.0f, 0.0f);

	// プレイヤーの移動方向の向きを初期化
	m_isMoveRight = false;
	m_isMoveLeft = false;
 
	// 上下左右の入力に応じて移動ベクトルを更新
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		// 上に移動
		move.y -= speed;
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		// 下に移動
		move.y += speed;
	}
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// 左に移動
		move.x -= speed;
		// 左を向いている
		m_isMoveLeft = true;
		m_isMoveRight = false;
		m_isFaceLeft = true;
		m_isFaceRight = false;
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// 右に移動
		move.x += speed;
		// 右を向いている
		m_isMoveRight = true;
		m_isMoveLeft = false;
		m_isFaceRight = true;
		m_isFaceLeft = false;
	}
	// 移動ベクトルを正規化
	if (move.Length() > 0.0f)
	{
		move.Normalize();
	}

	// プレイヤーの位置を更新
	m_pos += move;

	// 画面外に出ないように制限（オプション）
	// 右方向
	if (m_pos.x < kPlayerRadius) m_pos.x = kPlayerRadius;
	// 左方向
	if (m_pos.x > Game::kScreenWidth- kPlayerRadius) m_pos.x = Game::kScreenWidth- kPlayerRadius;
	// 上方向
	if (m_pos.y < kPlayerRadius) m_pos.y = kPlayerRadius;
	// 下方向
	if (m_pos.y > Game::kScreenHeight + kPlayerRadius) m_pos.y = Game::kScreenHeight + kPlayerRadius;

}

void player::UpdateAttack()
{
	m_isAttack = false; // 攻撃中でない場合
	// 攻撃の処理
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// 攻撃ボタンが押されたら
		// 攻撃処理を実行
		m_isAttack = true; // 攻撃中にする
		m_isShot = true; // 射撃中にする
	}

	if (m_isShot)
	{
		DrawCircle(m_pos.x, m_pos.y, kPlayerRadius, kPlayerColor, FALSE); // 赤い円を描画
	}
}