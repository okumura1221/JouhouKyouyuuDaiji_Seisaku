#include "DxLib.h"
#include "Enemy.h"
#include "../Player/player.h"
#include <math.h>
#include <cmath>
#include "../MyMath/MyMath.h"

//�摜�p�X
#define PLAYER_PATH "Data/Image/Enemy/player_div.png"

//�v���C���[���o���Ă����ō��X�s�[�h
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

//������
void Enemy::Init() {

	m_next_pos = { ((WINDOW_WIDTH / 4) - ((float)EnemySize / 2)),
			  ((WINDOW_HEIGHT / 4) - ((float)EnemySize / 2)),0 };
	//�摜�ǂݍ���
	LoadDivGraph("Data/Image/Player/player_div.png", 12, 4, 3, 64, 64, EnemyHan);
	speed = 0;
	animIndex = 1;
}
void Enemy::Step(VECTOR mouse, VECTOR player) {
	VECTOR playerPos = player; // �v���C���[�̈ʒu���擾
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
			float angle = atan2(dy_player, dx_player); // �}�E�X�|�C���^�ƃL�����N�^�[�̊p�x
			float t = (DISTANCE - distance_player) / 100; // �����ɉ�������ԌW��
			float currentSpeed = lerp(BasePlayerSpeed, MaxPlayerSpeed, t);

			speed = currentSpeed;

			m_next_pos.x += speed * cos(angle); // X�����̈ړ�

			m_next_pos.y += speed * sin(angle); // Y�����̈ړ�
		}
		else speed = 0;
	}
	else
	{
		if (distance_mouse < DISTANCE) {
			float angle = atan2(dy_mouse, dx_mouse); // �v���C���[�ƃL�����N�^�[�̊p�x
			float t = (DISTANCE - distance_mouse) / 100; // �����ɉ�������ԌW��
			float currentSpeed = lerp(BasePlayerSpeed, MaxPlayerSpeed, t);

			speed = currentSpeed;

			m_next_pos.x += speed * cos(angle); // X�����̈ړ�

			m_next_pos.y += speed * sin(angle); // Y�����̈ړ�
		}
		else speed = 0;
	}
}

void Enemy::Fin()
{
}

void Enemy::Draw() {
	//�v���C���[��`��
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

// �i��ł���������`�F�b�N
// �㉺���E�̏��ɂȂ��Ă���
void Enemy::GetMoveDirection(bool* _dirArray) {
	// �E�����̃`�F�b�N
	if (GetNextEnemyPosX() > GetEnemyPosX()) {
		_dirArray[3] = true;
	}

	// �������̃`�F�b�N
	if (GetNextEnemyPosX() < GetEnemyPosX()) {
		_dirArray[2] = true;
	}
	// �������̃`�F�b�N
	if (GetNextEnemyPosY() > GetEnemyPosY()) {
		_dirArray[1] = true;
	}

	// ������̃`�F�b�N
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