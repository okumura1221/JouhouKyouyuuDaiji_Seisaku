#include "../Scene//Scene.h"




class Enemy {

protected:
	//�v���C���[�ϐ�
	int EnemyHan[11] = { 0 };				//�v���C���[�摜
	const int Enemy_Animation = 11;			//�v���C���[�̃A�j���[�V������
	const int EnemySize = 64;					//�v���C���[�摜�T�C�Y

	float BaseEnemySpeed = 0.5f;				//�v���C���[��{�ړ����x
	float MaxEnemySpeed = 5.0f;				//�v���C���[�ő�ړ����x
//	float accelerationFactor = 0.0001f;			//�����x

	int animState = 0;						//�E��������������
	int animFlag  = 0;						//�A�j���[�V�����̎��
	int animIndex = 0;						//�A�j���[�V�����̓Y����
	int changeAnimFlame = 0;				//�A�j���[�V�����؂�ւ�����

	int animFlameCount  = 0;				//�؂�ւ����ԃJ�E���g
	bool EnemyOnSwitch = false;			//�v���C���[�ƃX�C�b�`���d�Ȃ��Ă��邩
	bool EnemyGoalFlag = false;			//�v���C���[���S�[���ɂ��邩

	float BasePlayerSpeed = 0.2f;				//�v���C���[��{�ړ����x
	float MaxPlayerSpeed = 4.0f;				//�v���C���[�ő�ړ����x

	VECTOR m_pos;//�v���C���[�̍��W
	VECTOR m_next_pos;//���̃t���[���̍��W
	float speed;

	VECTOR m_move_vec;

	bool enemyStopFlag = false;

	bool MouseOrPlayer = false;//�}�E�X�ɔ�����false�A�v���C���[�ɔ�����true;
public:
	Enemy();
	~Enemy();

	//������
	void Init();

	//�ʏ폈��
	void Step(VECTOR mouse, VECTOR player);

	//�`�揈��
	void Draw();

	//�I������
	void Fin();

	//�v���C���[

	//�v���C���[�̂����W�𓾂�
	float GetEnemyPosX() { return m_pos.x; }

	//�v���C���[�̂����W�𓾂�
	float GetEnemyPosY() { return m_pos.y; }

	//�v���C���[�̂w�T�C�Y�𓾂�
	int GetEnemySizeX() { return EnemySize; }

	//�v���C���[�̂x�T�C�Y�𓾂�
	int GetEnemySizeY() { return EnemySize; }

	//�v���C���[�̐i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);

	//�v���C���[�̂����W�𓾂�
	float GetNextEnemyPosX() { return m_next_pos.x; }

	//�v���C���[�̂����W�𓾂�
	float GetNextEnemyPosY() { return m_next_pos.y; }

	//�v���C���[��x���W���Z�b�g
	void SetEnemyNextPosX(float new_pos_x) { m_next_pos.x = new_pos_x; }

	//�v���C���[�̂����W���Z�b�g
	void SetEnemyNextPosY(float new_pos_y) { m_next_pos.y = new_pos_y; }

	//���`�⊮�֐�
	float lerp(float start, float end, float t);

	void SetEnemyOnSwitchTrue();

	void SetEnemyOnSwitchFalse();

	bool GetEnemyOnSwitch() { return EnemyOnSwitch; };

	//void ApproachTarget(VECTOR targetPos, float distance);
};