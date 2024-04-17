#include "DxLib.h"
#include "MyMath.h"
#include <math.h>

//長さの差を返す
float GetDefLen_f(float pos_A, float pos_B) { return fabsf(pos_A - pos_B); }

// ≒
bool NearyEqual(float num1, float num2, float error_num)
{
	if (fabsf(num1 - num2) < error_num)
		return true;

	return false;
}

int GetNumLen(int num)
{
	int len = 0;
	if (num == 0)
		return 1;
	else
		while (num != 0){
			num /= 10;
			len++;
		}

	return len;
}

//ベクトルの足し算
VECTOR AddVec(VECTOR vec1, VECTOR vec2)
{
	VECTOR vec = {
		vec1.x + vec2.x,
		vec1.y + vec2.y,
		vec1.z + vec2.z
	};

	return vec;
}

//ベクトルの引き算
VECTOR SubVec(VECTOR vec1, VECTOR vec2)
{
	VECTOR vec = {
		vec1.x - vec2.x,
		vec1.y - vec2.y,
		vec1.z - vec2.z
	};

	return vec;
}

//ベクトルの掛け算
VECTOR MulVec(VECTOR vec, float mul)
{
	VECTOR mul_vec = {
		vec.x * mul,
		vec.y * mul,
		vec.z * mul,
	};

	return mul_vec;
}

//ベクトルの割り算
VECTOR DivVec(VECTOR vec, float div)
{
	VECTOR div_vec = {
		vec.x / div,
		vec.y / div,
		vec.z / div,
	};

	return div_vec;
}

//ベクトルの長さ取得
float GetVecLen(VECTOR vec)
{
	float vec_len = (float)sqrt((double)pow(vec.x, 2) + (double)pow(vec.y, 2) + (double)pow(vec.z, 2));

	return vec_len;
}

//ベクトルの正規化
VECTOR NorVec(VECTOR vec)
{
	float vec_len = GetVecLen(vec);

	if (vec_len == 0)
		return VGet(0.0f, 0.0f, 0.0f);

	VECTOR nor_vec = {
		vec.x / vec_len,
		vec.y / vec_len,
		vec.z / vec_len
	};

	return nor_vec;
}

//現在地から目的地まで指定の速さで動くベクトル
VECTOR GetVector(VECTOR vec_here, VECTOR vec_dis, float speed)
{
	//現在地から目的地のベクトル
	VECTOR sub_vec = SubVec(vec_dis, vec_here);

	//正規化
	VECTOR nor_vec = NorVec(sub_vec);

	//取得するベクトルの大きさ
	VECTOR mul_vec = MulVec(nor_vec, speed);

	return mul_vec;
}

//内積
float VecDot(VECTOR vec1, VECTOR vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

//外積
float VecCross2D(VECTOR vec1, VECTOR vec2)
{
	return (vec1.x * vec2.y - vec1.y * vec2.x);
}

VECTOR VecCross(VECTOR vec1, VECTOR vec2)
{
	VECTOR EP = {
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	};

	return EP;
}

//ベクトルのなす角
float AngleOf2Vector(VECTOR vec1, VECTOR vec2,bool degree_switch)
{
	//ベクトルの長さ
	double len1 = GetVecLen(vec1);
	double len2 = GetVecLen(vec2);

	//cosθ
	double cos_sita = VecDot(vec1, vec2) / (len1 * len2);

	//θ
	double sita = acos(cos_sita);

	//角度
	if (degree_switch)
		sita = sita * 180.0 / DX_PI;

	return (float)sita;
}

//２点間の距離
float GetDistance(VECTOR pos1, VECTOR pos2)
{
	VECTOR distance = {
		fabsf(pos1.x - pos2.x),
		fabsf(pos1.y - pos2.y),
		fabsf(pos1.z - pos2.z),
	};

	return (float)sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
}

//反比例
float GetInverseProportion(float x,int constant)
{
	if (x != 0)
		return constant / x;
	else
		return 0;
}