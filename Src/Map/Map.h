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
	bool Invert_Color_flag[MAP_DATA_Y][MAP_DATA_X] = { false };
	bool Invert_Color_flag_full = false;
public:
	Map();
	~Map();

	// マップデータ
	const int m_MapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };
	int mposX;  //マップ座標

	// 初期化
	void Init(int num);

	// 描画
	void Draw(bool playeron, bool enemyeron);

	void Set_Invert_Color(int y, int x);
	void Set_Invert_Color();

	bool Get_Invert_Color() { return Invert_Color_flag_full; };
};

