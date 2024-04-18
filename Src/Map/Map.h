#pragma once

// 各マップのデータ数
const int MAP_DATA_Y = 12;
const int MAP_DATA_X = 20;

// マップサイズ
const int MAP_SIZE = 64;

//マップデータバリエーション


// マップクラス
class Map
{
private:
	// マップチップハンドル
	int mapHandle[4];
	int mapSelect[4];
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

