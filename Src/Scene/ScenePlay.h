#pragma once

// 画像パス
// プレイ背景
#define PLAY_BG_PATH "Data/Image/BackGround/back.png"
#define BACK_MAX_NUM 2
class ScenePlay {
private:
	// プレイ背景ハンドル
<<<<<<< HEAD
	int PlayBGHandle[BACK_MAX_NUM];
	int backX[BACK_MAX_NUM] = { 0,-1280 };
	int	backY = -1;
=======
	int PlayBGHandle;
	int backX = 0;
	int backX2 = 1280;
	int backY = 0;
>>>>>>> a53e01db79afa4726d10b5e7d9caedef1d723562

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