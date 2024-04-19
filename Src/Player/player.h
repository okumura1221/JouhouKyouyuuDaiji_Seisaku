#include "../Scene//Scene.h"

constexpr int PLAYER_SPEED = 1;
constexpr float DISTANCE = 200;
enum Animation {
	R,//�E
	L //��
};

class Player {

protected:
	//�v���C���[�ϐ�
	int playerHan   = 0;					//�v���C���[�摜
	const int playerSize = 64;					//�v���C���[�摜�T�C�Y

	float playerX = 0.0f, playerY = 0.0f;	//���W

	float BasePlayerSpeed = 0.5f;				//�v���C���[��{�ړ����x
	float MaxPlayerSpeed = 5.0f;				//�v���C���[�ő�ړ����x
	float accelerationFactor = 0.0001f;			//�����x

	int animState = 0;						//�E��������������
	int animFlag  = 0;						//�A�j���[�V�����̎��
	int animIndex = 0;						//�A�j���[�V�����̓Y����
	int changeAnimFlame = 0;				//�A�j���[�V�����؂�ւ�����
	int animFlameCount  = 0;				//�؂�ւ����ԃJ�E���g

	//�}�E�X�p�ϐ�
	int mouseHan = 0;						//�}�E�X�摜
	int mouseX   = 0, mouseY = 0;			//�}�E�X���W
	bool mauseOnPicture = false;			//�}�E�X�|�C���g�ƃ}�E�X�摜���d�Ȃ��Ă��邩
	bool mauseGetFlag = false;				//�}�E�X�|�C���g�ƃ}�E�X�摜���������Ă��邩
	VECTOR m_pos;

	float speed;
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
	int GetPlayerSizeX() { return playerSize; }

	//�v���C���[�̂x�T�C�Y�𓾂�
	int GetPlayerSizeY() { return playerSize; }

	//�v���C���[�̐i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);

	//���`�⊮�֐�
	float lerp(float start, float end, float t);
};