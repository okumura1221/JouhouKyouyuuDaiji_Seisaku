#include "DxLib.h"
#include "Scene.h"
#include "ScenePlay.h"

ScenePlay::ScenePlay() 
{
	// プレイ背景ハンドル
	PlayBGHandle = 0;
}
ScenePlay::~ScenePlay() { FinPlay(); }

//プレイシーンの初期化
void ScenePlay::InitPlay()
{
	// プレイ背景ハンドル
	PlayBGHandle = LoadGraph(PLAY_BG_PATH);

	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイシーン通常処理
void ScenePlay::StepPlay()
{

	// Enterを押したら
	if (InputKey::Push(KEY_INPUT_RETURN))
	{
		// プレイシーンを終了する
		FinPlay();
	}
}

//プレイシーン描画処理
void ScenePlay::DrawPlay()
{
	// タイトル背景描画
	DrawGraph(0, 0, PlayBGHandle, true);
}

//プレイシーン終了処理
void ScenePlay::FinPlay()
{
	// タイトル背景ハンドル
	DeleteGraph(PlayBGHandle);

	// クリアシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
}
