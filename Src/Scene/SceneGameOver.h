#pragma once

// �摜�p�X
// �Q�[���I�[�o�[�w�i
#define GAMEOVER_BG_PATH "Data/Image/Gameover/over1.png"
#define GAMEOVER_TEXT_PATH "Data/Image/Gameover/overtext1.png"
#define GAMEOVER_TEXT2_PATH "Data/Image/Gameover/overtext2.png"

class SceneGameOver {
private:
	// �Q�[���I�[�o�[�w�i�n���h��
	int GameOverBGHandle;
	int GameOverTextHandle;
	int GameOverText2Handle;

	int mouseX, mouseY;

public:
	int BGM = 0;

	SceneGameOver();
	~SceneGameOver();

	//�Q�[���I�[�o�[�V�[��������
	void InitGameOver();

	//�Q�[���I�[�o�[�V�[���ʏ폈��
	void StepGameOver();

	//�Q�[���I�[�o�[�V�[���`�揈��
	void DrawGameOver();

	//�Q�[���I�[�o�[�V�[���I������
	void FinGameOver();
};
