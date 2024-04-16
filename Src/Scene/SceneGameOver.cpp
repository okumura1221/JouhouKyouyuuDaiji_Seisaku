#include "DxLib.h"
#include "Scene.h"
#include "SceneGameOver.h"

SceneGameOver::SceneGameOver()
{
	// ゲームオーバー背景ハンドル
	GameOverBGHandle = 0;
}
SceneGameOver::~SceneGameOver() { FinGameOver(); }

//ゲームオーバーシーン初期化
void SceneGameOver::InitGameOver()
{
	// ゲームオーバー背景ハンドル
	GameOverBGHandle = LoadGraph(GAMEOVER_BG_PATH);

	//ゲームオーバーループへ
	g_CurrentSceneID = SCENE_ID_LOOP_GAMEOVER;
}

//ゲームオーバーシーン通常処理
void SceneGameOver::StepGameOver()
{

	// Enterを押したら
	if (InputKey::Push(KEY_INPUT_RETURN))
	{
		// ゲームオーバーシーンを終了
		FinGameOver();
	}
}

//ゲームオーバーシーン描画処理
void SceneGameOver::DrawGameOver()
{
	// ゲームオーバー背景描画
	DrawGraph(0, 0, GameOverBGHandle, true);
}

//ゲームオーバーシーン終了処理
void SceneGameOver::FinGameOver()
{
	// ゲームオーバー背景ハンドル
	DeleteGraph(GameOverBGHandle);

	//タイトルシーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
