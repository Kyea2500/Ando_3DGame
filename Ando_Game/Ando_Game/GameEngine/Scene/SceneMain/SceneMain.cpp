#include "SceneMain.h"
#include "DxLib.h"
#include "../../GameObject/Player/Player.h"

SceneMain::SceneMain()
	:m_playerHandle(-1), // プレイヤーのハンドルを初期化 
	m_pPlayer(nullptr), // プレイヤーのポインタを初期化
	m_pEnemy(nullptr),    // 敵のポインタを初期化
	m_pCamera(nullptr) // カメラのポインタを初期化
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// モデルを読み込む
	m_playerHandle = MV1LoadModel("../../data/model/player.mv1 ");
	// m_enemyHandle = MV1LoadModel("data/model/Enemy.mv1"); // 敵のモデルを読み込む（必要ならコメントアウトを外す）

	// プレイヤーの初期化
	m_pPlayer = std::make_shared<Player>();
	m_pPlayer->SetModel(m_playerHandle); // モデルハンドルを設定
	m_pPlayer->Init();
	// 敵の初期化
	// m_pEnemy = std::make_shared<enemy>();
	// m_pEnemy->SetModel(m_enemyHandle); // 敵のモデルハンドルを設定
	// m_pEnemy->Init(); // 敵の初期化

	// カメラの初期化
	//m_pCamera = std::make_shared<Camera>();
	//m_pCamera->Init(); // カメラの初期化


}

void SceneMain::End()
{
	MV1DeleteModel(m_playerHandle);
	//	MV1DeleteModel(m_enemyHandle);
}

void SceneMain::Update()
{
	// プレイヤーの更新処理
	m_pPlayer->Update();
	// カメラの更新処理
	//m_pCamera->Update(); // カメラの更新
	//
	// 敵の更新処理
	// m_pEnemy->Update(); // 敵の更新（必要ならコメントアウトを外す）
}

void SceneMain::Draw()
{
	DrawGrid();
	// プレイヤーの描画処理
	m_pPlayer->Draw();
	// 敵の描画処理
	// m_pEnemy->Draw(); // 敵の描画（必要ならコメントアウトを外す）


}

void SceneMain::DrawGrid() const
{
	for (int z = -500; z <= 500; z += 100)
	{
		DrawLine3D(VGet(-500, 0, z), VGet(500, 0, z), 0xff0000);
	}
	for (int x = -500; x <= 500; x += 100)
	{
		DrawLine3D(VGet(x, 0, -500), VGet(x, 0, 500), 0x0000ff);
	}
}
