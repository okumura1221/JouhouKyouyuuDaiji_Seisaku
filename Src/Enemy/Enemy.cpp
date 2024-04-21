#include "DxLib.h"
#include "Enemy.h"
#include "../Player/player.h"
#include <math.h>
#include <cmath>
#include "../MyMath/MyMath.h"

//画像パス
#define PLAYER_PATH "Data/Image/Enemy/player_div.png"

//プレイヤーが出していい最高スピード
#define PLAYER_SPEED_MAX 6

Enemy::Enemy()
{
	m_move_vec = { 0 };
	m_next_pos = { 0 };
	m_next_pos = { 0 };
}

Enemy::~Enemy()
{
}

//初期化
void Enemy::Init() {

	m_next_pos = { ((WINDOW_WIDTH / 4) - ((float)EnemySize / 2)),
			  ((WINDOW_HEIGHT / 4) - ((float)EnemySize / 2)),0 };
	//画像読み込み
	LoadDivGraph("Data/Image/Player/player_div.png", 12, 4, 3, 64, 64, EnemyHan);
	speed = 0;
	animIndex = 1;
}
void Enemy::Step(VECTOR mouse, VECTOR player) {
	VECTOR playerPos = player; // プレイヤーの位置を取得
	VECTOR mousePos = mouse;

	m_pos = m_next_pos;

	int dx_player = player.x - m_pos.x;
	int dy_player = player.y - m_pos.y;
	float distance_player = sqrt(dx_player * dx_player + dy_player * dy_player);
	
	int dx_mouse = mouse.x - (m_pos.x + ((float)EnemySize / 2));
	int dy_mouse = mouse.y - (m_pos.y + ((float)EnemySize / 2));
	float distance_mouse = sqrt(dx_mouse * dx_mouse + dy_mouse * dy_mouse);

	if (distance_mouse < DISTANCE)
	{
		if (distance_player < DISTANCE)
			MouseOrPlayer = true;
		else MouseOrPlayer = false;
	}
	if (distance_player < DISTANCE)
	{
		MouseOrPlayer = true;
	}

	if (MouseOrPlayer)
	{
		if (distance_player < DISTANCE) {
			float angle = atan2(dy_player, dx_player); // マウスポインタとキャラクターの角度
			float t = (DISTANCE - distance_player) / 100; // 距離に応じた補間係数
			float currentSpeed = lerp(BasePlayerSpeed, MaxPlayerSpeed, t);

			speed = currentSpeed;

			m_next_pos.x += speed * cos(angle); // X方向の移動

			m_next_pos.y += speed * sin(angle); // Y方向の移動
		}
		else speed = 0;
	}
	else
	{
		if (distance_mouse < DISTANCE) {
			float angle = atan2(dy_mouse, dx_mouse); // プレイヤーとキャラクターの角度
			float t = (DISTANCE - distance_mouse) / 100; // 距離に応じた補間係数
			float currentSpeed = lerp(BasePlayerSpeed, MaxPlayerSpeed, t);

			speed = currentSpeed;

			m_next_pos.x += speed * cos(angle); // X方向の移動

			m_next_pos.y += speed * sin(angle); // Y方向の移動
		}
		else speed = 0;
	}
}

void Enemy::Fin()
{
}

void Enemy::Draw() {
	//プレイヤーを描画
	if (speed == 0.0 && !EnemyGoalFlag)
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
	else if (speed != 0.0&&!EnemyGoalFlag)
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
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);	
	DrawGraph(m_pos.x, m_pos.y, EnemyHan[animIndex], true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// 進んでいる方向をチェック
// 上下左右の順になっている
void Enemy::GetMoveDirection(bool* _dirArray) {
	// 右方向のチェック
	if (GetNextEnemyPosX() > GetEnemyPosX()) {
		_dirArray[3] = true;
	}

	// 左方向のチェック
	if (GetNextEnemyPosX() < GetEnemyPosX()) {
		_dirArray[2] = true;
	}
	// 下方向のチェック
	if (GetNextEnemyPosY() > GetEnemyPosY()) {
		_dirArray[1] = true;
	}

	// 上方向のチェック
	if (GetNextEnemyPosY() < GetEnemyPosY()) {
		_dirArray[0] = true;
	}
}

float Enemy::lerp(float start, float end, float t) {
	return start + t * (end - start);
}

void Enemy::SetEnemyOnSwitchTrue()
{
	EnemyOnSwitch = true;
}

void Enemy::SetEnemyOnSwitchFalse()
{
	EnemyOnSwitch = false;
}