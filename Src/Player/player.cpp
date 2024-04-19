#include "DxLib.h"
#include "player.h"
#include <math.h>
#include <cmath>
#include "../MyMath/MyMath.h"

//スクリーンサイズ設定
#define WINDOW_WIDTH			(1280)
#define WINDOW_HEIGHT			(720)						

//プレイヤーが動ける範囲設定
#define PLAYER_MOVE_SPACE_X			(1180)		
#define PLAYER_MOVE_SPACE_Y			(620)						

//画像パス
#define PLAYER_PATH "Data/Image/Player/player.png"
#define PLAYER_PATH "Data/Image/Player/player.png"

#define MOUSE_PATH  "Data/Image/Player/mouse.png"

//プレイヤーが出していい最高スピード
#define PLAYER_SPEED_MAX 6

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
	m_pos = { ((WINDOW_WIDTH / 2) - ((float)playerSize / 2)),
			  ((WINDOW_HEIGHT / 2) - ((float)playerSize / 2)) };
	//プレイヤー画像読み込み
	playerHan = LoadGraph(PLAYER_PATH);
	mouseHan = LoadGraph(MOUSE_PATH);
	mouse_pos = VGet((WINDOW_WIDTH / 2)+(WINDOW_WIDTH / 4), (WINDOW_HEIGHT / 2), 0);
	speed = 0;
	mauseGetFlag = false;
	mauseOnPicture = false;
}

void Player::Step() {

	GetMousePoint(&mouseX, &mouseY);
	
	if ((mouse_pos.x - (playerSize / 2)) <= mouseX &&
		mouseX <= (mouse_pos.x + (playerSize / 2)) &&
		(mouse_pos.y - (playerSize / 2)) <= mouseY &&
		mouseY <= (mouse_pos.y + (playerSize / 2)))
	{
		mauseOnPicture = true;
		//マウス画像をクリックする
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//マウスの表示状態を変更
			SetMouseDispFlag(false);
			mauseGetFlag = true;
		}
	}
	else mauseOnPicture = false;
	if(mauseGetFlag)mouse_pos = VGet((float)mouseX, (float)mouseY, 0);
		
	//マウスの位置を取得
	

	// マウスポインタとキャラクターの距離を計算
	int dx = mouse_pos.x - (m_pos.x + ((float)playerSize / 2));
	int dy = mouse_pos.y - (m_pos.y + ((float)playerSize / 2));
	float distance = sqrt(dx * dx + dy * dy);

	// 一定距離内にマウスポインタがある場合、キャラクターが逃げる
	if (distance < DISTANCE) {
		float angle = atan2(dy, dx); // マウスポインタとキャラクターの角度
		float t = (DISTANCE - distance) / 100; // 距離に応じた補間係数
		float currentSpeed = lerp(BasePlayerSpeed, MaxPlayerSpeed, t);

		speed = currentSpeed;

		m_pos.x -= currentSpeed * cos(angle); // X方向の移動

		m_pos.y -= currentSpeed * sin(angle); // Y方向の移動
	}

	//スピードを出しすぎたらゲームオーバー
	if (speed >= PLAYER_SPEED_MAX) {
		SetMouseDispFlag(true);
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}

	////プレイヤーが範囲外に行かない処理
	//if (m_pos.x <= PLAYER_MOVE_SPACE_X)
	//{
	//	m_pos.x = PLAYER_MOVE_SPACE_X;
	//}
	//if (m_pos.x >= WINDOW_WIDTH - PLAYER_MOVE_SPACE_X)
	//{
	//	m_pos.x = WINDOW_WIDTH - PLAYER_MOVE_SPACE_X;
	//}
	//if (m_pos.y <= PLAYER_MOVE_SPACE_Y)
	//{
	//	m_pos.y = PLAYER_MOVE_SPACE_Y;
	//}
	//if (m_pos.y >= WINDOW_HEIGHT - PLAYER_MOVE_SPACE_Y)
	//{
	//	m_pos.y = WINDOW_HEIGHT - PLAYER_MOVE_SPACE_Y;
	//}
}

void Player::Draw() {
	//プレイヤーを描画

	DrawGraph(m_pos.x, m_pos.y, playerHan, true);
	if(mauseOnPicture&& !mauseGetFlag)
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	DrawRotaGraph(mouse_pos.x, mouse_pos.y, 1.0, 0.0, mouseHan, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatString(0, 0, GetColor(255, 0, 0), 
		"プレイヤー座標:X:%f\nプレイヤー座標:Y:%f\nプレイヤー座標:Z:%f"
		, m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 55, GetColor(0, 0, 255),
		"マウス座標:X:%f\nマウス座標:Y:%f\nマウス座標:Z:%f"
		, mouse_pos.x, mouse_pos.y, mouse_pos.z);
	DrawFormatString(0, 110, GetColor(255, 0, 255),
		"加速度:%f", speed);
}

void Player::Fin() {
	//プレイヤー画像の後処理
	DeleteGraph(playerHan);
}


// 進んでいる方向をチェック
// 上下左右の順になっている
void Player::GetMoveDirection(bool* _dirArray) {

}

float Player::lerp(float start, float end, float t) {
	return start + t * (end - start);
}