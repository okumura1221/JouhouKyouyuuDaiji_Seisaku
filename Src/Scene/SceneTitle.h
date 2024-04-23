#pragma once

// �摜�p�X
// �^�C�g���w�i
#define TITLE_BG_PATH "Data/Image/Title/TitleImage.png"

#define TITLE_BUTTTON_PATH1 "Data/Image/Title/SelectButton.png"
#define TITLE_BUTTTON_PATH2 "Data/Image/Title/SelectButton2.png"

//�^�C�g��BGM
#define TITLE_BGM_PATH "Data/Sound/title.wav"
#define BUTTON_SE_PATH "Data/Sound/click.mp3"

class SceneTitle {
private:
	// �^�C�g���w�i�n���h��
	int TitleBGHandle;
	int TitleButtonHandle1, TitleButtonHandle2;

	int mouseX, mouseY;

	int TitleSoundPath;
	int ButtonSEPath;

	int NextSceneCnt;

	bool SceneFlag;

	
public:

	bool clickflag;

	SceneTitle();
	~SceneTitle();
	
	// �^�C�g���̏�����
	void InitTitle();

	// �^�C�g���ʏ폈��
	void StepTitle();

	// �^�C�g���`�揈��
	void DrawTitle();

	// �^�C�g���I������
	void FinTitle();

	void Setclickflag();

	bool Getclickflag(){ return clickflag; };
};
