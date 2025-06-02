#pragma once
#include "DxLib.h"
class player
{
public:
	// コンストラクタ
	player();
	// デストラクタ
	~player();
	// 初期化処理
	void Init();
	void SetModel(int model) { m_modelHandle = model; }
	// 終了処理
	void End();
	// 更新処理
	void Update();
	VECTOR GetPos() const { return m_pos; }
	// 描画処理
	void Draw();

private:
	void UpdateJump();
	void UpdateMove();

private:
	// プレイヤーの座標
	VECTOR m_pos;
	
	// プレイヤーの移動速度
	float speed;

	// プレイヤーのモデルハンドル
	int m_modelHandle;	// モデルハンドル
	
	// プレイヤーの移動方向
	bool m_isMoveRight;		// trueなら右に移動		falseなら左に移動
	bool m_isMoveLeft;		// trueなら左に移動		falseなら右に移動

	// プレイヤーの移動状態
	bool m_isMove;			// trueなら移動中		falseなら移動していない

	// プレイヤーのジャンプ状態
	bool m_isJump;		    // trueならジャンプ中		falseならジャンプしていない

	// プレイヤーが空中にいるか
	bool m_isSky;		// trueなら空中にいる	falseなら地上にいる

};