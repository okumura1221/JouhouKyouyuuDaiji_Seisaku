#include "DxLib.h"
#include "player.h"
#include <math.h>
#include <cmath>
#include"../Scene/ScenePlay.h"
//�X�N���[���T�C�Y�ݒ�
#define WINDOW_WIDTH			(1280)
#define WINDOW_HEIGHT			(720)						

//�v���C���[��������͈͐ݒ�
#define PLAYER_MOVE_SPACE_X			(1180)		
#define PLAYER_MOVE_SPACE_Y			(620)						

//�摜�p�X
//#define PLAYER_PATH "Data/Image/Player/player.png"
#define PLAYER_PATH "Data/Image/Player/player_div.png"

#define MOUSE_PATH  "Data/Image/Player/mouse.png"

//�v���C���[���o���Ă����ō��X�s�[�h
#define PLAYER_SPEED_MAX 6

Player::Player()
{
	m_move_vec = { 0 };
	mouse_pos = { 0 };
	m_next_pos = { 0 };
}

Player::~Player()
{
}

//������
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
	//�v���C���[�摜�ǂݍ���
	//playerHan = LoadGraph(PLAYER_PATH);
	LoadDivGraph("Data/Image/Player/player_div.png", 12, 4, 3, 64, 64, playerHan);
	mouseHan = LoadGraph(MOUSE_PATH);
	mouse_pos = VGet((WINDOW_WIDTH / 2)+(WINDOW_WIDTH / 4), (WINDOW_HEIGHT / 2), 0);
	speed = 0;
	mauseGetFlag = false;
	mauseOnPicture = false;
	animIndex = 1;
}

void Player::Step() {

	GetMousePoint(&mouseX, &mouseY);
	
	if ((mouse_pos.x - (playerSize / 2)) <= mouseX &&
		mouseX <= (mouse_pos.x + (playerSize / 2)) &&
		(mouse_pos.y - (playerSize / 2)) <= mouseY &&
		mouseY <= (mouse_pos.y + (playerSize / 2)))
	{
		mauseOnPicture = true;
		//�}�E�X�摜���N���b�N����
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//�}�E�X�̕\����Ԃ�ύX
			SetMouseDispFlag(false);
			mauseGetFlag = true;
		}
	}
	else mauseOnPicture = false;
	if(mauseGetFlag)mouse_pos = VGet((float)mouseX, (float)mouseY, 0);
		
	//�}�E�X�̈ʒu���擾
	
	// �}�E�X�|�C���^�ƃL�����N�^�[�̋������v�Z
	int dx = mouse_pos.x - (m_pos.x + ((float)playerSize / 2));
	int dy = mouse_pos.y - (m_pos.y + ((float)playerSize / 2));
	float distance = sqrt(dx * dx + dy * dy);

	//���W������
	m_pos = m_next_pos;


	// ��苗�����Ƀ}�E�X�|�C���^������ꍇ�A�L�����N�^�[��������
	if (!playerGoalFlag) {
		if (distance < DISTANCE) {
			float angle = atan2(dy, dx); // �}�E�X�|�C���^�ƃL�����N�^�[�̊p�x
			float t = (DISTANCE - distance) / 100; // �����ɉ�������ԌW��
			float currentSpeed = lerp(BasePlayerSpeed, MaxPlayerSpeed, t);

			speed = currentSpeed;

			m_next_pos.x -= speed * cos(angle); // X�����̈ړ�

			m_next_pos.y -= speed * sin(angle); // Y�����̈ړ�
		}
		else speed = 0;
		//�X�s�[�h���o����������Q�[���I�[�o�[
		if (speed >= PLAYER_SPEED_MAX) {
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
	//�v���C���[��`��
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
	DrawFormatString(0, 0, GetColor(255, 0, 0), 
		"�v���C���[���W:X:%f\n�v���C���[���W:Y:%f\n�v���C���[���W:Z:%f"
		, m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 55, GetColor(0, 0, 255),
		"�}�E�X���W:X:%f\n�}�E�X���W:Y:%f\n�}�E�X���W:Z:%f"
		, mouse_pos.x, mouse_pos.y, mouse_pos.z);
	DrawFormatString(0, 110, GetColor(255, 0, 255),
		"�����x:%f", speed);

	DrawFormatString(0, 250, GetColor(255, 0, 255),
		"%f", GetPlayerPosX());
}

// �i��ł���������`�F�b�N
// �㉺���E�̏��ɂȂ��Ă���
void Player::GetMoveDirection(bool* _dirArray) {
	// �E�����̃`�F�b�N
	if (GetNextPlayerPosX() > GetPlayerPosX()) {
		_dirArray[3] = true;
	}

	// �������̃`�F�b�N
	if (GetNextPlayerPosX() < GetPlayerPosX()) {
		_dirArray[2] = true;
	}
	// �������̃`�F�b�N
	if (GetNextPlayerPosY() > GetPlayerPosY()) {
		_dirArray[1] = true;
	}

	// ������̃`�F�b�N
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