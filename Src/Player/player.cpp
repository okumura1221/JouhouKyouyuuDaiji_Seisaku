#include "DxLib.h"
#include "player.h"
#include <math.h>
#include <cmath>
#include"../Scene/ScenePlay.h"
#include"../Scene/SceneGameOver.h"
//スクリーンサイズ設定
#define WINDOW_WIDTH			(1280)
#define WINDOW_HEIGHT			(720)						

//プレイヤーが動ける範囲設定
#define PLAYER_MOVE_SPACE_X			(1180)		
#define PLAYER_MOVE_SPACE_Y			(620)						

//画像パス
//#define PLAYER_PATH "Data/Image/Player/player.png"
#define PLAYER_PATH "Data/Image/Player/player_div.png"

#define MOUSE_PATH  "Data/Image/Player/mouse.png"

//プレイヤーが出していい最高スピード
#define PLAYER_SPEED_MAX 6

bool S_Stop_BGM;
int GameOverNumbe=0;

Player::Player()
{
	m_move_vec = { 0 };
	mouse_pos = { 0 };
	m_next_pos = { 0 };
}

Player::~Player()
{
}

//初期化
void Player::Init(int num) {

	SetMouseDispFlag(true);
	if (num == 0)
		m_next_pos = { ((WINDOW_WIDTH / 2) - ((float)playerSize / 2)),
				  ((WINDOW_HEIGHT / 2) - ((float)playerSize / 2)),0 };
	if (num == 1)
		m_next_pos = { ((WINDOW_WIDTH / 2) - ((float)playerSize / 2)),
				  ((WINDOW_HEIGHT / 2) - ((float)playerSize / 2)),0 };
	if (num == 2)
		m_next_pos = { ((WINDOW_WIDTH / 2) + ((float)playerSize / 2)),
				  ((WINDOW_HEIGHT / 2) + ((float)playerSize / 2)),0 };
	if (num == 3)
		m_next_pos = { ((WINDOW_WIDTH / 2) - ((float)playerSize / 2)),
				  ((WINDOW_HEIGHT / 2) - ((float)playerSize / 2)),0 };
	//プレイヤー画像読み込み
	//playerHan = LoadGraph(PLAYER_PATH);
	LoadDivGraph("Data/Image/Player/player_div.png", 12, 4, 3, 64, 64, playerHan);
	mouseHan = LoadGraph(MOUSE_PATH);
	mouse_pos = VGet((WINDOW_WIDTH / 2)+(WINDOW_WIDTH / 4), (WINDOW_HEIGHT / 2), 0);
	speed = 0;
	mauseGetFlag = false;
	mauseOnPicture = false;
	animIndex = 1;

	Walk_Sound[0] = LoadSoundMem("Data/Sound/ashi/0.mp3");
	Walk_Sound[1] = LoadSoundMem("Data/Sound/ashi/1.mp3");
	Walk_Sound[2] = LoadSoundMem("Data/Sound/ashi/2.mp3");
	Walk_Sound[3] = LoadSoundMem("Data/Sound/ashi/3.mp3");
	Walk_Sound[4] = LoadSoundMem("Data/Sound/ashi/4.mp3");
	Walk_Sound[5] = LoadSoundMem("Data/Sound/ashi/5.mp3");
	Walk_Sound[6] = LoadSoundMem("Data/Sound/ashi/6.mp3");
	Walk_Sound[7] = LoadSoundMem("Data/Sound/ashi/7.mp3");
	Walk_Sound[8] = LoadSoundMem("Data/Sound/ashi/8.mp3");
	Walk_Sound[9] = LoadSoundMem("Data/Sound/ashi/9.mp3");
	Walk_Sound[10] = LoadSoundMem("Data/Sound/ashi/10.mp3");
	Walk_Sound[11] = LoadSoundMem("Data/Sound/ashi/11.mp3");
	Walk_Sound[12] = LoadSoundMem("Data/Sound/ashi/12.mp3");

	S_Stop_BGM = false;
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

	//座標を決定
	m_pos = m_next_pos;


	// 一定距離内にマウスポインタがある場合、キャラクターが逃げる
	if (!playerGoalFlag) {
		if (distance < DISTANCE) {
			float angle = atan2(dy, dx); // マウスポインタとキャラクターの角度
			float t = (DISTANCE - distance) / 100; // 距離に応じた補間係数
			float currentSpeed = lerp(BasePlayerSpeed, MaxPlayerSpeed, t);

			speed = currentSpeed;

			m_next_pos.x -= speed * cos(angle); // X方向の移動

			m_next_pos.y -= speed * sin(angle); // Y方向の移動
		}
		else speed = 0;
		//スピードを出しすぎたらゲームオーバー
		if (speed >= PLAYER_SPEED_MAX) {
			S_Stop_BGM = true;
			GameOverNumber = 0;
			g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
		}
	}
	else
		if (distance < (DISTANCE / 4))
		{
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
			{
				stage_change_flag = true;
				g_CurrentSceneID = SCENE_ID_INIT_PLAY;
			}
		}
}

