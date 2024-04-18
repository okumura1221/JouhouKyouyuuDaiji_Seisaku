#include "DxLib.h"
#include "player.h"
#include "math.h"
#include "../MyMath/MyMath.h"

//スクリーンサイズ設定
#define WINDOW_WIDTH			(1280)
#define WINDOW_HEIGHT			(720)						

//プレイヤーが動ける範囲設定
#define PLAYER_MOVE_SPACE_X			(1180)		
#define PLAYER_MOVE_SPACE_Y			(620)						

//画像パス
#define PLAYER_PATH "Data/Image/Player/player.png"
#define MOUSE_PATH  "Data/Image/Player/mouse.png"

Player::Player()
{
	m_move_vec = { 0 };
	mouse_pos = { 0 };
}

Player::~Player()
{
	Fin();
}

//初期化
void Player::Init() {
	//m_pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2,0 };

	//プレイヤー画像読み込み
	playerHan = LoadGraph(PLAYER_PATH);
	mouseHan = LoadGraph(MOUSE_PATH);
}

void Player::Step() {
	//マウスの位置を取得
	GetMousePoint(&mouseX, &mouseY);
	mouse_pos = VGet((float)mouseX, (float)mouseY, 0);

	//動く向きと速さ
	m_move_vec = GetVector(mouse_pos, m_pos, GetInverseProportion(GetDistance(mouse_pos, m_pos), PLAYER_SPEED));

	//マウスポインタの位置からプレイヤーが逃げる
	m_pos.x += m_move_vec.x;
	m_pos.y += m_move_vec.y;
	m_pos.z += m_move_vec.z;

	//プレイヤーが範囲外に行かない処理
	if (m_pos.x <= PLAYER_MOVE_SPACE_X)
	{
		m_pos.x = PLAYER_MOVE_SPACE_X;
	}
	if (m_pos.x >= WINDOW_WIDTH - PLAYER_MOVE_SPACE_X)
	{
		m_pos.x = WINDOW_WIDTH - PLAYER_MOVE_SPACE_X;
	}
	if (m_pos.y <= PLAYER_MOVE_SPACE_Y)
	{
		m_pos.y = PLAYER_MOVE_SPACE_Y;
	}
	if (m_pos.y >= WINDOW_HEIGHT - PLAYER_MOVE_SPACE_Y)
	{
		m_pos.y = WINDOW_HEIGHT - PLAYER_MOVE_SPACE_Y;
	}
}

void Player::Draw() {
	//プレイヤーを描画
	DrawGraph(m_pos.x, m_pos.y, playerHan, true);
	DrawGraph(mouse_pos.x, mouse_pos.y, mouseHan, true);

	DrawFormatString(0, 0, GetColor(255, 0, 0), 
		"プレイヤー座標:X:%f\nプレイヤー座標:Y:%f\nプレイヤー座標:Z:%f"
		, m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 55, GetColor(255, 0, 0),
		"マウス座標:X:%f\nマウス座標:Y:%f\nマウス座標:Z:%f"
		, mouse_pos.x, mouse_pos.y, mouse_pos.z);
}

void Player::Fin() {
	//プレイヤー画像の後処理
	DeleteGraph(playerHan);
}


// 進んでいる方向をチェック
// 上下左右の順になっている
void Player::GetMoveDirection(bool* _dirArray) {

}
