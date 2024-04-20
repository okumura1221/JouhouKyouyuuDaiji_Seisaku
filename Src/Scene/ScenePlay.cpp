#include "DxLib.h"
#include "Scene.h"
#include "ScenePlay.h"
#include"../Map/Map.h"
#include "../Collision/Collision.h"
#include"../Player/player.h"

Player* player;
Map* CMap;
ScenePlay::MAPCollision mapcollision;

ScenePlay::ScenePlay()
{
	// �v���C�w�i�n���h��
	for (int i = 0;i < BACK_MAX_NUM;i++)
	PlayBGHandle[i] = 0;
}

ScenePlay::~ScenePlay() { FinPlay(); }

//�v���C�V�[���̏�����
void ScenePlay::InitPlay()
{
	
	// �v���C�w�i�n���h��
	for (int i = 0;i < BACK_MAX_NUM;i++)
	{
		PlayBGHandle[i] = LoadGraph(PLAY_BG_PATH);
	}

	TextHan = LoadGraph(TEXT_PATH);

	backX[0] = 0;
	backX[1] = 1280;

	player = new Player;
	CMap = new Map;

	CMap->Init();
	player->Init();
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���ʏ폈��
void ScenePlay::StepPlay(){
	
	// Enter����������
	if (InputKey::Push(KEY_INPUT_RETURN))
	{
		// �v���C�V�[�����I������
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}

	player->Step();
	//�}�b�v�Ƃ̓����蔻��
	mapcollision.MapCollision();

	//�w�i�X�N���[������
	for (int i = 0;i < BACK_MAX_NUM;i++)
	{
		backX[i]--;
		if (backX[i] == -1280)backX[i] = 1280;
	}
}

//�v���C�V�[���`�揈��
void ScenePlay::DrawPlay()
{
	// �^�C�g���w�i�`��
	for (int i = 0; i < BACK_MAX_NUM; i++) {
		DrawGraph(backX[i], backY, PlayBGHandle[i], true);
	}

	CMap->Draw();
	player->Draw();
	DrawGraph(10, 50, TextHan, true);
}

//�v���C�V�[���I������
void ScenePlay::FinPlay()
{
	delete player;
	player = nullptr;
	delete CMap;
	CMap = nullptr;

	for (int i = 0;i < BACK_MAX_NUM;i++)
		DeleteGraph(PlayBGHandle[i]);

	// �N���A�V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
}

// �}�b�v�̓����蔻��
void ScenePlay::MAPCollision::MapCollision() {

	// Y�����̂ݓ����蔻����`�F�b�N����
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// �ǂ̕����ɐi��ł������`�F�b�N
			bool dirArray[4] = { false,false,false,false };
			player->GetMoveDirection(dirArray);
			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = player->GetPlayerPosX();
			int Ay = player->GetPlayerPosY();
			int Aw = player->GetPlayerSizeX();
			int Ah = player->GetPlayerSizeY();

			// �I�u�W�F�N�g�̏��
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// ��Y�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
			Ay = player->GetNextPlayerPosY();
			Ax = player->GetPlayerPosX();

			// �������Ă��邩�`�F�b�N
			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {


				// �u���b�N�ȊO�̏ꏊ�ɂ͐i�߂Ȃ�
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
				{
					// ������̏C��
					if (dirArray[0]) {
						// �߂荞�ݗʂ��v�Z����
						int overlap = By + Bh - Ay;
						player->SetPlayerNextPosY(Ay + overlap);
					}

					// �������̏C��
					if (dirArray[1]) {
						// �߂荞�ݗʂ��v�Z����
						int overlap = Ay + Ah - By;
						player->SetPlayerNextPosY(Ay - overlap);

					}
				}
				//���ɐG���Ɖ�ʑJ��
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 4)
					g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
			}

		}
	}
	// X�����̂ݓ����蔻����`�F�b�N����
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{

			// �ǂ̕����ɐi��ł������`�F�b�N
			// ��Player�N���X�ɐi�ޕ������`�F�b�N����֐����������Ă��܂��B
			bool dirArray[4] = { false,false,false,false };
			player->GetMoveDirection(dirArray);

			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = player->GetPlayerPosX();
			int Ay = player->GetPlayerPosY();
			int Aw = player->GetPlayerSizeX();
			int Ah = player->GetPlayerSizeY();

			// �I�u�W�F�N�g�̏��
			int Bx = mapIndexX * MAP_SIZE;
			int By = mapIndexY * MAP_SIZE;
			int Bw = MAP_SIZE;
			int Bh = MAP_SIZE;

			// ��`�̓����蔻��p�̃f�[�^������
			// ��X�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
			Ay = player->GetNextPlayerPosY();
			Ax = player->GetNextPlayerPosX();

			// �������Ă��邩�`�F�b�N
			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
				// �u���b�N�ȊO�̏ꏊ�ɂ͐i�߂Ȃ�
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
				{
					// �������̏C��
					if (dirArray[2]) {
						// �߂荞�ݗʂ��v�Z����
						int overlap = Bx + Bw - Ax;
						player->SetPlayerNextPosX(Ax + overlap);
					}

					// �E�����̏C��
					if (dirArray[3]) {
						// �߂荞�ݗʂ��v�Z����
						int overlap = Ax + Aw - Bx;
						player->SetPlayerNextPosX(Ax - overlap);
					}
				}
				//���ɐG���Ɖ�ʑJ��
				if (CMap->m_MapData[mapIndexY][mapIndexX] == 4)
					g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
			}

		}
	}
}