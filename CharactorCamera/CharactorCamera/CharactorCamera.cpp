// キャラクターに付いていくカメラ
//
// ＜操作＞
// 方向キー：キャラクターモデル移動
// Z,Cキー：カメラの水平角度を変更
// S,Xキー：カメラの垂直角度を変更

#include "DxLib.h"
#include <math.h>

// 移動速度
#define MOVESPEED					10.0f

// DxChara.x での走りアニメーションの番号
#define ANIM_RUN					1

// DxChara.x での待機アニメーションの番号
#define ANIM_NEUTRAL				4

// カメラの回転速度
#define CAMERA_ANGLE_SPEED			3.0f

// カメラの注視点の高さ
#define CAMERA_LOOK_AT_HEIGHT		400.0f

// カメラと注視点の距離
#define CAMERA_LOOK_AT_DISTANCE		2150.0f

// ラインを描く範囲
#define LINE_AREA_SIZE				10000.0f

// ラインの数
#define LINE_NUM					50

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	int    ModelHandle ;
	float  AnimTotalTime ;
	float  AnimNowTime ;
	int    AnimAttachIndex ;
	int    RunFlag ;
	int    MoveAnimFrameIndex ;
	VECTOR Position ;
	int    MoveFlag ;
	float  Angle ;
	float  CameraHAngle ;
	float  CameraVAngle ;
	VECTOR MoveVector ;
	float  SinParam ;
	float  CosParam ;

	// ウインドウモードで起動
	ChangeWindowMode( TRUE ) ;

	// ＤＸライブラリの初期化
	if( DxLib_Init() < 0 ) return -1 ;

	// ３Ｄモデルの読み込み
	ModelHandle = MV1LoadModel( "DxChara.x" ) ;

	// カメラの向きを初期化
	CameraHAngle = 0.0f ;
	CameraVAngle = 40.0f ;

	// 向きを初期化
	Angle = 0.0f ;

	// 走っているフラグを倒す
	RunFlag = FALSE ;

	// 待機アニメーションをアタッチ
	AnimAttachIndex = MV1AttachAnim( ModelHandle, ANIM_NEUTRAL ) ;

	// 待機アニメーションの総時間を取得しておく
	AnimTotalTime = MV1GetAttachAnimTotalTime( ModelHandle, AnimAttachIndex ) ;

	// アニメーション再生時間を初期化
	AnimNowTime = 0.0f ;
	MV1SetAttachAnimTime( ModelHandle, AnimAttachIndex, AnimNowTime ) ;

	// アニメーションで移動をしているフレームの番号を検索する
	MoveAnimFrameIndex = MV1SearchFrame( ModelHandle, "BasePoint" ) ;

	// アニメーションで移動をしているフレームを無効にする
	MV1SetFrameUserLocalMatrix( ModelHandle, MoveAnimFrameIndex, MV1GetFrameLocalMatrix( ModelHandle, MoveAnimFrameIndex ) ) ;

	// ３Ｄモデルの座標を初期化
	Position = VGet( 0.0f, 0.0f, 0.0f ) ;

	// 描画先を裏画面にする
	SetDrawScreen( DX_SCREEN_BACK ) ;

	// カメラのクリッピング距離を設定
	SetCameraNearFar( 100.0f, 50000.0f );

	// 背景の色を灰色にする
	SetBackgroundColor( 128, 128, 128 ) ;

	// メインループ(何かキーが押されたらループを抜ける)
	while( ProcessMessage() == 0 )
	{
		// 画面のクリア
		ClearDrawScreen() ;

		// ZCSXキーでカメラの操作
		if( CheckHitKey( KEY_INPUT_C ) == 1 )
		{
			CameraHAngle += CAMERA_ANGLE_SPEED ;
			if( CameraHAngle >= 180.0f )
			{
				CameraHAngle -= 360.0f ;
			}
		}

		if( CheckHitKey( KEY_INPUT_Z ) == 1 )
		{
			CameraHAngle -= CAMERA_ANGLE_SPEED ;
			if( CameraHAngle <= -180.0f )
			{
				CameraHAngle += 360.0f ;
			}
		}

		if( CheckHitKey( KEY_INPUT_S ) == 1 )
		{
			CameraVAngle += CAMERA_ANGLE_SPEED ;
			if( CameraVAngle >= 80.0f )
			{
				CameraVAngle = 80.0f ;
			}
		}

		if( CheckHitKey( KEY_INPUT_X ) == 1 )
		{
			CameraVAngle -= CAMERA_ANGLE_SPEED ;
			if( CameraVAngle <= 0.0f )
			{
				CameraVAngle = 0.0f ;
			}
		}

		// 移動ベクトルを初期化
		MoveVector = VGet( 0.0f, 0.0f, 0.0f ) ;

		// 移動しているかどうかのフラグを倒す
		MoveFlag = FALSE ;

		// 方向入力に従ってキャラクターの移動ベクトルと向きを設定
		if( CheckHitKey( KEY_INPUT_LEFT ) == 1 )
		{
			Angle        = 90.0f - CameraHAngle ;
			MoveFlag     = TRUE ;
			MoveVector.x = -MOVESPEED ;
		}

		if( CheckHitKey( KEY_INPUT_RIGHT ) == 1 )
		{
			Angle        = -90.0f - CameraHAngle ;
			MoveFlag     = TRUE ;
			MoveVector.x = MOVESPEED ;
		}

		if( CheckHitKey( KEY_INPUT_DOWN ) == 1 )
		{
			Angle        = 0.0f - CameraHAngle ;
			MoveFlag     = TRUE ;
			MoveVector.z = -MOVESPEED ;
		}

		if( CheckHitKey( KEY_INPUT_UP ) == 1 )
		{
			Angle        = 180.0f - CameraHAngle ;
			MoveFlag     = TRUE ;
			MoveVector.z = MOVESPEED ;
		}

		// 移動した場合は、カメラの水平角度を考慮した方向に座標を移動する
		if( MoveFlag == TRUE )
		{
			VECTOR TempMoveVector ;

			// カメラの角度に合わせて移動ベクトルを回転してから加算
			SinParam = sin( CameraHAngle / 180.0f * DX_PI_F ) ;
			CosParam = cos( CameraHAngle / 180.0f * DX_PI_F ) ;
			TempMoveVector.x = MoveVector.x * CosParam - MoveVector.z * SinParam ;
			TempMoveVector.y = 0.0f ;
			TempMoveVector.z = MoveVector.x * SinParam + MoveVector.z * CosParam ;

			Position = VAdd( Position, TempMoveVector ) ;
		}

		// 今までと状態が変化した場合はアニメーションを変更する
		if( RunFlag != MoveFlag )
		{
			// 走っているかどうかのフラグを保存
			RunFlag = MoveFlag ;

			// 今までアタッチしていたアニメーションをデタッチ
			MV1DetachAnim( ModelHandle, AnimAttachIndex ) ;

			// 新しいアニメーションをアタッチ
			if( RunFlag )
			{
				AnimAttachIndex = MV1AttachAnim( ModelHandle, ANIM_RUN ) ;
			}
			else
			{
				AnimAttachIndex = MV1AttachAnim( ModelHandle, ANIM_NEUTRAL ) ;
			}

			// アニメーションの総時間を取得しておく
			AnimTotalTime = MV1GetAttachAnimTotalTime( ModelHandle, AnimAttachIndex ) ;

			// アニメーション再生時間を初期化
			AnimNowTime = 0.0f ;
		}
		else
		{
			// アニメーション再生時間を進める
			AnimNowTime += 200.0f ;

			// アニメーション再生時間がアニメーションの総時間を越えていたらループさせる
			if( AnimNowTime >= AnimTotalTime )
			{
				// 新しいアニメーション再生時間は、アニメーション再生時間からアニメーション総時間を引いたもの
				AnimNowTime -= AnimTotalTime ;
			}
		}

		// 新しいアニメーション再生時間をセット
		MV1SetAttachAnimTime( ModelHandle, AnimAttachIndex, AnimNowTime ) ;

		// 新しい向きをセット
		MV1SetRotationXYZ( ModelHandle, VGet( 0.0f, Angle / 180.0f * DX_PI_F, 0.0f ) ) ;

		// ３Ｄモデルに新しい座標をセット
		MV1SetPosition( ModelHandle, Position ) ;

		// カメラの位置と向きを設定
		{
			VECTOR TempPosition1 ;
			VECTOR TempPosition2 ;
			VECTOR CameraPosition ;
			VECTOR CameraLookAtPosition ;

			// 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
			CameraLookAtPosition    = Position ;
			CameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT ;

			// カメラの位置はカメラの水平角度と垂直角度から算出

			// 最初に垂直角度を反映した位置を算出
			SinParam = sin( CameraVAngle / 180.0f * DX_PI_F ) ;
			CosParam = cos( CameraVAngle / 180.0f * DX_PI_F ) ;
			TempPosition1.x = 0.0f ;
			TempPosition1.y =  SinParam * CAMERA_LOOK_AT_DISTANCE ;
			TempPosition1.z = -CosParam * CAMERA_LOOK_AT_DISTANCE ;

			// 次に水平角度を反映した位置を算出
			SinParam = sin( CameraHAngle / 180.0f * DX_PI_F ) ;
			CosParam = cos( CameraHAngle / 180.0f * DX_PI_F ) ;
			TempPosition2.x = CosParam * TempPosition1.x - SinParam * TempPosition1.z ;
			TempPosition2.y = TempPosition1.y ;
			TempPosition2.z = SinParam * TempPosition1.x + CosParam * TempPosition1.z ;

			// 算出した座標に注視点の位置を加算したものがカメラの位置
			CameraPosition = VAdd( TempPosition2, CameraLookAtPosition ) ;

			// カメラの設定に反映する
			SetCameraPositionAndTarget_UpVecY( CameraPosition, CameraLookAtPosition );
		}

		// ３Ｄモデルの描画
		MV1DrawModel( ModelHandle ) ;

		// 位置関係が分かるように地面にラインを描画する
		{
			int i ;
			VECTOR Pos1 ;
			VECTOR Pos2 ;

			SetUseZBufferFlag( TRUE ) ;

			Pos1 = VGet( -LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f ) ;
			Pos2 = VGet( -LINE_AREA_SIZE / 2.0f, 0.0f,  LINE_AREA_SIZE / 2.0f ) ;
			for( i = 0 ; i <= LINE_NUM ; i ++ )
			{
				DrawLine3D( Pos1, Pos2, GetColor( 255,255,255 ) ) ;
				Pos1.x += LINE_AREA_SIZE / LINE_NUM ;
				Pos2.x += LINE_AREA_SIZE / LINE_NUM ;
			}

			Pos1 = VGet( -LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f ) ;
			Pos2 = VGet(  LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f ) ;
			for( i = 0 ; i < LINE_NUM ; i ++ )
			{
				DrawLine3D( Pos1, Pos2, GetColor( 255,255,255 ) ) ;
				Pos1.z += LINE_AREA_SIZE / LINE_NUM ;
				Pos2.z += LINE_AREA_SIZE / LINE_NUM ;
			}

			SetUseZBufferFlag( FALSE ) ;
		}

		// 裏画面の内容を表画面に反映
		ScreenFlip() ;
	}

	// ＤＸライブラリの後始末
	DxLib_End() ;

	// ソフトの終了
	return 0 ;
}
