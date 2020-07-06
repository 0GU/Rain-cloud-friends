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
	float m_hp;			//体力（仮）
	
private:
	int reset;

	float m_px;
	float m_py;
	float m_vx;
	float m_vy;



	bool stay_flag;
	bool rain_flag;
};