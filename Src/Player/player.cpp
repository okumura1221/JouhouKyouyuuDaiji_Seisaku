#include "DxLib.h"
#include "player.h"
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
#define PLAYER_PATH "Data/Image/Player/player.png"
#define MOUSE_PATH  "Data/Image/Player/mouse.png"

//�v���C���[���o���Ă����ō��X�s�[�h
#define PLAYER_SPEED_MAX 5

Player::Player()
{
	m_move_vec = { 0 };
	mouse_pos = { 0 };
}

Player::~Player()
{
	Fin();
}

//������
void Player::Init() {
	m_pos = { ((WINDOW_WIDTH / 2) - ((float)playerSize / 2)),
			  ((WINDOW_HEIGHT / 2) - ((float)playerSize / 2)) };

	//�v���C���[�摜�ǂݍ���
	playerHan = LoadGraph(PLAYER_PATH);
	mouseHan = LoadGraph(MOUSE_PATH);

	speed = 0;
}

void Player::Step() {

	//�}�E�X�̈ʒu���擾
	GetMousePoint(&mouseX, &mouseY);
	mouse_pos = VGet((float)mouseX, (float)mouseY, 0);

	// �}�E�X�|�C���^�ƃL�����N�^�[�̋������v�Z
	int dx = mouse_pos.x - (m_pos.x + ((float)playerSize / 2));
	int dy = mouse_pos.y - (m_pos.y + ((float)playerSize / 2));
	float distance = sqrt(dx * dx + dy * dy);

	// ��苗�����Ƀ}�E�X�|�C���^������ꍇ�A�L�����N�^�[��������
	if (distance < DISTANCE) {
		float angle = atan2(dy, dx); // �}�E�X�|�C���^�ƃL�����N�^�[�̊p�x
		float t = (DISTANCE - distance) / 100; // �����ɉ�������ԌW��
		float currentSpeed = lerp(BasePlayerSpeed, MaxPlayerSpeed, t);

		speed = currentSpeed;

		m_pos.x -= currentSpeed * cos(angle); // X�����̈ړ�

		m_pos.y -= currentSpeed * sin(angle); // Y�����̈ړ�
	}

	//�X�s�[�h���o����������Q�[���I�[�o�[
	if (speed >= PLAYER_SPEED_MAX) {
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}

	////�v���C���[���͈͊O�ɍs���Ȃ�����
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
	//�v���C���[��`��

	DrawGraph(m_pos.x, m_pos.y, playerHan, true);
	DrawRotaGraph(mouse_pos.x, mouse_pos.y, 1.0, 0.0, mouseHan, true);

	DrawFormatString(0, 0, GetColor(255, 0, 0), 
		"�v���C���[���W:X:%f\n�v���C���[���W:Y:%f\n�v���C���[���W:Z:%f"
		, m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 55, GetColor(0, 0, 255),
		"�}�E�X���W:X:%f\n�}�E�X���W:Y:%f\n�}�E�X���W:Z:%f"
		, mouse_pos.x, mouse_pos.y, mouse_pos.z);
	DrawFormatString(0, 110, GetColor(255, 0, 255),
		"�����x:%f", speed);
}

void Player::Fin() {
	//�v���C���[�摜�̌㏈��
	DeleteGraph(playerHan);
}


// �i��ł���������`�F�b�N
// �㉺���E�̏��ɂȂ��Ă���
void Player::GetMoveDirection(bool* _dirArray) {

}

float Player::lerp(float start, float end, float t) {
	return start + t * (end - start);
}