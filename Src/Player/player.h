#include "../Scene//Scene.h"


enum Animation {
	R,//右
	L//左
};


class Player {

protected:
	//プレイヤー変数
	int playerHandle[2][18];//プレイヤー画像
	int button[4];//入力キー
	int playerSizeX;//プレイヤー画像のXサイズ
	int playerSizeY;//プレイヤー画像のYサイズ
	int hpBaseHandle;//プレイヤーHP土台画像
	int hpHandle[3];//プレイヤーHP画像
	int hp;//プレイヤーのHP
	int alphaCount;//
	int hpColorFlag;//HPの色変動変数

	float playerX;//ｘ座標
	float playerNextX;//次のフレームのｘ座標
	float playerY;//y座標
	float playerNextY;//次のフレームのy座標
	float playerSpeed;//プレイヤー移動速度
	float grav;//重力のおおきさ
	float jumpPower;//ジャンプ力
	
	int animState;//右向きか左向きか
	int animFlag;//アニメーションの種類
	int animIndex;//アニメーションの添え字
	int changeAnimFlame;//アニメーション切り替え時間
	int animFlameCount;//切り替え時間カウント

	bool jump;//ジャンプ中かどうか
	bool alphaFlag;
	bool danger;//ｈｐがピンチかどうか

	bool HitPlayerDamage;//プレイヤーが攻撃を受けた場合
	int hitArea;//どこから当たったか
	int HitJunpflmcnt;
	float HitFly_x;
	float HitFly_y;

	int runsounnd;
	int damagevoice[3];
	int Attackvoice[2];
	int jumpvoice[3];

	//弾変数
	int bulletHandle[2][10];//弾の画像
	int bulletState[10];//弾の向き
	int bulletinterval;//弾の発射間隔
	int bulletintervalCount;//弾の発射カウント
	int bulletSizeX;//弾のX大きさ
	int bulletSizeY;//弾のY大きさ
	int damage[10];//弾の攻撃力

	float bulletX[10];//弾のX座標
	float bulletY[10];//弾のY座標

	bool isUse[10];//弾使用中かどうか

public:

	//初期化
	void Init();

	//通常処理
	void Step();

	//描画処理
	void Draw();

	//プレイヤー

	//プレイヤーのｘ座標を得る
	float GetPlayerPosX() { return playerX; }

	//プレイヤーのｙ座標を得る
	float GetPlayerPosY() { return playerY; }

	//プレイヤーのｘ座標を得る
	float GetNextPlayerPosX() { return playerNextX; }

	//プレイヤーのｙ座標を得る
	float GetNextPlayerPosY() { return playerNextY; }

	//プレイヤーのx座標をセット
	void SetPlayerNextPosX(float new_pos_x) {  playerNextX= new_pos_x; }

	//プレイヤーのｙ座標をセット
	void SetPlayerNextPosY(float new_pos_y) {  playerNextY= new_pos_y; }

	//プレイヤーのＸサイズを得る
	int GetPlayerSizeX() { return playerSizeX; }

	//プレイヤーのＹサイズを得る
	int GetPlayerSizeY() { return playerSizeY; }

	//プレイヤーの体力を得る
	int GetPlayerHP() { return hp; }

	//プレイヤーがジャンプ可能にする
	void SetJump() { jump = false; }

	//プレイヤーがダメージを受け、ノックバック
	void InDamage(int damage, int bullet_state) {
		hp -= damage;
		hitArea = bullet_state;
		HitPlayerDamage = true;
	}

	//プレイヤーの進んでいる方向をチェック
	void GetMoveDirection(bool* _dirArray);


	//弾

	//弾のx座標を得る
	float GetBulletPosX(int bullet_index) { return bulletX[bullet_index]; }

	//弾のy座標を得る
	float GetBulletPosY(int bullet_index) { return bulletY[bullet_index]+10; }

	//弾のxサイズを得る
	float GetBulletSizeX() { return bulletSizeX-40; }

	//弾のyサイズを得る
	float GetBulletSizeY() { return bulletSizeY-10; }

	//弾の攻撃力を得る
	int GetBulletDamage(int bullet_index) { return damage[bullet_index]; }

	//弾の向きを得る
	int GetBulletState(int bullet_index) { return bulletState[bullet_index]; }

	//弾の使用状態を得る
	bool GetBulletIsUse(int bullet_index) { return isUse[bullet_index]; }

	//弾の使用状態をオフにする
	void SetBulletIsUse(int bullet_index) { isUse[bullet_index] = false;; }

};