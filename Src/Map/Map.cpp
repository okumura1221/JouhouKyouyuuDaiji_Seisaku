#include "map.h"
#include "DxLib.h"
#include "../Player/player.h"

//�}�b�v����

// ���������X�g��const�̃����o�ϐ���������
//�X�e�[�W�\��
Map::Map() :m_MapData{}
{
	mapHandle[0] = -1;
	mapHandle[1] = -1;
	mapHandle[2] = -1;
	mapHandle[3] = -1;
}

Map::~Map() {}

void Map::Init(int num) {
	// �摜�̓ǂݍ���
	LoadDivGraph("Data/Image/Map/map_div.png", 8, 2, 4, 64, 64, mapHandle);

	// �}�b�v�f�[�^��ǂݍ���
	FILE* fp=0;
	if (num == 0)
		fopen_s(&fp, "Data/MapData/Map_1/map1.csv", "r"); // �t�@�C�����J��
	if (num == 1)
		fopen_s(&fp, "Data/MapData/Map_2/map.csv", "r"); // �t�@�C�����J��
	if (num == 2)
		fopen_s(&fp, "Data/MapData/Map_3/map.csv", "r"); // �t�@�C�����J��
	if (num == 3)
		fopen_s(&fp, "Data/MapData/Map_4/map.csv", "r"); // �t�@�C�����J��
	if (fp == NULL) // �t�@�C�����J���Ȃ�������
	{
		DrawString(0, 0, "dgsgh", GetColor(255, 255, 255));
		return; // �I��
	}
	for (int i = 0; i < MAP_DATA_Y; i++) // �}�b�v�̍������J��Ԃ�
	{
		for (int j = 0; j < MAP_DATA_X; j++) // �}�b�v�̕����J��Ԃ�
		{
			fscanf_s(fp, "%d,", &m_MapData[i][j]); // �}�b�v�f�[�^��ǂݍ���
		}
	}
	fclose(fp); // �t�@�C�������
}



void Map::Draw(bool playeron, bool enemyeron) {

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// �u���b�N��`��
			if (m_MapData[y][x] != 0) {
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHandle[m_MapData[y][x] - 1], true);
			}
			if (m_MapData[y][x] == 7|| m_MapData[y][x] == 2) {
				if (Invert_Color_flag_full)
					SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHandle[m_MapData[y][x] - 1], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			if (m_MapData[y][x] == 8) {
				if(Invert_Color_flag[y][x])
				SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHandle[m_MapData[y][x] - 1], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

void Map::Set_Invert_Color(int y,int x) {
	if (!Invert_Color_flag[y][x])
		Invert_Color_flag[y][x] = true;
	else
		Invert_Color_flag[y][x] = false;
}

void Map::Set_Invert_Color() {
	if (!Invert_Color_flag_full)
		Invert_Color_flag_full = true;
	else
		Invert_Color_flag_full = false;
}