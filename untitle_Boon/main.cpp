#include "DxLib.h"
#include "InputDevice/game.h"
#include"Scene/SceneMain/SceneMain.h"
namespace
{
	constexpr int MaxTime = 16667;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// フルスクリーンではなく、ウィンドウモードで開くようにする
	ChangeWindowMode(Game::kDefaultWindowMode);
	SetWindowText("<Untitle>");

	// 画面サイズ
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	SceneMain sceneMain;	// シーンのインスタンスを作成
	sceneMain.Init();		// シーンの初期化
	
	// ゲームループ
	while (ProcessMessage() == 0)
	{
		// ループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();
		// 画面をクリアに
		ClearDrawScreen();

		// ここにゲームの処理を書く
		DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ
		sceneMain.Update();		// シーンの更新
		sceneMain.Draw();		// シーンの描画
	


		// 画面の切り替わりを待つ必要がある
		ScreenFlip();
		//FPS(Frame Per Second)60に固定


		// escキーで終了(いったん終了)
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		while (GetNowHiPerformanceCount() - time < MaxTime)
		{
		}

	}

	WaitKey();				// キー入力待ち

	sceneMain.End();		// シーンの終了処理
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}