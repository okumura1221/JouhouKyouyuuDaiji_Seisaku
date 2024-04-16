#include "DxLib.h"
#include "Scene.h"
#include "SceneClear.h"

SceneClear::SceneClear() 
{
	// クリア背景ハンドル
	ClearBGHandle = 0;
}
SceneClear::~SceneClear() { FinClear(); }

//クリアシーン初期化
void SceneClear::InitClear()
{
	// クリア背景ハンドル
	ClearBGHandle = LoadGraph(CLEAR_BG_PATH);

	//クリアシーンループへ
	g_CurrentSceneID = SCENE_ID_LOOP_CLEAR;
}

//クリアシーン通常処理
void SceneClear::StepClear()
{

	// Enterを押したら
	if (InputKey::Push(KEY_INPUT_RETURN))
	{
		// クリアシーンを終了
		FinClear();
	}
}

//クリアシーン描画処理
void SceneClear::DrawClear()
{
	// クリア背景描画
	DrawGraph(0, 0, ClearBGHandle, true);
}

//クリアシーン終了処理
void SceneClear::FinClear()
{
	// クリア背景ハンドル
	DeleteGraph(ClearBGHandle);

	//タイトルシーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
