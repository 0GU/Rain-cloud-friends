#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：亀
class CObjTurtle : public CObj
{
public:
	CObjTurtle(float x, float y);
	~CObjTurtle() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

	float GetVx() { return m_vx; };
	float GetPY() { return m_py; };

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
	bool stay_flag;
	int m_hp;
	//被弾関係
	bool m_damege_flag;//被弾フラグ　実験時はtrueで停止
	float m_transparent;//逃走時徐々に透明に変化させる変数
	bool m_escaoe_flag;//逃走終了フラグ　trueでオブジェクト破棄
	//踏んでいるblockの種類を確認用
	int  m_block_type;
	bool m_swanp;
};