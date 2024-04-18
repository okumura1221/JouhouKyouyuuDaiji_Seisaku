#include "DxLib.h"
#include "player.h"
#include "math.h"
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
	//m_pos = { WINDOW_WIDTH / 2,WINDOW_HEIGHT / 2,0 };

	//�v���C���[�摜�ǂݍ���
	playerHan = LoadGraph(PLAYER_PATH);
	mouseHan = LoadGraph(MOUSE_PATH);
}

void Player::Step() {
	//�}�E�X�̈ʒu���擾
	GetMousePoint(&mouseX, &mouseY);
	mouse_pos = VGet((float)mouseX, (float)mouseY, 0);

	//���������Ƒ���
	m_move_vec = GetVector(mouse_pos, m_pos, GetInverseProportion(GetDistance(mouse_pos, m_pos), PLAYER_SPEED));

	//�}�E�X�|�C���^�̈ʒu����v���C���[��������
	m_pos.x += m_move_vec.x;
	m_pos.y += m_move_vec.y;
	m_pos.z += m_move_vec.z;

	//�v���C���[���͈͊O�ɍs���Ȃ�����
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
	//�v���C���[��`��
	DrawGraph(m_pos.x, m_pos.y, playerHan, true);
	DrawGraph(mouse_pos.x, mouse_pos.y, mouseHan, true);

	DrawFormatString(0, 0, GetColor(255, 0, 0), 
		"�v���C���[���W:X:%f\n�v���C���[���W:Y:%f\n�v���C���[���W:Z:%f"
		, m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 55, GetColor(255, 0, 0),
		"�}�E�X���W:X:%f\n�}�E�X���W:Y:%f\n�}�E�X���W:Z:%f"
		, mouse_pos.x, mouse_pos.y, mouse_pos.z);
}

void Player::Fin() {
	//�v���C���[�摜�̌㏈��
	DeleteGraph(playerHan);
}


// �i��ł���������`�F�b�N
// �㉺���E�̏��ɂȂ��Ă���
void Player::GetMoveDirection(bool* _dirArray) {

}
