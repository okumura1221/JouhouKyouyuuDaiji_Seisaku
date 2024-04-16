#include "DxLib.h"					// DXライブラリのインクルード
#include "FrameRate/FrameRate.h"	// フレームレートのインクルード
#include "Input/Input.h"			// インプット系のインクルード
#include "Scene/Scene.h"			// シーンヘッダーのインクルード
#include "Scene/SceneClear.h"		// クリアシーンのインクルード
#include "Scene/SceneGameOver.h"	// ゲームオーバーのインクルード
#include "Scene/ScenePlay.h"		//  シーンプレイのインクルード
#include "Scene/SceneTitle.h"		// シーンタイトルのインクウード

// 現在のシーンID
SCENE_ID g_CurrentSceneID = SCENE_ID_INIT_TITLE;

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// 画面サイズを変更
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);

	//入力制御初期化
	InitInput();
	
	//Class
	SceneTitle    Title;
	ScenePlay     Play;
	SceneClear    Clear;
	SceneGameOver GameOver;

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);	//システムに処理を返す

		//FPS処理
		ProcessingFPS();

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//エスケープキーが押されたら終了
			break;
		}

		//画面に表示されたものを初期化
		ClearDrawScreen();

		//入力制御ステップ
		StepInput();

		//シーンIDによって処理の振り分け
		switch (g_CurrentSceneID)
		{

		case SCENE_ID_INIT_TITLE:
		{
			//タイトル初期化
			Title.InitTitle();

		}//SCENE_ID_TITLE終わりの括弧
		break;

		case SCENE_ID_LOOP_TITLE:
		{
			//タイトル描画処理
			Title.DrawTitle();

			//タイトル通常処理
			Title.StepTitle();

		}//SCENE_ID_TITLE終わりの括弧
		break;

		case SCENE_ID_FIN_TITLE:
		{
			//タイトル終了処理
			Title.FinTitle();
		}
		break;

		case SCENE_ID_INIT_PLAY:
		{
			//プレイシーンの初期化
			Play.InitPlay();

		}//SCENE_ID_INIT_PLAY

		break;

		case SCENE_ID_LOOP_PLAY:
		{
			//プレイシーン通常処理
			Play.StepPlay();

			//プレイシーン描画処理
			Play.DrawPlay();

		}//SCENE_ID_LOOP_PLAY終わりの括弧
		break;

		case SCENE_ID_FIN_PLAY:
		{
			//プレイシーン終了処理
			Play.FinPlay();
		}
		break;

		case SCENE_ID_INIT_CLEAR:
		{
			//クリアシーン初期化
			Clear.InitClear();

		}//SCENE_ID_INIT_CLEAR終わりの括弧
		break;

		case SCENE_ID_LOOP_CLEAR:
		{
			//クリアシーン通常処理
			Clear.StepClear();

			//クリアシーン描画処理
			Clear.DrawClear();

		}//SCENE_ID_LOOP_CLEAR終わりの括弧
		break;

		case SCENE_ID_FIN_CLEAR:
		{
			//クリアシーン終了処理
			Clear.FinClear();
		}
		break;

		case SCENE_ID_INIT_GAMEOVER:
		{

			//ゲームオーバーシーン初期化
			GameOver.InitGameOver();

		}//SCENE_ID_INIT_CLEAR終わりの括弧
		break;

		case SCENE_ID_LOOP_GAMEOVER:
		{

			//ゲームオーバーシーン通常処理
			GameOver.StepGameOver();

			//ゲームオーバーシーン描画処理
			GameOver.DrawGameOver();

		}//SCENE_ID_LOOP_CLEAR終わりの括弧
		break;

		case SCENE_ID_FIN_GAMEOVER:
		{

			//ゲームオーバーシーン終了処理
			GameOver.FinGameOver();

		}//SCENE_ID_FIN_CLEAR終わりの括弧
		break;

		}//シーン振り分けのswitch文

		//FPS計算
		CalcFPS();

		//FPS表示
		DrawFPS();

		ScreenFlip();
		
	}

	//最後に１回だけやる処理をここに書く
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

