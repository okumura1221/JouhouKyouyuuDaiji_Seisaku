#include "../Scene//Scene.h"

constexpr int PLAYER_SPEED = 1;
constexpr float DISTANCE = 200;

extern bool stage_change_flag;

enum Animation {
	R,//�E
	L //��
};

class Player {

protected:
	//�v���C���[�ϐ�
	int playerHan[11] = { 0 };				//�v���C���[�摜
	const int Player_Animation = 11;			//�v���C���[�̃A�j���[�V������
	const int playerSize = 64;					//�v���C���[�摜�T�C�Y

	float BasePlayerSpeed = 0.5f;				//�v���C���[��{�ړ����x
	float MaxPlayerSpeed = 5.0f;				//�v���C���[�ő�ړ����x
	//float accelerationFactor = 0.0001f;			//�����x

	int animState = 0;						//�E��������������
	int animFlag  = 0;						//�A�j���[�V�����̎��
	int animIndex = 0;						//�A�j���[�V�����̓Y����
	int changeAnimFlame = 0;				//�A�j���[�V�����؂�ւ�����
	int animFlameCount  = 0;				//�؂�ւ����ԃJ�E���g
	bool playerOnSwitch = false;			//�v���C���[�ƃX�C�b�`���d�Ȃ��Ă��邩
	bool playerGoalFlag = false;			//�v���C���[���S�[���ɂ��邩

	//�}�E�X�p�ϐ�
	int mouseHan = 0;						//�}�E�X�摜
	int mouseX   = 0, mouseY = 0;			//�}�E�X���W
	bool mauseOnPicture = false;			//�}�E�X�|�C���g�ƃ}�E�X�摜���d�Ȃ��Ă��邩
	bool mauseGetFlag = false;				//�}�E�X�|�C���g�ƃ}�E�X�摜���������Ă��邩
	VECTOR m_pos;//�v���C���[�̍��W
	VECTOR m_next_pos;//���̃t���[���̍��W
	float speed;

	VECTOR m_move_vec;
	VECTOR mouse_pos = { 0 };

public:
	Player();
	~Player();

	//������
	void Init(int num);

	//�ʏ폈��
	void Step();

	//�`�揈��
	void Draw();

	//�I������
	void Fin();

	//�v���C���[

	//�v���C���[�̂����W�𓾂�
	float GetPlayerPosX() { return m_pos.x; }

	//�v���C���[�̂����W�𓾂�
	float GetPlayerPosY() { return m_pos.y; }

	//�v���C���[�̂w�T�C�Y�𓾂�
	int GetPlayerSizeX() { return playerSize; }

	//�v���C���[�̂x�T�C�Y�𓾂�
	int GetPlayerSizeY() { return playerSize; }

	//�v���C���[�̐i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);


	//�v���C���[�̂����W�𓾂�
	float GetNextPlayerPosX() { return m_next_pos.x; }

	//�v���C���[�̂����W�𓾂�
	float GetNextPlayerPosY() { return m_next_pos.y; }

	//�v���C���[��x���W���Z�b�g
	void SetPlayerNextPosX(float new_pos_x) { m_next_pos.x = new_pos_x; }

	//�v���C���[�̂����W���Z�b�g
	void SetPlayerNextPosY(float new_pos_y) { m_next_pos.y = new_pos_y; }


	//���`�⊮�֐�
	float lerp(float start, float end, float t);

	void SetplayerOnSwitchTrue();

	void SetplayerOnSwitchFalse();

	bool GetplayerOnSwitch() { return playerOnSwitch; };

	void SetplayerGoalFlag();

	void SetplayerGoal(float x, float y);

	VECTOR  GetplayerVector() const{ return m_pos; };

	VECTOR  GetMouseVector() const { return mouse_pos; };
};