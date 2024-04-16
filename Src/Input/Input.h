#pragma once

#define KEY_BUF_LEN	(256)

//入力制御初期化
void InitInput();

//入力制御ステップ
//他のStepより早く呼ぶ
void StepInput();

class InputKey {
public:
//単純に押されているか
static bool Down(int key_code);

//今押された
static bool Push(int key_code);

//押し続けられているか
static bool Keep(int key_code);

//たった今離されたか
static bool Release(int key_code);
};
