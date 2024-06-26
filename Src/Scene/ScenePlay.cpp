#include "DxLib.h"
#include "Scene.h"
#include "ScenePlay.h"
#include"../Map/Map.h"
#include "../Collision/Collision.h"
#include"../Player/player.h"
#include"../Enemy/Enemy.h"
#include"../Scene/SceneGameOver.h"
Player* player;
Enemy* enemy;
Map* CMap;
ScenePlay::MAPCollision mapcollision;
Collision c;

bool stage_change_flag;
int GameOverNumber;

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
	GameOverNumber = 0;
	for(int i=0;i<3;i++)
	StopSoundMem(BGM[i]);
	if (stage_num < STAGE_MAX_NUM)
	{
		if (stage_change_flag) {
			Setstage_num(Getstage_num() + 1);
			stage_change_flag = false;
		}
	}
	
	// プレイ背景ハンドル
	for (int i = 0;i < BACK_MAX_NUM;i++)
	{
		PlayBGHandle[i] = LoadGraph(PLAY_BG_PATH);
	}

	TextHan = LoadGraph(TEXT_PATH);

	backX[0] = 0;
	backX[1] = 1280;

	S_Stop_BGM = false;

	player = new Player;
	enemy = new Enemy;
	CMap = new Map;

	BGM[0] = LoadSoundMem("Data/Sound/BGM/1.wav");
	BGM[1] = LoadSoundMem("Data/Sound/BGM/2.wav");
	BGM[2] = LoadSoundMem("Data/Sound/BGM/3.wav");

	stage_change_flag = false;
	CMap->Init(stage_num);
	player->Init(stage_num);
	enemy->Init(stage_num);
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
	if (stage_num == STAGE_MAX_NUM)g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	PlaySoundMem(BGM[GetRand(2)], DX_PLAYTYPE_LOOP, true);
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
	enemy->Step(player->GetMouseVector(), player->GetplayerVector());
	//マップとの当たり判定
	mapcollision.MapCollision(0);
	mapcollision.MapCollision(1);

	if(c.Circle((int)player->GetPlayerSizeX() / 2,
		(int)enemy->GetEnemySizeX() / 2,
		(int)player->GetNextPlayerPosX(),
		(int)enemy->GetEnemyPosX(),
		(int)player->GetNextPlayerPosY(),
		(int)enemy->GetEnemyPosY()))
	{
		GameOverNumber = 2;
		S_Stop_BGM = true;
		g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
	}

	if (S_Stop_BGM)
	{
		for (int i = 0; i < 3; i++)
			StopSoundMem(BGM[i]);
	}
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

	CMap->Draw(player->GetplayerOnSwitch(), enemy->GetEnemyOnSwitch());
	player->Draw();
	enemy->Draw();
	DrawGraph(10, 50, TextHan, true);
}

//プレイシーン終了処理
void ScenePlay::FinPlay()
{
	
	delete player;
	player = nullptr;
	delete CMap;
	CMap = nullptr;
	delete enemy;
	enemy = nullptr;
	for (int i = 0;i < BACK_MAX_NUM;i++)
		DeleteGraph(PlayBGHandle[i]);
	for (int i = 0; i < 3; i++)
	DeleteSoundMem(BGM[i]);

	Setstage_num(0);
	// クリアシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
}

