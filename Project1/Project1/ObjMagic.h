#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjMagic : public CObj
{
public:
	CObjMagic(float x, float y,bool posture);
	~CObjMagic() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float x, y;

private:
	float m_px;//ｘ方向の位置
	float m_py;//ｙ方向の位置
	float m_vx;//ベクトルX
	float m_vy;//ベクトルY
	float m_r;//角度

	int   m_ani_time;   //アニメーションフレーム動作間隔
	int   m_ani_frame;  //描画フレーム
	bool m_del;
	bool m_posture;
	bool m_check;//位置チェック用

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool stay_flag;


	bool light_flag;//明るさ変更
	float m_light;
};