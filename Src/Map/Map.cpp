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

void Map::Init() {
	// �摜�̓ǂݍ���
	LoadDivGraph("Data/Image/Map/map.png", 4, 2, 2, 64, 64, mapHandle);

	// �}�b�v�f�[�^��ǂݍ���
	FILE* fp;
	fopen_s(&fp, "Data/map.csv", "r"); // �t�@�C�����J��
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



void Map::Draw() {

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// �u���b�N��`��
			if (m_MapData[y][x] != 0) {
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHandle[m_MapData[y][x] - 1], true);
			}
		}
	}
}

