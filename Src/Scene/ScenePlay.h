#pragma once

// 画像パス
// プレイ背景
#define PLAY_BG_PATH "Data/Image/Play/back.png"
#define BACK_MAX_NUM 2

#define TEXT_PATH	 "Data/Image/Play/text.png"

#define STAGE_MAX_NUM 4

class ScenePlay {
private:
	// プレイ背景ハンドル
	int PlayBGHandle[BACK_MAX_NUM];
	int backX[BACK_MAX_NUM] = { 0 };
	int	backY = 0;

	//テキストハンドル
	int TextHan = 0;

	int stage_num = 0;
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

	struct MAPCollision
	{
		// マップの当たり判定
		void MapCollision(int num);

	};
	int Getstage_num() { return stage_num; }

	void  Setstage_num(int num);
};
