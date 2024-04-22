#include "DxLib.h"
#include "Scene.h"
#include "SceneGameOver.h"

SceneGameOver::SceneGameOver()
{
	// ゲームオーバー背景ハンドル
	GameOverBGHandle = 0;
	GameOverTextHandle = 0;
	GameOverText2Handle = 0;
}
SceneGameOver::~SceneGameOver() { FinGameOver(); }

//ゲームオーバーシーン初期化
void SceneGameOver::InitGameOver()
{
	SetMouseDispFlag(true);

	// ゲームオーバー背景ハンドル
	GameOverBGHandle = LoadGraph(GAMEOVER_BG_PATH);
	GameOverTextHandle = LoadGraph(GAMEOVER_TEXT_PATH);
	GameOverText2Handle = LoadGraph(GAMEOVER_TEXT2_PATH);

	//ゲームオーバーループへ
	g_CurrentSceneID = SCENE_ID_LOOP_GAMEOVER;
}

//ゲームオーバーシーン通常処理
void SceneGameOver::StepGameOver()
{
	GetMousePoint(&mouseX, &mouseY);

	if (mouseX >= 273 && mouseX <= 1022 && mouseY >= 588 && mouseY <= 675 &&
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
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

	if (mouseX >= 273 && mouseX <= 1022 && mouseY >= 588 && mouseY <= 675)
	{
		DrawGraph(0, 0, GameOverTextHandle, true);
	}
	else
	{
		DrawGraph(0, 0, GameOverText2Handle, true);
	}
}

//ゲームオーバーシーン終了処理
void SceneGameOver::FinGameOver()
{
	// ゲームオーバー背景ハンドル
	DeleteGraph(GameOverBGHandle);

	//タイトルシーンへ移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
