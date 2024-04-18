#include "DxLib.h"
#include "Scene.h"
#include "ScenePlay.h"
#include"../Map/Map.h"
#include "../Collision/Collision.h"
#include"../Player/player.h"

Player* player;
Map* CMap;
MAPCollision mapcollision;

ScenePlay::ScenePlay()
{
	// プレイ背景ハンドル
	PlayBGHandle = 0;
}
ScenePlay::~ScenePlay() { FinPlay(); }

//プレイシーンの初期化
void ScenePlay::InitPlay()
{
	// プレイ背景ハンドル
	PlayBGHandle = LoadGraph(PLAY_BG_PATH);

	CMap = new Map;

	CMap->Init();

	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//プレイシーン通常処理
void ScenePlay::StepPlay(){
	//マップとの当たり判定
	mapcollision.MapCollision();
	// Enterを押したら
	if (InputKey::Push(KEY_INPUT_RETURN))
	{
		// プレイシーンを終了する
		FinPlay();
	}

	backX--;
	backX2--;
	if (backX == -1280) {
		backX = 1280;
	}
	if (backX2 == -1280) {
		backX2 = 1280;
	}
}

//プレイシーン描画処理
void ScenePlay::DrawPlay()
{
	// タイトル背景描画
	DrawGraph(backX, backY, PlayBGHandle, true);
	DrawGraph(backX2, backY, PlayBGHandle, true);

	CMap->Draw();

}

//プレイシーン終了処理
void ScenePlay::FinPlay()
{
	// タイトル背景ハンドル
	DeleteGraph(PlayBGHandle);

	// クリアシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
}

// マップの当たり判定
void MAPCollision::MapCollision() {

	//for (int index = 0;index < 2;index++) {
	//	// Y方向のみ当たり判定をチェックする
	//	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	//	{
	//		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
	//		{
	//			// ブロック以外は処理しない
	//			if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
	//				continue;

	//			// どの方向に進んでいたかチェック
	//			bool dirArray[4] = { false,false,false,false };
	//			player[index].GetMoveDirection(dirArray);

	//			// 矩形の当たり判定用のデータを準備
	//			// プレイヤーの情報
	//			int Ax = player[index].GetPlayerPosX();
	//			int Ay = player[index].GetPlayerPosY();
	//			int Aw = player[index].GetPlayerSizeX();
	//			int Ah = player[index].GetPlayerSizeY();

	//			// オブジェクトの情報
	//			int Bx = mapIndexX * MAP_SIZE;
	//			int By = mapIndexY * MAP_SIZE;
	//			int Bw = MAP_SIZE;
	//			int Bh = MAP_SIZE;

	//			// ※Y方向のみに移動したと仮定した座標で当たり判定をチェックします
	//			Ay = player[index].GetNextPlayerPosY();
	//			Ax = player[index].GetPlayerPosX();

	//			// 当たっているかチェック
	//			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
	//				// 上方向の修正
	//				if (dirArray[0]) {
	//					// めり込み量を計算する
	//					int overlap = By + Bh - Ay;
	//					player[index].SetPlayerNextPosY(Ay + overlap);
	//				}

	//				// 下方向の修正
	//				if (dirArray[1]) {
	//					// めり込み量を計算する
	//					int overlap = Ay + Ah - By;
	//					player[index].SetPlayerNextPosY(Ay - overlap);

	//				}
	//			}
	//		}
	//	}
	//	// X方向のみ当たり判定をチェックする
	//	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	//	{
	//		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
	//		{
	//			// ブロック以外は処理しない
	//			if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
	//				continue;

	//			// どの方向に進んでいたかチェック
	//			// ※Playerクラスに進む方向をチェックする関数を準備しています。
	//			bool dirArray[4] = { false,false,false,false };
	//			player[index].GetMoveDirection(dirArray);

	//			// 矩形の当たり判定用のデータを準備
	//			// プレイヤーの情報
	//			int Ax = player[index].GetPlayerPosX();
	//			int Ay = player[index].GetPlayerPosY();
	//			int Aw = player[index].GetPlayerSizeX();
	//			int Ah = player[index].GetPlayerSizeY();

	//			// オブジェクトの情報
	//			int Bx = mapIndexX * MAP_SIZE;
	//			int By = mapIndexY * MAP_SIZE;
	//			int Bw = MAP_SIZE;
	//			int Bh = MAP_SIZE;

	//			// 矩形の当たり判定用のデータを準備
	//			// ※X方向のみに移動したと仮定した座標で当たり判定をチェックします
	//			Ay = player[index].GetNextPlayerPosY();
	//			Ax = player[index].GetNextPlayerPosX();

	//			// 当たっているかチェック
	//			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
	//				// 左方向の修正
	//				if (dirArray[2]) {
	//					// めり込み量を計算する
	//					int overlap = Bx + Bw - Ax;
	//					player[index].SetPlayerNextPosX(Ax + overlap);
	//				}

	//				// 右方向の修正
	//				if (dirArray[3]) {
	//					// めり込み量を計算する
	//					int overlap = Ax + Aw - Bx;
	//					player[index].SetPlayerNextPosX(Ax - overlap);
	//				}
	//			}
	//		}
	//	}
	//}
}