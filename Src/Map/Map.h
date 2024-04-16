#pragma once

// 各マップのデータ数
const int MAP_DATA_Y = 25;
const int MAP_DATA_X = 40;

// マップサイズ
const int MAP_SIZE = 32;

// マップクラス
class Map
{
private:
	// マップチップハンドル
	int mapHandle[4];

public:
	Map();
	~Map();

	// マップデータ
	const int m_MapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };
	int mposX;  //マップ座標

	// 初期化
	void Init();

	// 描画
	void Draw();
};

