#pragma once

// �摜�p�X
// �v���C�w�i
#define PLAY_BG_PATH "Data/Image/Play/back.png"
#define BACK_MAX_NUM 2

#define TEXT_PATH	 "Data/Image/Play/text.png"

#define STAGE_MAX_NUM 4

class ScenePlay {
private:
	// �v���C�w�i�n���h��
	int PlayBGHandle[BACK_MAX_NUM];
	int backX[BACK_MAX_NUM] = { 0 };
	int	backY = 0;

	//�e�L�X�g�n���h��
	int TextHan = 0;

	int stage_num = 0;
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

	struct MAPCollision
	{
		// �}�b�v�̓����蔻��
		void MapCollision(int num);

	};
	int Getstage_num() { return stage_num; }

	void  Setstage_num(int num);
};
