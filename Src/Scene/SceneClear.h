#pragma once

// �摜�p�X
// �N���A�w�i
#define CLEAR_BG_PATH "Data/Image/Clear/ClearImage.png"

#define CLEAR_BUTTTON_PATH1 "Data/Image/Clear/ClearButton1.png"
#define CLEAR_BUTTTON_PATH2 "Data/Image/Clear/ClearButton2.png"

#define CLEAR_EFFECT_PATH "Data/Image/Clear/ClearEffect.png"

//�^�C�g��BGM
#define CLEAR_BGM_PATH "Data/Sound/ed.wav"
#define CLEAR_BUTTON_SE_PATH "Data/Sound/click.mp3"

class SceneClear {
private:
	// �N���A�w�i�n���h��
	int ClearBGHandle;

	int ClearButtonHandle1, ClearButtonHandle2;

	int ClearEffectHandle[2];
	int ClearEffectposX, ClearEffectposY[2];
	

	int mouseX, mouseY;

	int ClearSoundPath;
	int ButtonSEPath;

public:
	bool clickflag;
	SceneClear();
	~SceneClear();

	//�N���A�V�[��������
	void InitClear();

	//�N���A�V�[���ʏ폈��
	void StepClear();

	//�N���A�V�[���`�揈��
	void DrawClear();

	//�N���A�V�[���I������
	void FinClear();
};
