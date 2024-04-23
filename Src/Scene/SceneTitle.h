#pragma once

// 画像パス
// タイトル背景
#define TITLE_BG_PATH "Data/Image/Title/TitleImage.png"

#define TITLE_BUTTTON_PATH1 "Data/Image/Title/SelectButton.png"
#define TITLE_BUTTTON_PATH2 "Data/Image/Title/SelectButton2.png"

//タイトルBGM
#define TITLE_BGM_PATH "Data/Sound/title.wav"
#define BUTTON_SE_PATH "Data/Sound/click.mp3"

class SceneTitle {
private:
	// タイトル背景ハンドル
	int TitleBGHandle;
	int TitleButtonHandle1, TitleButtonHandle2;

	int mouseX, mouseY;

	int TitleSoundPath;
	int ButtonSEPath;

	int NextSceneCnt;

	bool SceneFlag;

	
public:

	bool clickflag;

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

	void Setclickflag();

	bool Getclickflag(){ return clickflag; };
};
