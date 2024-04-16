#pragma once

// 画像パス
// クリア背景
#define CLEAR_BG_PATH "Data/Image/BackGround/TentativeClearBG.png"

class SceneClear {
private:
	// クリア背景ハンドル
	int ClearBGHandle;

public:
	SceneClear();
	~SceneClear();

	//クリアシーン初期化
	void InitClear();

	//クリアシーン通常処理
	void StepClear();

	//クリアシーン描画処理
	void DrawClear();

	//クリアシーン終了処理
	void FinClear();
};
