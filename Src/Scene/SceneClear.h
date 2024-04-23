#pragma once

// 画像パス
// クリア背景
#define CLEAR_BG_PATH "Data/Image/Clear/ClearImage.png"

#define CLEAR_BUTTTON_PATH1 "Data/Image/Clear/ClearButton1.png"
#define CLEAR_BUTTTON_PATH2 "Data/Image/Clear/ClearButton2.png"

#define CLEAR_EFFECT_PATH "Data/Image/Clear/ClearEffect.png"

//タイトルBGM
#define CLEAR_BGM_PATH "Data/Sound/ed.wav"
#define CLEAR_BUTTON_SE_PATH "Data/Sound/click.mp3"

class SceneClear {
private:
	// クリア背景ハンドル
	int ClearBGHandle;

	int ClearButtonHandle1, ClearButtonHandle2;

	int ClearEffectHandle[2];
	int ClearEffectposX, ClearEffectposY[2];
	

	int mouseX, mouseY;

	int ClearSoundPath;
	int ButtonSEPath;

public:
	bool clickflag;
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
