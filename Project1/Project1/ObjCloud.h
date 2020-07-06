#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjCloud : public CObj
{
public:
	CObjCloud(int stage);
	~CObjCloud() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー

	float GetHP() { return m_hp; }

	
private:
	int reset;

	float m_px;
	float m_py;
	float m_vx;
	float m_vy;

	float m_hp;			//体力（仮）

	bool stay_flag;
	bool rain_flag;

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
};