#include "../Scene//Scene.h"




class Enemy {

protected:
	//プレイヤー変数
	int EnemyHan[11] = { 0 };				//プレイヤー画像
	const int Enemy_Animation = 11;			//プレイヤーのアニメーション数
	const int EnemySize = 64;					//プレイヤー画像サイズ

	float BaseEnemySpeed = 0.5f;				//プレイヤー基本移動速度
	float MaxEnemySpeed = 5.0f;				//プレイヤー最大移動速度
//	float accelerationFactor = 0.0001f;			//加速度

	int animState = 0;						//右向きか左向きか
	int animFlag  = 0;						//アニメーションの種類
	int animIndex = 0;						//アニメーションの添え字
	int changeAnimFlame = 0;				//アニメーション切り替え時間

	int animFlameCount  = 0;				//切り替え時間カウント
	bool EnemyOnSwitch = false;			//プレイヤーとスイッチが重なっているか
	bool EnemyGoalFlag = false;			//プレイヤーがゴールにいるか

	float BasePlayerSpeed = 0.2f;				//プレイヤー基本移動速度
	float MaxPlayerSpeed = 4.0f;				//プレイヤー最大移動速度

	VECTOR m_pos;//プレイヤーの座標
	VECTOR m_next_pos;//次のフレームの座標
	float speed;

	VECTOR m_move_vec;

	bool enemyStopFlag = false;

	bool MouseOrPlayer = false;//マウスに反応時false、プレイヤーに反応時true;
public:
	Enemy();
	~Enemy();

	//初期化
	void Init();

	//通常処理
	void Step(VECTOR mouse, VECTOR player);

	//描画処理
	void Draw();

	//終了処理
	void Fin();

	//プレイヤー

	//プレイヤーのｘ座標を得る
	float GetEnemyPosX() { return m_pos.x; }

	//プレイヤーのｙ座標を得る
	float GetEnemyPosY() { return m_pos.y; }

	//プレイヤーのＸサイズを得る
	int GetEnemySizeX() { return EnemySize; }

	//プレイヤーのＹサイズを得る
	int GetEnemySizeY() { return EnemySize; }

	//プレイヤーの進んでいる方向をチェック
	void GetMoveDirection(bool* _dirArray);

	//プレイヤーのｘ座標を得る
	float GetNextEnemyPosX() { return m_next_pos.x; }

	//プレイヤーのｙ座標を得る
	float GetNextEnemyPosY() { return m_next_pos.y; }

	//プレイヤーのx座標をセット
	void SetEnemyNextPosX(float new_pos_x) { m_next_pos.x = new_pos_x; }

	//プレイヤーのｙ座標をセット
	void SetEnemyNextPosY(float new_pos_y) { m_next_pos.y = new_pos_y; }

	//線形補完関数
	float lerp(float start, float end, float t);

	void SetEnemyOnSwitchTrue();

	void SetEnemyOnSwitchFalse();

	bool GetEnemyOnSwitch() { return EnemyOnSwitch; };

	//void ApproachTarget(VECTOR targetPos, float distance);
};