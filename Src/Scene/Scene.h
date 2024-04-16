#pragma once
#include "../Input/Input.h"

//ウィンドウサイズ
#define	WINDOW_WIDTH	1280	// X方向の画面サイズを指定
#define	WINDOW_HEIGHT	720		// Y方向の画面サイズを指定

enum SCENE_ID
{
	//タイトルシーンのID
	SCENE_ID_INIT_TITLE,	//初期化
	SCENE_ID_LOOP_TITLE,	//ループ
	SCENE_ID_FIN_TITLE,		//終了

	//プレイシーンのID
	SCENE_ID_INIT_PLAY,		//初期化
	SCENE_ID_LOOP_PLAY,		//ループ
	SCENE_ID_FIN_PLAY,		//終了

	//クリアシーンのID
	SCENE_ID_INIT_CLEAR,	//初期化
	SCENE_ID_LOOP_CLEAR,	//ループ
	SCENE_ID_FIN_CLEAR,		//終了

	//ゲームオーバーのID
	SCENE_ID_INIT_GAMEOVER,	//初期化
	SCENE_ID_LOOP_GAMEOVER,	//ループ
	SCENE_ID_FIN_GAMEOVER,	//終了
};

//現在のシーンID
extern SCENE_ID g_CurrentSceneID;