#pragma once

// 画像パス
// タイトル背景
#define TITLE_BG_PATH "Data/Image/BackGround/TentativeTitleBG.png"

class SceneTitle {
private:
	// タイトル背景ハンドル
	int TitleBGHandle;

public:
	SceneTitle();
	~SceneTitle();

	// タイトルの初期化
	void InitTitle();

	// タイトル通常処理
	void StepTitle();

	// タイトル描画処理
	void DrawTitle();

	// タイトル終了処理
	void FinTitle();
};
