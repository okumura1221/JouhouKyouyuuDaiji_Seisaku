#include "DxLib.h"
#include "Enemy.h"
#include "../Player/player.h"
#include <math.h>
#include <cmath>
#include "../MyMath/MyMath.h"

//�X�N���[���T�C�Y�ݒ�
#define WINDOW_WIDTH			(1280)
#define WINDOW_HEIGHT			(720)						

//�v���C���[��������͈͐ݒ�
#define PLAYER_MOVE_SPACE_X			(1180)		
#define PLAYER_MOVE_SPACE_Y			(620)						

//�摜�p�X
//#define PLAYER_PATH "Data/Image/Player/player.png"
#define PLAYER_PATH "Data/Image/Enemy/player_div.png"

//�v���C���[���o���Ă����ō��X�s�[�h
#define PLAYER_SPEED_MAX 6

Enemy::Enemy()
{
	m_move_vec = { 0 };
	m_next_pos = { 0 };
}

Enemy::~Enemy()
{
}

//������
void Enemy::Init() {

	SetMouseDispFlag(true);
	m_next_pos = { ((WINDOW_WIDTH / 2) - ((float)EnemySize / 2)),
			  ((WINDOW_HEIGHT / 2) - ((float)EnemySize / 2)),0 };
	//�v���C���[�摜�ǂݍ���
	//playerHan = LoadGraph(PLAYER_PATH);
	LoadDivGraph("Data/Image/Player/player_div.png", 12, 4, 3, 64, 64, EnemyHan);
	speed = 0;
	animIndex = 1;
}
void Enemy::Step(VECTOR mouse, VECTOR player) {
	VECTOR playerPos = player=a; // �v���C���[�̈ʒu���擾
	VECTOR mousePos = mouse;

	

	// �v���C���[�Ƃ̋������v�Z
	int dxPlayer = playerPos.x - (m_pos.x + ((float)EnemySize / 2));
	int dyPlayer = playerPos.y - (m_pos.y + ((float)EnemySize / 2));
	float distancePlayer = sqrt(dxPlayer * dxPlayer + dyPlayer * dyPlayer);

	// �}�E�X�|�C���^�Ƃ̋������v�Z
	int dxMouse = mousePos.x - (m_pos.x + ((float)EnemySize / 2));
	int dyMouse = mousePos.y - (m_pos.y + ((float)EnemySize / 2));
	float distanceMouse = sqrt(dxMouse * dxMouse + dyMouse * dyMouse);

	// �v���C���[�ɗD��I�ɋ߂Â�
	bool prioritizePlayer = distancePlayer < distanceMouse;

	// ���W������
	m_pos = m_next_pos;

	// �G���v���C���[�܂��̓}�E�X�|�C���^�ɋ߂Â�
	if (!enemyStopFlag) {
		if (prioritizePlayer) {
			ApproachTarget(playerPos, distancePlayer);
		}
		else {
			ApproachTarget(mousePos, distanceMouse);
		}
	}

	// �}�E�X�|�C���^�ɔ������Ă��鎞�ɍ��N���b�N���ꂽ���~
	if (!prioritizePlayer && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		enemyStopFlag = true;
	}
}

void Enemy::ApproachTarget(VECTOR targetPos, float distance) {
	if (distance < DISTANCE) {
		float angle = atan2(targetPos.y - m_pos.y, targetPos.x - m_pos.x); // �^�[�Q�b�g�Ƃ̊p�x
		float t = (DISTANCE - distance) / 100; // �����ɉ�������ԌW��
		float currentSpeed = lerp(BaseEnemySpeed, MaxEnemySpeed, t);

		m_next_pos.x += currentSpeed * cos(angle); // X�����̈ړ�
		m_next_pos.y += currentSpeed * sin(angle); // Y�����̈ړ�
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

	DrawFormatString(0, 200, GetColor(255, 0, 255),
		"%f", a.x);
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

void Enemy::SetEnemyGoalFlag()
{
	EnemyGoalFlag = true;
}

void Enemy::SetEnemyGoal(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}