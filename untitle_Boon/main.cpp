#include "DxLib.h"
#include "InputDevice/game.h"
#include"Scene/SceneMain/SceneMain.h"
namespace
{
	constexpr int MaxTime = 16667;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �t���X�N���[���ł͂Ȃ��A�E�B���h�E���[�h�ŊJ���悤�ɂ���
	ChangeWindowMode(Game::kDefaultWindowMode);
	SetWindowText("<Untitle>");

	// ��ʃT�C�Y
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	SceneMain sceneMain;	// �V�[���̃C���X�^���X���쐬
	sceneMain.Init();		// �V�[���̏�����
	
	// �Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		// ���[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();
		// ��ʂ��N���A��
		ClearDrawScreen();

		// �����ɃQ�[���̏���������
		DrawPixel(320, 240, GetColor(255, 255, 255));	// �_��ł�
		sceneMain.Update();		// �V�[���̍X�V
		sceneMain.Draw();		// �V�[���̕`��
	


		// ��ʂ̐؂�ւ���҂K�v������
		ScreenFlip();
		//FPS(Frame Per Second)60�ɌŒ�


		// esc�L�[�ŏI��(��������I��)
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		while (GetNowHiPerformanceCount() - time < MaxTime)
		{
		}

	}

	WaitKey();				// �L�[���͑҂�

	sceneMain.End();		// �V�[���̏I������
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}