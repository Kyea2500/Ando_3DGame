#pragma once
#include "Vec2.h"
class player
{
public:
	// コンストラクタ
	player();
	// デストラクタ
	~player();
	// 初期化処理
	void Init();
	// 終了処理
	void End();
	// 更新処理
	void Update();
	// 描画処理
	void Draw();

private:
	void UpdateJump();
	void UpdateMove();
	void UpdateAttack();
private:
	// プレイヤーの座標
	Vec2 m_pos;
	
	// プレイヤーの移動速度
	float speed;
	
	// プレイヤーの移動方向
	bool m_isMoveRight;		// trueなら右に移動		falseなら左に移動
	bool m_isMoveLeft;		// trueなら左に移動		falseなら右に移動

	// プレイヤーが最後に向いた向きを表示
	bool m_isFaceRight;		// trueなら右を向いている	falseなら左を向いている
	bool m_isFaceLeft;		// trueなら左を向いている	falseなら右を向いている

	// プレイヤーの移動状態
	bool m_isMove;			// trueなら移動中		falseなら移動していない

	// プレイヤーのジャンプ状態
	bool m_isJump;		    // trueならジャンプ中		falseならジャンプしていない

	// プレイヤーが空中にいるか
	bool m_isSky;		// trueなら空中にいる	falseなら地上にいる
	
	// プレイヤーの攻撃状態
	bool m_isAttack;	// trueなら攻撃中		falseなら攻撃していない
	bool m_isShot;	// trueなら射撃中		falseなら射撃していない

	// 弾の座標
	Vec2 m_bulletPos;	// 弾の座標

	// プレイヤーの攻撃力
	int m_attackPower;	// 攻撃力
	// プレイヤーの攻撃範囲
	int m_attackRange;	// 攻撃範囲
	// プレイヤーの攻撃速度
	float m_attackSpeed;	// 攻撃速度
};