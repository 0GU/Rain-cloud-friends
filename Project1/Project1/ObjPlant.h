#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjPlant : public CObj
{
public:
	CObjPlant(float x, float y,int count);
	~CObjPlant() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float m_px, m_py;
	int grow;
private:
	int   m_ani_time;   //アニメーションフレーム動作間隔
	int   m_ani_frame;  //描画フレーム

	float m_ani_max_time; //アニメーション動作間隔最大値
	bool stay_flag;
	int HP;
	bool grow_flag;
};