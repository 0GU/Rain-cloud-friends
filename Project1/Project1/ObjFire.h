#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjFire : public CObj
{
public:
	CObjFire(float x, float y);
	~CObjFire() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float m_px, m_py;
private:
	int   m_ani_time;   //アニメーションフレーム動作間隔
	int   m_ani_frame;  //描画フレーム

	float m_ani_max_time; //アニメーション動作間隔最大値
};