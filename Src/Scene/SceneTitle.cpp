#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle() 
{
	SetMouseDispFlag(true);

	// �^�C�g���w�i�n���h��
	TitleBGHandle = 0;

	TitleButtonHandle1 = 0;
	TitleButtonHandle2 = 0;

	//TitleSoundPath = 0;
}
SceneTitle::~SceneTitle() { FinTitle(); }

// �^�C�g���̏�����
void SceneTitle::InitTitle()
{
	// �^�C�g���w�i�n���h��
	TitleBGHandle = LoadGraph(TITLE_BG_PATH);

	//�^�C�g���{�^���n���h��
	TitleButtonHandle1 = LoadGraph(TITLE_BUTTTON_PATH1);
	TitleButtonHandle2 = LoadGraph(TITLE_BUTTTON_PATH2);

	//�T�E���h�n���h��
	TitleSoundPath = LoadSoundMem(TITLE_BGM_PATH);

	PlaySoundMem(TitleSoundPath, DX_PLAYTYPE_BACK, true);
	// �^�C�g�����[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

// �^�C�g���ʏ폈��
void SceneTitle::StepTitle()
{
	GetMousePoint(&mouseX, &mouseY);


	

	// Enter����������
	//if(InputKey::Push(KEY_INPUT_RETURN))
	//{
	//	// �^�C�g���V�[�����I��
	//	FinTitle();
	//}

	//�^�C�g���{�^������������
	if (mouseX>=273&&mouseX<=1022&&mouseY >= 588&&mouseY<=675&&
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		// �^�C�g���V�[�����I��
		FinTitle();
	}
}

// �^�C�g���`�揈��
void SceneTitle::DrawTitle()
{
	// �^�C�g���w�i�`��
	DrawGraph(0, 0, TitleBGHandle, true);

	//�^�C�g���{�^���`��
	if (mouseX >= 273 && mouseX <= 1022 && mouseY >= 588 && mouseY <= 675)
	{
	   DrawGraph(0, 0, TitleButtonHandle2, true);
	}
	else
	{
		DrawGraph(-4, -4, TitleButtonHandle1, true);
	}

	//���W�m�F�p
   /* DrawFormatString(0, 55, GetColor(0, 0, 255),
		"�}�E�X���W:X:%d\n�}�E�X���W:Y:%d"
		, mouseX, mouseY);*/
}

// �^�C�g���I������
void SceneTitle::FinTitle()
{
	// �^�C�g���w�i�n���h��
	DeleteGraph(TitleBGHandle);

	//�^�C�g���{�^���n���h��
	DeleteGraph(TitleButtonHandle1);
	DeleteGraph(TitleButtonHandle2);

	//BGM�n���h��
	DeleteSoundMem(TitleSoundPath);

	// �v���C�V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
