#pragma once

//設定フレームレート（60FPS）
#define FRAME_RATE	(60)

//1フレームの時間
#define FRAME_TIME	(1000/FRAME_RATE)

//FPS処理
void ProcessingFPS();

//FPS計算
void CalcFPS();

//FPS表示（デバック用）
void DrawFPS();