void Player::Fin()
{
}

void Player::Draw() {
	//プレイヤーを描画
	if (speed == 0.0 && !playerGoalFlag)
	{
		changeAnimFlame = 10;
		animFlameCount++;
		if (animFlameCount >= changeAnimFlame) {
			animFlameCount = 0;
			animIndex++;
			if (animIndex >= 4) {
				animIndex = 0;
			}
			else if (animIndex <= 0) {
				animIndex = 3;
			}
		}
	}
	else if (speed != 0.0&&!playerGoalFlag)
	{
		changeAnimFlame = 6;
		animFlameCount++;
		if (animFlameCount >= changeAnimFlame) {
			animFlameCount = 0;
			animIndex++;
			if (animIndex >= 8) {
				animIndex = 4;
			}
			else if (animIndex <= 4) {
				animIndex = 7;
			}
			if (animIndex == 4 || animIndex == 6)
				PlaySoundMem(Walk_Sound
					[GetRand(WALK_SOUND_MAX_NUM - 1)]
					, DX_PLAYTYPE_BACK, true);
		}
	}
	else
	{
		changeAnimFlame = 10;
		animFlameCount++;
		if (animFlameCount >= changeAnimFlame) {
			animFlameCount = 0;
			animIndex++;
			if (animIndex >= 10) {
				animIndex = 8;
			}
			else if (animIndex <= 8) {
				animIndex = 9;
			}
		}
	}
		DrawGraph(m_pos.x, m_pos.y, playerHan[animIndex], true);

	if(mauseOnPicture&& !mauseGetFlag)
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	DrawRotaGraph(mouse_pos.x, mouse_pos.y, 1.0, 0.0, mouseHan, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 進んでいる方向をチェック
// 上下左右の順になっている
void Player::GetMoveDirection(bool* _dirArray) {
	// 右方向のチェック
	if (GetNextPlayerPosX() > GetPlayerPosX()) {
		_dirArray[3] = true;
	}

	// 左方向のチェック
	if (GetNextPlayerPosX() < GetPlayerPosX()) {
		_dirArray[2] = true;
	}
	// 下方向のチェック
	if (GetNextPlayerPosY() > GetPlayerPosY()) {
		_dirArray[1] = true;
	}

	// 上方向のチェック
	if (GetNextPlayerPosY() < GetPlayerPosY()) {
		_dirArray[0] = true;
	}
}

float Player::lerp(float start, float end, float t) {
	return start + t * (end - start);
}

void Player::SetplayerOnSwitchTrue()
{
	playerOnSwitch = true;
}

void Player::SetplayerOnSwitchFalse()
{
	playerOnSwitch = false;
}

void Player::SetplayerGoalFlag()
{
	playerGoalFlag = true;
}

void Player::SetplayerGoal(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}