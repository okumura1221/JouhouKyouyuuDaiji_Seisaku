#pragma once

// �摜�p�X
// �v���C�w�i
#define PLAY_BG_PATH "Data/Image/BackGround/back.png"
#define BACK_MAX_NUM 2
class ScenePlay {
private:
	// �v���C�w�i�n���h��
<<<<<<< HEAD
	int PlayBGHandle[BACK_MAX_NUM];
	int backX[BACK_MAX_NUM] = { 0,-1280 };
	int	backY = -1;
=======
	int PlayBGHandle;
	int backX = 0;
	int backX2 = 1280;
	int backY = 0;
>>>>>>> a53e01db79afa4726d10b5e7d9caedef1d723562

public:
	ScenePlay();
	~ScenePlay();

	// �v���C�V�[���̏�����
	void InitPlay();

	// �v���C�V�[���ʏ폈��
	void StepPlay();

	// �v���C�V�[���`�揈��
	void DrawPlay();

	// �v���C�V�[���I������
	void FinPlay();

};

struct MAPCollision
{
	// �}�b�v�̓����蔻��
	void MapCollision();

};