#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

SceneMain::SceneMain()
	: m_pPlayer(nullptr), // プレイヤーのポインタを初期化
	m_pEnemy(nullptr)    // 敵のポインタを初期化
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// プレイヤーの初期化
	m_pPlayer = std::make_shared<player>();
	m_pPlayer->Init();
	// 敵の初期化
	m_pEnemy = std::make_shared<enemy>();
	m_pEnemy->Init();
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	// 入力状態の更新
	Pad::Update();
	// プレイヤーの更新処理
	m_pPlayer->Update();
	// 敵の更新処理
	m_pEnemy->Update();
}

void SceneMain::Draw()
{
	// プレイヤーの描画処理
	m_pPlayer->Draw();
	// 敵の描画処理
	m_pEnemy->Draw();
}
