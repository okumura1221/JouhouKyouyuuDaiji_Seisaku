#pragma once

// 画像パス
// プレイ背景
#define PLAY_BG_PATH "Data/Image/BackGround/TentativePlayBG.png"

class ScenePlay {
private:
	// プレイ背景ハンドル
	int PlayBGHandle;

public:
	ScenePlay();
	~ScenePlay();

	// プレイシーンの初期化
	void InitPlay();

	// プレイシーン通常処理
	void StepPlay();

	// プレイシーン描画処理
	void DrawPlay();

	// プレイシーン終了処理
	void FinPlay();
};
