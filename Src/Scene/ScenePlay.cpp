#include "DxLib.h"
#include "Scene.h"
#include "ScenePlay.h"
#include"../Map/Map.h"
#include "../Collision/Collision.h"
#include"../Player/player.h"
#include"../Enemy/Enemy.h"
Player* player;
Enemy* enemy;
Map* CMap;
ScenePlay::MAPCollision mapcollision;
Collision c;

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
	enemy = new Enemy;
	CMap = new Map;

	CMap->Init(stage_num);
	player->Init();
	enemy->Init();
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���ʏ폈��
void ScenePlay::StepPlay(){
	if (stage_num>= STAGE_MAX_NUM)
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	// Enter����������
	if (InputKey::Push(KEY_INPUT_RETURN))
	{
		// �v���C�V�[�����I������
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}
	player->Step();
	enemy->Step(player->GetMouseVector(), player->GetplayerVector());
	//�}�b�v�Ƃ̓����蔻��
	mapcollision.MapCollision(0);
	mapcollision.MapCollision(1);

	if(c.Circle((int)player->GetPlayerSizeX() / 2,
		(int)enemy->GetEnemySizeX() / 2,
		(int)player->GetNextPlayerPosX(),
		(int)enemy->GetEnemyPosX(),
		(int)player->GetNextPlayerPosY(),
		(int)enemy->GetEnemyPosY()))
	{
		g_CurrentSceneID = SCENE_ID_INIT_PLAY;
	}

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

	CMap->Draw(player->GetplayerOnSwitch(), enemy->GetEnemyOnSwitch());
	if(player->GetplayerOnSwitch())
	DrawFormatString(0, 300, GetColor(255, 0, 255),"adffds");

	player->Draw();
	enemy->Draw();
	DrawGraph(10, 50, TextHan, true);
}

//�v���C�V�[���I������
void ScenePlay::FinPlay()
{
	delete player;
	player = nullptr;
	delete CMap;
	CMap = nullptr;
	delete enemy;
	enemy = nullptr;
	for (int i = 0;i < BACK_MAX_NUM;i++)
		DeleteGraph(PlayBGHandle[i]);

	// �N���A�V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
}