// マップの当たり判定
void ScenePlay::MAPCollision::MapCollision(int num) {

	// Y方向のみ当たり判定をチェックする
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// どの方向に進んでいたかチェック
			bool dirArray[4] = { false,false,false,false };
			if (num == 0)
			{
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
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 0 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 6 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						!CMap->Get_Invert_Color()||
						CMap->m_MapData[mapIndexY][mapIndexX] == 2 &&
						CMap->Get_Invert_Color())
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
					{
						S_Stop_BGM = true;
						GameOverNumber = 1;
						g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
					}
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 5)
					{
						player->SetplayerGoalFlag();
					}
					//スイッチを押すと色が反転
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 8)
						player->SetplayerOnSwitchTrue();
					else if (CMap->m_MapData[mapIndexY][mapIndexX] != 8)
						player->SetplayerOnSwitchFalse();
					if (player->GetplayerOnSwitch())
					{
						CMap->Set_Invert_Color(mapIndexY, mapIndexX);
						CMap->Set_Invert_Color();
					}
					/*if (CMap->m_MapData[mapIndexY][mapIndexX] == 7)
						if (player->GetplayerOnSwitch())
							CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
				}
			}
			if (num == 1)
			{
				enemy->GetMoveDirection(dirArray);
				// 矩形の当たり判定用のデータを準備

					// プレイヤーの情報
				int Ax = enemy->GetEnemyPosX();
				int Ay = enemy->GetEnemyPosY();
				int Aw = enemy->GetEnemySizeX();
				int Ah = enemy->GetEnemySizeY();

				// オブジェクトの情報
				int Bx = mapIndexX * MAP_SIZE;
				int By = mapIndexY * MAP_SIZE;
				int Bw = MAP_SIZE;
				int Bh = MAP_SIZE;

				// ※Y方向のみに移動したと仮定した座標で当たり判定をチェックします
				Ay = enemy->GetNextEnemyPosY();
				Ax = enemy->GetEnemyPosX();

				// 当たっているかチェック
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {


					// ブロック以外の場所には進めない
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 0 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 6 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 && 
						!CMap->Get_Invert_Color() ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 2 &&
						CMap->Get_Invert_Color())
					{
						// 上方向の修正
						if (dirArray[0]) {
							// めり込み量を計算する
							int overlap = By + Bh - Ay;
							enemy->SetEnemyNextPosY(Ay + overlap);
						}

						// 下方向の修正
						if (dirArray[1]) {
							// めり込み量を計算する
							int overlap = Ay + Ah - By;
							enemy->SetEnemyNextPosY(Ay - overlap);
						}
					}
					//スイッチを押すと色が反転
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 8)
						enemy->SetEnemyOnSwitchTrue();
					else if (CMap->m_MapData[mapIndexY][mapIndexX] != 8)
						enemy->SetEnemyOnSwitchFalse();
					if (enemy->GetEnemyOnSwitch())
					{
						CMap->Set_Invert_Color(mapIndexY, mapIndexX);
						CMap->Set_Invert_Color();
					}
					/*if (CMap->m_MapData[mapIndexY][mapIndexX] == 7)
						if (enemy->GetEnemyOnSwitch())
							CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
				}
				
				
			}
			/*if (enemy->GetEnemyOnSwitch() && CMap->m_MapData[mapIndexY][mapIndexX] == 7)
				CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
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
			if (num == 0)
			{
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
				Ay = player->GetPlayerPosY();
				Ax = player->GetNextPlayerPosX();

				// 当たっているかチェック
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
					// ブロック以外の場所には進めない
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 0 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 6||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						!CMap->Get_Invert_Color() ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 2 &&
						CMap->Get_Invert_Color())
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
					{
						S_Stop_BGM = true;
						GameOverNumber = 1;
						g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
					}
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 5)
					{
						player->SetplayerGoalFlag();
						player->SetplayerGoal(Bx, By);
					}
					//スイッチを押すと色が反転
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 8)
						player->SetplayerOnSwitchTrue();
					else if (CMap->m_MapData[mapIndexY][mapIndexX] != 8)
						player->SetplayerOnSwitchFalse();
					if (player->GetplayerOnSwitch())
					{
						CMap->Set_Invert_Color(mapIndexY, mapIndexX);
						CMap->Set_Invert_Color();
					}			
					/*if (CMap->m_MapData[mapIndexY][mapIndexX] == 7)
						if (player->GetplayerOnSwitch())
							CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
				}
			}
			if (num == 1)
			{
				enemy->GetMoveDirection(dirArray);

				// 矩形の当たり判定用のデータを準備
				// プレイヤーの情報
				int Ax = enemy->GetEnemyPosX();
				int Ay = enemy->GetEnemyPosY();
				int Aw = enemy->GetEnemySizeX();
				int Ah = enemy->GetEnemySizeY();

				// オブジェクトの情報
				int Bx = mapIndexX * MAP_SIZE;
				int By = mapIndexY * MAP_SIZE;
				int Bw = MAP_SIZE;
				int Bh = MAP_SIZE;

				// 矩形の当たり判定用のデータを準備
				// ※X方向のみに移動したと仮定した座標で当たり判定をチェックします
				Ay = enemy->GetEnemyPosY();
				Ax = enemy->GetNextEnemyPosX();

				// 当たっているかチェック
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
					// ブロック以外の場所には進めない
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 0 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 6 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7&&
						!CMap->Get_Invert_Color() ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 2 &&
						CMap->Get_Invert_Color())
					{
						// 左方向の修正
						if (dirArray[2]) {
							// めり込み量を計算する
							int overlap = Bx + Bw - Ax;
							enemy->SetEnemyNextPosX(Ax + overlap);
						}
						// 右方向の修正
						if (dirArray[3]) {
							// めり込み量を計算する
							int overlap = Ax + Aw - Bx;
							enemy->SetEnemyNextPosX(Ax - overlap);
						}
					}
					//スイッチを押すと色が反転
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 8)
						enemy->SetEnemyOnSwitchTrue();
					else if(CMap->m_MapData[mapIndexY][mapIndexX] != 8)
						enemy->SetEnemyOnSwitchFalse();
					if (enemy->GetEnemyOnSwitch())
					{
						CMap->Set_Invert_Color(mapIndexY, mapIndexX);
						CMap->Set_Invert_Color();
					}			
					/*if (CMap->m_MapData[mapIndexY][mapIndexX] == 7)
						if (enemy->GetEnemyOnSwitch())
							CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
				
				}
				
			}
			//if (enemy->GetEnemyOnSwitch() && CMap->m_MapData[mapIndexY][mapIndexX] == 7)
				//CMap->Set_Invert_Color(mapIndexY, mapIndexX);
		}
	}
}
void  ScenePlay::Setstage_num(int num)
{
	stage_num = num;
}
