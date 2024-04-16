#pragma once

// 画像パス
// ゲームオーバー背景
#define GAMEOVER_BG_PATH "Data/Image/BackGround/TentativeGameOverBG.png"

class SceneGameOver {
private:
	// ゲームオーバー背景ハンドル
	int GameOverBGHandle;

public:
	SceneGameOver();
	~SceneGameOver();

	//ゲームオーバーシーン初期化
	void InitGameOver();

	//ゲームオーバーシーン通常処理
	void StepGameOver();

	//ゲームオーバーシーン描画処理
	void DrawGameOver();

	//ゲームオーバーシーン終了処理
	void FinGameOver();
};
