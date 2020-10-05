#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：突進敵
class CObjRushEnemy : public CObj
{
public:
	CObjRushEnemy(float x, float y);
	~CObjRushEnemy() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

	float GetVx() { return m_vx; }

private:
	float m_px;			//位置
	float m_py;
	float m_vx;			//移動ベクトル
	float m_vy;
	float m_posture;	//姿勢

	int   m_ani_time;   //アニメーションフレーム動作間隔
	int   m_ani_frame;  //描画フレーム

	float m_speed_power;  //スピードパワー
	float m_ani_max_time; //アニメーション動作間隔最大値

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//追加したやつ
	float pos_init;	//沸いた時の位置記憶用
	bool m_move;	//移動の向き制御用

	bool m_rush;//突進モード用　trueで突進モード移行
	bool m_rush_stay;//突進溜め状態用

	bool stay_flag;
};