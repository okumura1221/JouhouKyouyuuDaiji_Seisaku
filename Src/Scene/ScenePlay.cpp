#include "DxLib.h"
#include "Scene.h"
#include "ScenePlay.h"
#include"../Map/Map.h"
#include "../Collision/Collision.h"
#include"../Player/player.h"

Player* player;
Map* CMap;
ScenePlay::MAPCollision mapcollision;

ScenePlay::ScenePlay()
{
	// プレイ背景ハンドル
	for (int i = 0;i < BACK_MAX_NUM;i++)
	PlayBGHandle[i] = 0;
}

ScenePlay::~ScenePlay() { FinPlay(); }

//プレイシーンの初期化
void ScenePlay::InitPlay()
{
	
	// プレイ背景ハンドル
	for (int i = 0;i < BACK_MAX_NUM;i++)
	{
		PlayBGHandle[i] = LoadGraph(PLAY_BG_PATH);
	}

	TextHan = LoadGraph(TEXT_PATH);

	backX[0] = 0;
	backX[1] = 1280;

	player = new Player;
	CMap = new Map;

	CMap->Init();
	player->Init();
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイシーン通常処理
void ScenePlay::StepPlay(){
	
	// Enterを押したら
	if (InputKey::Push(KEY_INPUT_RETURN))
	{
		// プレイシーンを終了する
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}

	player->Step();
	//マップとの当たり判定
	mapcollision.MapCollision();

	//背景スクロール処理
	for (int i = 0;i < BACK_MAX_NUM;i++)
	{
		backX[i]--;
		if (backX[i] == -1280)backX[i] = 1280;
	}
}

//プレイシーン描画処理
void ScenePlay::DrawPlay()
{
	// タイトル背景描画
	for (int i = 0; i < BACK_MAX_NUM; i++) {
		DrawGraph(backX[i], backY, PlayBGHandle[i], true);
	}

	CMap->Draw();
	player->Draw();
	DrawGraph(10, 50, TextHan, true);
}

//プレイシーン終了処理
void ScenePlay::FinPlay()
{
	delete player;
	player = nullptr;
	delete CMap;
	CMap = nullptr;

	for (int i = 0;i < BACK_MAX_NUM;i++)
		DeleteGraph(PlayBGHandle[i]);

	// クリアシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
}

// マップの当たり判定
void ScenePlay::MAPCollision::MapCollision() {

	// Y方向のみ当たり判定をチェックする
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// どの方向に進んでいたかチェック
			bool dirArray[4] = { false,false,false,false };
			player->GetMoveDirection(dirArray);
			// 矩形の当たり判定用のデータを準備
			// プレイヤーの情報
			int Ax = player->GetPlayerPosX();
			int Ay = player->GetPlayerPosY();
			int Aw = player->GetPlayerSizeX();
			int Ah = player->GetPlayerSizeY();

			// オブジェクトの情報
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// ※Y方向のみに移動したと仮定した座標で当たり判定をチェックします
			Ay = player->GetNextPlayerPosY();
			Ax = player->GetPlayerPosX();

			// 当たっているかチェック
			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {


				// ブロック以外の場所には進めない
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
				{
					// 上方向の修正
					if (dirArray[0]) {
						// めり込み量を計算する
						int overlap = By + Bh - Ay;
						player->SetPlayerNextPosY(Ay + overlap);
					}

					// 下方向の修正
					if (dirArray[1]) {
						// めり込み量を計算する
						int overlap = Ay + Ah - By;
						player->SetPlayerNextPosY(Ay - overlap);

					}
				}
				//水に触れると画面遷移
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 4)
					g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
			}

		}
	}
	// X方向のみ当たり判定をチェックする
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{

			// どの方向に進んでいたかチェック
			// ※Playerクラスに進む方向をチェックする関数を準備しています。
			bool dirArray[4] = { false,false,false,false };
			player->GetMoveDirection(dirArray);

			// 矩形の当たり判定用のデータを準備
			// プレイヤーの情報
			int Ax = player->GetPlayerPosX();
			int Ay = player->GetPlayerPosY();
			int Aw = player->GetPlayerSizeX();
			int Ah = player->GetPlayerSizeY();

			// オブジェクトの情報
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// 矩形の当たり判定用のデータを準備
			// ※X方向のみに移動したと仮定した座標で当たり判定をチェックします
			Ay = player->GetNextPlayerPosY();
			Ax = player->GetNextPlayerPosX();

			// 当たっているかチェック
			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
				// ブロック以外の場所には進めない
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
				{
					// 左方向の修正
					if (dirArray[2]) {
						// めり込み量を計算する
						int overlap = Bx + Bw - Ax;
						player->SetPlayerNextPosX(Ax + overlap);
					}

					// 右方向の修正
					if (dirArray[3]) {
						// めり込み量を計算する
						int overlap = Ax + Aw - Bx;
						player->SetPlayerNextPosX(Ax - overlap);
					}
				}
				//水に触れると画面遷移
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 4)
					g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
			}

		}
	}
}