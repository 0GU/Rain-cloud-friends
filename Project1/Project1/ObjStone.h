#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjStone : public CObj
{
public:
	CObjStone(float x, float y);
	~CObjStone() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	float SetVX(float vx) { m_vx = vx; };

	float m_px, m_py;
	float m_vx, m_vy;
private:
	bool stay_flag;
};