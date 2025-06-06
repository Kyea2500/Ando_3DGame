#include "SceneManager.h"
#include "../SceneTitle/SceneTitle.h"
#include "../SceneMain/SceneMain.h"
#include "../SceneGameOver/SceneGameOver.h"

SceneManager::SceneManager():
	m_Kind(kSceneTitle), // 初期シーンをタイトルに設定
	m_pSceneTitle(nullptr), // タイトルシーンのポインタを初期化
	m_pSceneMain(nullptr),  // メインシーンのポインタを初期化
	m_pSceneGameOver(nullptr) // ゲームオーバーシーンのポインタを初期化
{
}

SceneManager::~SceneManager()
{
	// 各シーンのポインタを解放
	if (m_pSceneTitle != nullptr)
	{
		delete m_pSceneTitle;

	}
	else if (m_pSceneMain != nullptr)
	{
		delete m_pSceneMain;
	}
	else if (m_pSceneGameOver != nullptr)
	{
		delete m_pSceneGameOver;
	}
}

void SceneManager::Init()
{
	// シーンの初期化
	switch (m_Kind)
	{
	case kSceneTitle:
		m_pSceneTitle = new SceneTitle();
		m_pSceneTitle->Init();
		break;
	case kSceneMain:
		m_pSceneMain = new SceneMain();
		m_pSceneMain->Init();
		break;
	case kSceneGameOver:
		m_pSceneGameOver = new SceneGameOver();
		m_pSceneGameOver->Init();
		break;
	default:
		break;
	}
}

void SceneManager::End()
{// シーンの終了処理
	switch (m_Kind)
	{
	case kSceneTitle:
		m_pSceneTitle->End();
		delete m_pSceneTitle;
		m_pSceneTitle = nullptr;
		break;
	case kSceneMain:
		m_pSceneMain->End();
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
		break;
	case kSceneGameOver:
		m_pSceneGameOver->End();
		delete m_pSceneGameOver;
		m_pSceneGameOver = nullptr;
		break;
	default:
		break;
	}
}

void SceneManager::Update()
{
	// シーンの更新
	switch (m_Kind)
	{
	case kSceneTitle:
		m_pSceneTitle->Update();
		break;
	case kSceneMain:
		m_pSceneMain->Update();
		break;
	case kSceneGameOver:
		m_pSceneGameOver->Update();
		break;
	default:
		break;
	}
}


void SceneManager::Draw()
{
	// シーンの描画
	switch (m_Kind)
	{
	case kSceneTitle:
		m_pSceneTitle->Draw();
		break;
	case kSceneMain:
		m_pSceneMain->Draw();
		break;
	case kSceneGameOver:
		m_pSceneGameOver->Draw();
		break;
	default:
		break;
	}
}
