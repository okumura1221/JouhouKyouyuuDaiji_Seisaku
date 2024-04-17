#include "map.h"
#include "DxLib.h"
#include "../Player/player.h"

//マップ処理

// 初期化リストでconstのメンバ変数を初期化
//ステージ構成
Map::Map() :m_MapData{}
{
	mapHandle[0] = -1;
	mapHandle[1] = -1;
	mapHandle[2] = -1;
	mapHandle[3] = -1;
}

Map::~Map() {}

void Map::Init() {
	// 画像の読み込み
	LoadDivGraph("Data/Image/Map/map.png", 4, 2, 2, 64, 64, mapHandle);

	// マップデータを読み込む
	FILE* fp;
	fopen_s(&fp, "Data/map.csv", "r"); // ファイルを開く
	if (fp == NULL) // ファイルが開けなかったら
	{
		DrawString(0, 0, "dgsgh", GetColor(255, 255, 255));
		return; // 終了
	}
	for (int i = 0; i < MAP_DATA_Y; i++) // マップの高さ分繰り返す
	{
		for (int j = 0; j < MAP_DATA_X; j++) // マップの幅分繰り返す
		{
			fscanf_s(fp, "%d,", &m_MapData[i][j]); // マップデータを読み込む
		}
	}
	fclose(fp); // ファイルを閉じる
}



void Map::Draw() {

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// ブロックを描画
			if (m_MapData[y][x] != 0) {
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHandle[m_MapData[y][x] - 1], true);
			}
		}
	}
}

