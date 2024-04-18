#include "DxLib.h"
#include "Scene.h"
#include "ScenePlay.h"
#include"../Map/Map.h"
#include "../Collision/Collision.h"
#include"../Player/player.h"

Player* player;
Map* CMap;
MAPCollision mapcollision;

ScenePlay::ScenePlay()
{
	// �v���C�w�i�n���h��
	PlayBGHandle = 0;
}
ScenePlay::~ScenePlay() { FinPlay(); }

//�v���C�V�[���̏�����
void ScenePlay::InitPlay()
{
	// �v���C�w�i�n���h��
	PlayBGHandle = LoadGraph(PLAY_BG_PATH);

	CMap = new Map;

	CMap->Init();

	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���ʏ폈��
void ScenePlay::StepPlay(){
	//�}�b�v�Ƃ̓����蔻��
	mapcollision.MapCollision();
	// Enter����������
	if (InputKey::Push(KEY_INPUT_RETURN))
	{
		// �v���C�V�[�����I������
		FinPlay();
	}

	backX--;
	backX2--;
	if (backX == -1280) {
		backX = 1280;
	}
	if (backX2 == -1280) {
		backX2 = 1280;
	}
}

//�v���C�V�[���`�揈��
void ScenePlay::DrawPlay()
{
	// �^�C�g���w�i�`��
	DrawGraph(backX, backY, PlayBGHandle, true);
	DrawGraph(backX2, backY, PlayBGHandle, true);

	CMap->Draw();

}

//�v���C�V�[���I������
void ScenePlay::FinPlay()
{
	// �^�C�g���w�i�n���h��
	DeleteGraph(PlayBGHandle);

	// �N���A�V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
}

// �}�b�v�̓����蔻��
void MAPCollision::MapCollision() {

	//for (int index = 0;index < 2;index++) {
	//	// Y�����̂ݓ����蔻����`�F�b�N����
	//	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	//	{
	//		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
	//		{
	//			// �u���b�N�ȊO�͏������Ȃ�
	//			if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
	//				continue;

	//			// �ǂ̕����ɐi��ł������`�F�b�N
	//			bool dirArray[4] = { false,false,false,false };
	//			player[index].GetMoveDirection(dirArray);

	//			// ��`�̓����蔻��p�̃f�[�^������
	//			// �v���C���[�̏��
	//			int Ax = player[index].GetPlayerPosX();
	//			int Ay = player[index].GetPlayerPosY();
	//			int Aw = player[index].GetPlayerSizeX();
	//			int Ah = player[index].GetPlayerSizeY();

	//			// �I�u�W�F�N�g�̏��
	//			int Bx = mapIndexX * MAP_SIZE;
	//			int By = mapIndexY * MAP_SIZE;
	//			int Bw = MAP_SIZE;
	//			int Bh = MAP_SIZE;

	//			// ��Y�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
	//			Ay = player[index].GetNextPlayerPosY();
	//			Ax = player[index].GetPlayerPosX();

	//			// �������Ă��邩�`�F�b�N
	//			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
	//				// ������̏C��
	//				if (dirArray[0]) {
	//					// �߂荞�ݗʂ��v�Z����
	//					int overlap = By + Bh - Ay;
	//					player[index].SetPlayerNextPosY(Ay + overlap);
	//				}

	//				// �������̏C��
	//				if (dirArray[1]) {
	//					// �߂荞�ݗʂ��v�Z����
	//					int overlap = Ay + Ah - By;
	//					player[index].SetPlayerNextPosY(Ay - overlap);

	//				}
	//			}
	//		}
	//	}
	//	// X�����̂ݓ����蔻����`�F�b�N����
	//	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	//	{
	//		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
	//		{
	//			// �u���b�N�ȊO�͏������Ȃ�
	//			if (CMap->m_MapData[mapIndexY][mapIndexX] == 0)
	//				continue;

	//			// �ǂ̕����ɐi��ł������`�F�b�N
	//			// ��Player�N���X�ɐi�ޕ������`�F�b�N����֐����������Ă��܂��B
	//			bool dirArray[4] = { false,false,false,false };
	//			player[index].GetMoveDirection(dirArray);

	//			// ��`�̓����蔻��p�̃f�[�^������
	//			// �v���C���[�̏��
	//			int Ax = player[index].GetPlayerPosX();
	//			int Ay = player[index].GetPlayerPosY();
	//			int Aw = player[index].GetPlayerSizeX();
	//			int Ah = player[index].GetPlayerSizeY();

	//			// �I�u�W�F�N�g�̏��
	//			int Bx = mapIndexX * MAP_SIZE;
	//			int By = mapIndexY * MAP_SIZE;
	//			int Bw = MAP_SIZE;
	//			int Bh = MAP_SIZE;

	//			// ��`�̓����蔻��p�̃f�[�^������
	//			// ��X�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
	//			Ay = player[index].GetNextPlayerPosY();
	//			Ax = player[index].GetNextPlayerPosX();

	//			// �������Ă��邩�`�F�b�N
	//			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
	//				// �������̏C��
	//				if (dirArray[2]) {
	//					// �߂荞�ݗʂ��v�Z����
	//					int overlap = Bx + Bw - Ax;
	//					player[index].SetPlayerNextPosX(Ax + overlap);
	//				}

	//				// �E�����̏C��
	//				if (dirArray[3]) {
	//					// �߂荞�ݗʂ��v�Z����
	//					int overlap = Ax + Aw - Bx;
	//					player[index].SetPlayerNextPosX(Ax - overlap);
	//				}
	//			}
	//		}
	//	}
	//}
}