// �}�b�v�̓����蔻��
void ScenePlay::MAPCollision::MapCollision(int num) {

	// Y�����̂ݓ����蔻����`�F�b�N����
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			// �ǂ̕����ɐi��ł������`�F�b�N
			bool dirArray[4] = { false,false,false,false };
			if (num == 0)
			{
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
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 0 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 6 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						player->GetplayerOnSwitch() ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						enemy->GetEnemyOnSwitch())
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
						g_CurrentSceneID = SCENE_ID_INIT_PLAY;

					if (CMap->m_MapData[mapIndexY][mapIndexX] == 5)
					{
						player->SetplayerGoalFlag();
					}
					//�X�C�b�`�������ƐF�����]
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 8)
						player->SetplayerOnSwitchTrue();
					else if (CMap->m_MapData[mapIndexY][mapIndexX] != 8)
						player->SetplayerOnSwitchFalse();
					if (player->GetplayerOnSwitch())
					{
						CMap->Set_Invert_Color(mapIndexY, mapIndexX);
					}
					/*if (CMap->m_MapData[mapIndexY][mapIndexX] == 7)
						if (player->GetplayerOnSwitch())
							CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
				}
			}
			if (num == 1)
			{
				enemy->GetMoveDirection(dirArray);
				// ��`�̓����蔻��p�̃f�[�^������

					// �v���C���[�̏��
				int Ax = enemy->GetEnemyPosX();
				int Ay = enemy->GetEnemyPosY();
				int Aw = enemy->GetEnemySizeX();
				int Ah = enemy->GetEnemySizeY();

				// �I�u�W�F�N�g�̏��
				int Bx = mapIndexX * MAP_SIZE;
				int By = mapIndexY * MAP_SIZE;
				int Bw = MAP_SIZE;
				int Bh = MAP_SIZE;

				// ��Y�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
				Ay = enemy->GetNextEnemyPosY();
				Ax = enemy->GetEnemyPosX();

				// �������Ă��邩�`�F�b�N
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {


					// �u���b�N�ȊO�̏ꏊ�ɂ͐i�߂Ȃ�
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 0 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 6 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						enemy->GetEnemyOnSwitch() ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						player->GetplayerOnSwitch())
					{
						// ������̏C��
						if (dirArray[0]) {
							// �߂荞�ݗʂ��v�Z����
							int overlap = By + Bh - Ay;
							enemy->SetEnemyNextPosY(Ay + overlap);
						}

						// �������̏C��
						if (dirArray[1]) {
							// �߂荞�ݗʂ��v�Z����
							int overlap = Ay + Ah - By;
							enemy->SetEnemyNextPosY(Ay - overlap);
						}
					}
					//�X�C�b�`�������ƐF�����]
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 8)
						enemy->SetEnemyOnSwitchTrue();
					else if (CMap->m_MapData[mapIndexY][mapIndexX] != 8)
						enemy->SetEnemyOnSwitchFalse();
					if (enemy->GetEnemyOnSwitch())
					{
						CMap->Set_Invert_Color(mapIndexY, mapIndexX);
					}
					/*if (CMap->m_MapData[mapIndexY][mapIndexX] == 7)
						if (enemy->GetEnemyOnSwitch())
							CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
				}
				
				
			}
			/*if (enemy->GetEnemyOnSwitch() && CMap->m_MapData[mapIndexY][mapIndexX] == 7)
				CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
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
			if (num == 0)
			{
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
				Ay = player->GetPlayerPosY();
				Ax = player->GetNextPlayerPosX();

				// �������Ă��邩�`�F�b�N
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
					// �u���b�N�ȊO�̏ꏊ�ɂ͐i�߂Ȃ�
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 0 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 6||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						player->GetplayerOnSwitch()||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						enemy->GetEnemyOnSwitch())
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
						g_CurrentSceneID = SCENE_ID_INIT_PLAY;

					if (CMap->m_MapData[mapIndexY][mapIndexX] == 5)
					{
						player->SetplayerGoalFlag();
						player->SetplayerGoal(Bx, By);
					}
					//�X�C�b�`�������ƐF�����]
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 8)
						player->SetplayerOnSwitchTrue();
					else if (CMap->m_MapData[mapIndexY][mapIndexX] != 8)
						player->SetplayerOnSwitchFalse();
					if (player->GetplayerOnSwitch())
					{
						CMap->Set_Invert_Color(mapIndexY, mapIndexX);
					}			
					/*if (CMap->m_MapData[mapIndexY][mapIndexX] == 7)
						if (player->GetplayerOnSwitch())
							CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
				}
			}
			if (num == 1)
			{
				enemy->GetMoveDirection(dirArray);

				// ��`�̓����蔻��p�̃f�[�^������
				// �v���C���[�̏��
				int Ax = enemy->GetEnemyPosX();
				int Ay = enemy->GetEnemyPosY();
				int Aw = enemy->GetEnemySizeX();
				int Ah = enemy->GetEnemySizeY();

				// �I�u�W�F�N�g�̏��
				int Bx = mapIndexX * MAP_SIZE;
				int By = mapIndexY * MAP_SIZE;
				int Bw = MAP_SIZE;
				int Bh = MAP_SIZE;

				// ��`�̓����蔻��p�̃f�[�^������
				// ��X�����݂̂Ɉړ������Ɖ��肵�����W�œ����蔻����`�F�b�N���܂�
				Ay = enemy->GetEnemyPosY();
				Ax = enemy->GetNextEnemyPosX();

				// �������Ă��邩�`�F�b�N
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh)) {
					// �u���b�N�ȊO�̏ꏊ�ɂ͐i�߂Ȃ�
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 0 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 6 ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7&&
						enemy->GetEnemyOnSwitch() ||
						CMap->m_MapData[mapIndexY][mapIndexX] == 7 &&
						player->GetplayerOnSwitch())
					{
						// �������̏C��
						if (dirArray[2]) {
							// �߂荞�ݗʂ��v�Z����
							int overlap = Bx + Bw - Ax;
							enemy->SetEnemyNextPosX(Ax + overlap);
						}
						// �E�����̏C��
						if (dirArray[3]) {
							// �߂荞�ݗʂ��v�Z����
							int overlap = Ax + Aw - Bx;
							enemy->SetEnemyNextPosX(Ax - overlap);
						}
					}
					//�X�C�b�`�������ƐF�����]
					if (CMap->m_MapData[mapIndexY][mapIndexX] == 8)
						enemy->SetEnemyOnSwitchTrue();
					else if(CMap->m_MapData[mapIndexY][mapIndexX] != 8)
						enemy->SetEnemyOnSwitchFalse();
					if (enemy->GetEnemyOnSwitch())
					{
						CMap->Set_Invert_Color(mapIndexY, mapIndexX);
					}			
					/*if (CMap->m_MapData[mapIndexY][mapIndexX] == 7)
						if (enemy->GetEnemyOnSwitch())
							CMap->Set_Invert_Color(mapIndexY, mapIndexX);*/
				
				}
				
			}
			//if (enemy->GetEnemyOnSwitch() && CMap->m_MapData[mapIndexY][mapIndexX] == 7)
				//CMap->Set_Invert_Color(mapIndexY, mapIndexX);
		}
	}
}
void  ScenePlay::Setstage_num(int num)
{
	stage_num = num;
}
