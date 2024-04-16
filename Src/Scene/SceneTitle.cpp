#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle() 
{
	// タイトル背景ハンドル
	TitleBGHandle = 0;
}
SceneTitle::~SceneTitle() { FinTitle(); }

// タイトルの初期化
void SceneTitle::InitTitle()
{
	// タイトル背景ハンドル
	TitleBGHandle = LoadGraph(TITLE_BG_PATH);

	// タイトルループへ
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

// タイトル通常処理
void SceneTitle::StepTitle()
{

	// Enterを押したら
	if(InputKey::Push(KEY_INPUT_RETURN))
	{
		// タイトルシーンを終了
		FinTitle();
	}
}

// タイトル描画処理
void SceneTitle::DrawTitle()
{
	// タイトル背景描画
	DrawGraph(0, 0, TitleBGHandle, true);
}

// タイトル終了処理
void SceneTitle::FinTitle()
{
	// タイトル背景ハンドル
	DeleteGraph(TitleBGHandle);

	// プレイシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
