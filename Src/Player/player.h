#include "../Scene//Scene.h"

constexpr int PLAYER_SPEED = 300;

enum Animation {
	R,//�E
	L //��
};

class Player {

protected:
	//�v���C���[�ϐ�
	int playerHan   = 0;					//�v���C���[�摜
	int playerSizeX = 0, playerSizeY = 0;	//�v���C���[�摜�T�C�Y

	float playerX = 0.0f, playerY = 0.0f;	//���W
	float playerSpeed = 0.0f;				//�v���C���[�ړ����x

	int animState = 0;						//�E��������������
	int animFlag  = 0;						//�A�j���[�V�����̎��
	int animIndex = 0;						//�A�j���[�V�����̓Y����
	int changeAnimFlame = 0;				//�A�j���[�V�����؂�ւ�����
	int animFlameCount  = 0;				//�؂�ւ����ԃJ�E���g

	//�}�E�X�p�ϐ�
	int mouseHan = 0;						//�}�E�X�摜
	int mouseX   = 0, mouseY = 0;			//�}�E�X���W
	VECTOR m_pos;

private:
	VECTOR m_move_vec;
	VECTOR mouse_pos;

public:
	Player();
	~Player();

	//������
	void Init();

	//�ʏ폈��
	void Step();

	//�`�揈��
	void Draw();

	//�I������
	void Fin();

	//�v���C���[

	//�v���C���[�̂����W�𓾂�
	float GetPlayerPosX() { return playerX; }

	//�v���C���[�̂����W�𓾂�
	float GetPlayerPosY() { return playerY; }

	//�v���C���[�̂w�T�C�Y�𓾂�
	int GetPlayerSizeX() { return playerSizeX; }

	//�v���C���[�̂x�T�C�Y�𓾂�
	int GetPlayerSizeY() { return playerSizeY; }

	//�v���C���[�̐i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);
};