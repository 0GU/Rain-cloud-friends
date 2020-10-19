#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjHero : public CObj
{
public:
	CObjHero(int stage) ;
	~CObjHero() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }
	int GetBT() { return m_block_type; }
	float GetHP() { return m_hp; }

	void SetX(float x) { m_px = x; }
	void SetY(float y) { m_py = y; }
	void SetVY(float vy) { m_vy = vy; }
	void SetVX(float vx) { m_vx = vx; }
	void SetBT(int t) { m_block_type = t; }

	void SetUp(bool b) { m_hit_up = b; }
	void SetDown(bool b) { m_hit_down = b; }
	void SetLeft(bool b) { m_hit_left = b; }
	void SetRight(bool b) { m_hit_right = b; }

	void EnemyHit(int enemynume);
	float m_hp;			//体力（仮）
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

	//踏んでいるblockの種類を確認用
	int  m_block_type;

	//test
	float px, py; //交点

	int reset;

	bool hit_flag;
	bool stay_flag;


	int   m_hit_time;	//ダメージ間隔

	bool climb_flag;	//昇降フラグ

	bool falldamage_flag;	//落下ダメージフラグ

	bool reset_falldamage_cacancel_flag;//リスポーンリスポーン時の最初の落下ダメージを無効化

	bool landing_flag;//地面に着地した時用フラグ

	float m_py_h;

	//コントローラー用仮変数

	float m_con_x;
	float m_con_y;
	int m_con_num;
	bool m_con_flag;


};