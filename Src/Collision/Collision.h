#pragma once

class Collision {
public:
	// 矩形Aと矩形Bの当たり判定のプロトタイプ宣言
	static bool Rect(int Ax, int Ay, int Aw, int Ah,int Bx, int By, int Bw, int Bh);

	// 円Aと円Bの当たり判定のプロトタイプ宣言
	static bool Circle(int Ra, int Rb, int Xa, int Xb, int Ya, int Yb);

	// 矩形Aと点Bの当たり判定のプロトタイプ宣言
	static bool Rect_Dot(int Ax, int Ay, int Aw, int Ah, int Bx, int By);
};
