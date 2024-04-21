#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle() 
{
	SetMouseDispFlag(true);

	// タイトル背景ハンドル
	TitleBGHandle = 0;

	TitleButtonHandle1 = 0;
	TitleButtonHandle2 = 0;

	//TitleSoundPath = 0;
}
SceneTitle::~SceneTitle() { FinTitle(); }

// タイトルの初期化
void SceneTitle::InitTitle()
{
	// タイトル背景ハンドル
	TitleBGHandle = LoadGraph(TITLE_BG_PATH);

	//タイトルボタンハンドル
	TitleButtonHandle1 = LoadGraph(TITLE_BUTTTON_PATH1);
	TitleButtonHandle2 = LoadGraph(TITLE_BUTTTON_PATH2);

	//サウンドハンドル
	TitleSoundPath = LoadSoundMem(TITLE_BGM_PATH);

	PlaySoundMem(TitleSoundPath, DX_PLAYTYPE_BACK, true);
	// タイトルループへ
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

// タイトル通常処理
void SceneTitle::StepTitle()
{
	GetMousePoint(&mouseX, &mouseY);


	

	// Enterを押したら
	//if(InputKey::Push(KEY_INPUT_RETURN))
	//{
	//	// タイトルシーンを終了
	//	FinTitle();
	//}

	//タイトルボタンを押したら
	if (mouseX>=273&&mouseX<=1022&&mouseY >= 588&&mouseY<=675&&
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		// タイトルシーンを終了
		FinTitle();
	}
}

// タイトル描画処理
void SceneTitle::DrawTitle()
{
	// タイトル背景描画
	DrawGraph(0, 0, TitleBGHandle, true);

	//タイトルボタン描画
	if (mouseX >= 273 && mouseX <= 1022 && mouseY >= 588 && mouseY <= 675)
	{
	   DrawGraph(0, 0, TitleButtonHandle2, true);
	}
	else
	{
		DrawGraph(-4, -4, TitleButtonHandle1, true);
	}

	//座標確認用
   /* DrawFormatString(0, 55, GetColor(0, 0, 255),
		"マウス座標:X:%d\nマウス座標:Y:%d"
		, mouseX, mouseY);*/
}

// タイトル終了処理
void SceneTitle::FinTitle()
{
	// タイトル背景ハンドル
	DeleteGraph(TitleBGHandle);

	//タイトルボタンハンドル
	DeleteGraph(TitleButtonHandle1);
	DeleteGraph(TitleButtonHandle2);

	//BGMハンドル
	DeleteSoundMem(TitleSoundPath);

	// プレイシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
