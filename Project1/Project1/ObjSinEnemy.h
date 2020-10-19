#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：Sin敵機
class CObjSinEnemy :public CObj
{
public:
	CObjSinEnemy(float x, float y);//コンストラクタ
	~CObjSinEnemy() {};
	void Init();//イニシャライズ
	void Action();//アクション
	void Draw();//ドロー
private:
	float m_x;//敵機のｘ方向の位置
	float m_y;//敵機のｙ方向の位置
	float m_vx;//敵機移動ベクトルX
	float m_vy;//敵機移動ベクトルY
	float m_r;//サインカーブ用の角度

	int   m_ani_time;   //アニメーションフレーム動作間隔
	int   m_ani_frame;  //描画フレーム

	float m_ani_max_time; //アニメーション動作間隔最大値

	float m_posture;	//姿勢
	float pos_init;	//沸いた時の位置記憶用

	int m_charge_time;//チャージ時間
	int m_atk_time;//攻撃間隔

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool stay_flag;
	bool m_move;//移動の向き制御用 true=右 false=左
	bool m_atk_flag;//攻撃モード用
	bool m_charge_flag;//チャージ用

	bool sleep_flag;//デバッグ用停止フラグ

};