#pragma once

// 画像パス
// ゲームオーバー背景
#define GAMEOVER_BG_PATH_1 "Data/Image/Gameover/over1.png"
#define GAMEOVER_BG_PATH_2 "Data/Image/Gameover/over2.png"
#define GAMEOVER_BG_PATH_3 "Data/Image/Gameover/over3.png"
#define GAMEOVER_TEXT_PATH "Data/Image/Gameover/overtext1.png"
#define GAMEOVER_TEXT2_PATH "Data/Image/Gameover/overtext2.png"

extern int GameOverNumber;

class SceneGameOver {
private:
	// ゲームオーバー背景ハンドル
	int GameOverBGHandle[3];
	int GameOverTextHandle;
	int GameOverText2Handle;

	int mouseX, mouseY;

public:
	int BGM = 0;

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
