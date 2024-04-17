#pragma once

#include "DxLib.h"

//長さの差を返す
float GetDefLen_f(float pos_A, float pos_B);
//≒
bool NearyEqual(float num1, float num2, float error_num = 1.0f);

int GetNumLen(int num);

//ベクトルの足し算
VECTOR AddVec(VECTOR vec1, VECTOR vec2);
//ベクトルの引き算
VECTOR SubVec(VECTOR vec1, VECTOR vec2);
//ベクトルの掛け算
VECTOR MulVec(VECTOR vec, float mul);
//ベクトルの割り算
VECTOR DivVec(VECTOR vec, float div);

//ベクトルの長さ取得
float GetVecLen(VECTOR vec);

//ベクトルの正規化
VECTOR NorVec(VECTOR vec);

//現在地から目的地まで指定の速さで動くベクトル
VECTOR GetVector(VECTOR vec_here, VECTOR vec_dis, float speed = 1.0f);


//内積
float VecDot(VECTOR vec1, VECTOR vec2);

//外積
float VecCross2D(VECTOR vec1, VECTOR vec2);

VECTOR VecCross(VECTOR vec1, VECTOR vec2);

//ベクトルのなす角
float AngleOf2Vector(VECTOR vec1, VECTOR vec2, bool degree_switch = false);

//２点間の距離
float GetDistance(VECTOR pos1, VECTOR pos2);

//反比例
float GetInverseProportion(float x, int constant);