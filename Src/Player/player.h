#include "../Scene//Scene.h"

constexpr int PLAYER_SPEED = 1;
constexpr float DISTANCE = 200;
enum Animation {
	R,//右
	L //左
};

class Player {

protected:
	//プレイヤー変数
	int playerHan   = 0;					//プレイヤー画像
	const int playerSize = 64;					//プレイヤー画像サイズ

	float playerX = 0.0f, playerY = 0.0f;	//座標

	float BasePlayerSpeed = 0.5f;				//プレイヤー基本移動速度
	float MaxPlayerSpeed = 5.0f;				//プレイヤー最大移動速度
	float accelerationFactor = 0.0001f;			//加速度

	int animState = 0;						//右向きか左向きか
	int animFlag  = 0;						//アニメーションの種類
	int animIndex = 0;						//アニメーションの添え字
	int changeAnimFlame = 0;				//アニメーション切り替え時間
	int animFlameCount  = 0;				//切り替え時間カウント

	//マウス用変数
	int mouseHan = 0;						//マウス画像
	int mouseX   = 0, mouseY = 0;			//マウス座標
	bool mauseOnPicture = false;			//マウスポイントとマウス画像が重なっているか
	bool mauseGetFlag = false;				//マウスポイントとマウス画像が同期しているか
	VECTOR m_pos;

	float speed;
private:
	VECTOR m_move_vec;
	VECTOR mouse_pos;

public:
	Player();
	~Player();

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画処理
	void Draw();

	//終了処理
	void Fin();

	//プレイヤー

	//プレイヤーのｘ座標を得る
	float GetPlayerPosX() { return playerX; }

	//プレイヤーのｙ座標を得る
	float GetPlayerPosY() { return playerY; }

	//プレイヤーのＸサイズを得る
	int GetPlayerSizeX() { return playerSize; }

	//プレイヤーのＹサイズを得る
	int GetPlayerSizeY() { return playerSize; }

	//プレイヤーの進んでいる方向をチェック
	void GetMoveDirection(bool* _dirArray);

	//線形補完関数
	float lerp(float start, float end, float t);
};