#include "DxLib.h"
#include "Scene.h"
#include "SceneClear.h"

SceneClear::SceneClear() 
{
	// �N���A�w�i�n���h��
	ClearBGHandle = 0;

	ClearButtonHandle1 = 0;
	ClearButtonHandle2 = 0;

	ClearEffectHandle = 0;
}
SceneClear::~SceneClear() { FinClear(); }

//�N���A�V�[��������
void SceneClear::InitClear()
{
	SetMouseDispFlag(true);

	// �N���A�w�i�n���h��
	ClearBGHandle = LoadGraph(CLEAR_BG_PATH);

	//�^�C�g���{�^���n���h��
	ClearButtonHandle1 = LoadGraph(CLEAR_BUTTTON_PATH1);
	ClearButtonHandle2 = LoadGraph(CLEAR_BUTTTON_PATH2);

	ClearEffectHandle = LoadGraph(CLEAR_EFFECT_PATH);
	ClearEffectposX = 0;
	ClearEffectposY = -720;

	//�T�E���h�n���h��
	ClearSoundPath = LoadSoundMem(CLEAR_BGM_PATH);
	ButtonSEPath = LoadSoundMem(CLEAR_BUTTON_SE_PATH);

	PlaySoundMem(ClearSoundPath, DX_PLAYTYPE_BACK, true);

	//�N���A�V�[�����[�v��
	g_CurrentSceneID = SCENE_ID_LOOP_CLEAR;
}

//�N���A�V�[���ʏ폈��
void SceneClear::StepClear()
{
	GetMousePoint(&mouseX, &mouseY);
	// Enter����������
	//if (InputKey::Push(KEY_INPUT_RETURN))
	//{
	//	// �N���A�V�[�����I��
	//	FinClear();
	//}

	ClearEffectposY += 5;

	//�^�C�g���{�^������������
	if (mouseX >= 273 && mouseX <= 1022 && mouseY >= 588 && mouseY <= 675 &&
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		PlaySoundMem(ButtonSEPath, DX_PLAYTYPE_BACK, true);

		// �N���A�V�[�����I��
		FinClear();
		
	}

}

//�N���A�V�[���`�揈��
void SceneClear::DrawClear()
{
	// �N���A�w�i�`��
	DrawGraph(0, 0, ClearBGHandle, true);

	//�^�C�g���{�^���`��
	if (mouseX >= 273 && mouseX <= 1022 && mouseY >= 588 && mouseY <= 675)
	{
		DrawGraph(0, 0,ClearButtonHandle2, true);
	}
	else
	{
		
		DrawGraph(-4, -4, ClearButtonHandle1, true);
		
	}

	DrawGraph(ClearEffectposX, ClearEffectposY, ClearEffectHandle, true);

	DrawRotaGraph(ClearEffectposX,ClearEffectposY,1.0f,0.0f,ClearEffectHandle,true);
}

//�N���A�V�[���I������
void SceneClear::FinClear()
{
	// �N���A�w�i�n���h��
	DeleteGraph(ClearBGHandle);

	//�^�C�g���{�^���n���h��
	DeleteGraph(ClearButtonHandle1);
	DeleteGraph(ClearButtonHandle2);

	//BGM�n���h��
	DeleteSoundMem(ClearSoundPath);
	DeleteSoundMem(ButtonSEPath);

	//�^�C�g���V�[���ֈړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
