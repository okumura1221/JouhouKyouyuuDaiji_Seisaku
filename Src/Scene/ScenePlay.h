#pragma once

// 画像パス
// プレイ背景
#define PLAY_BG_PATH "Data/Image/BackGround/back.png"

class ScenePlay {
private:
	// プレイ背景ハンドル
	int PlayBGHandle;
	int backX = 0;
	int backX2 = 1280;
	int backY = 0;

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

struct MAPCollision
{
	// マップの当たり判定
	void MapCollision();

};