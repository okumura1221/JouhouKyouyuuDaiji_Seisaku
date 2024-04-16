#include "Collision.h"

// 矩形Aと矩形Bの当たり判定の定義
bool Collision::Rect(int Ax, int Ay, int Aw, int Ah,
				int Bx, int By, int Bw, int Bh)
{
	if (Bx < Ax + Aw &&
		Bx + Bw > Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		return true;
	}
	return false;
}

// 円Aと円Bの当たり判定の定義
bool Collision::Circle(int Ra, int Rb, int Xa, int Xb, int Ya, int Yb)
{
	if (((Ra + Rb) * (Ra + Rb)) > ((Xa - Xb) * (Xa - Xb)) + ((Ya - Yb) * (Ya - Yb)))
	{
		return true;
	}
	return false;
}

// 矩形Aと点Bの当たり判定のプロトタイプ宣言
bool Collision::Rect_Dot(int Ax, int Ay, int Aw, int Ah, int Bx, int By)
{
	if (Ax < Bx && 
		Bx < Ax + Aw && 
		Ay < By && 
		By < Ay + Ah)
	{
		return true;
	}
	return false;
}
