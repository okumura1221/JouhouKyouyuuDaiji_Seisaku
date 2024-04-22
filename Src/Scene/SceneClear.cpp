#include "DxLib.h"
#include "Scene.h"
#include "SceneClear.h"

SceneClear::SceneClear() 
{
	// クリア背景ハンドル
	ClearBGHandle = 0;

	ClearButtonHandle1 = 0;
	ClearButtonHandle2 = 0;

	ClearEffectHandle = 0;
}
SceneClear::~SceneClear() { FinClear(); }

//クリアシーン初期化
void SceneClear::InitClear()
{
	SetMouseDispFlag(true);

	// クリア背景ハンドル
	ClearBGHandle = LoadGraph(CLEAR_BG_PATH);

	//タイトルボタンハンドル
	ClearButtonHandle1 = LoadGraph(CLEAR_BUTTTON_PATH1);
	ClearButtonHandle2 = LoadGraph(CLEAR_BUTTTON_PATH2);

	ClearEffectHandle = LoadGraph(CLEAR_EFFECT_PATH);
	ClearEffectposX = 0;
	ClearEffectposY = -720;

	//サウンドハンドル
	ClearSoundPath = LoadSoundMem(CLEAR_BGM_PATH);
	ButtonSEPath = LoadSoundMem(CLEAR_BUTTON_SE_PATH);

	PlaySoundMem(ClearSoundPath, DX_PLAYTYPE_BACK, true);

	//クリアシーンループへ
	g_CurrentSceneID = SCENE_ID_LOOP_CLEAR;
}

//クリアシーン通常処理
void SceneClear::StepClear()
{
	GetMousePoint(&mouseX, &mouseY);
	// Enterを押したら
	//if (InputKey::Push(KEY_INPUT_RETURN))
	//{
	//	// クリアシーンを終了
	//	FinClear();
	//}

	ClearEffectposY += 5;

	//タイトルボタンを押したら
	if (mouseX >= 273 && mouseX <= 1022 && mouseY >= 588 && mouseY <= 675 &&
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		PlaySoundMem(ButtonSEPath, DX_PLAYTYPE_BACK, true);

		// クリアシーンを終了
		FinClear();
		
	}

}

//クリアシーン描画処理
void SceneClear::DrawClear()
{
	// クリア背景描画
	DrawGraph(0, 0, ClearBGHandle, true);

	//タイトルボタン描画
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

//クリアシーン終了処理
void SceneClear::FinClear()
{
	// クリア背景ハンドル
	DeleteGraph(ClearBGHandle);

	//タイトルボタンハンドル
	DeleteGraph(ClearButtonHandle1);
	DeleteGraph(ClearButtonHandle2);

	//BGMハンドル
	DeleteSoundMem(ClearSoundPath);
	DeleteSoundMem(ButtonSEPath);

	//タイトルシーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
