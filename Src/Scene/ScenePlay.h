#pragma once

// �摜�p�X
// �v���C�w�i
#define PLAY_BG_PATH "Data/Image/BackGround/TentativePlayBG.png"

class ScenePlay {
private:
	// �v���C�w�i�n���h��
	int PlayBGHandle;

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