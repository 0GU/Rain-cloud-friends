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

	void SetVX(float vx) { m_vx = vx; };
	float GetPX_L() { return m_px; };
	float GetPX_R() { return m_px+128; };
	float GetPY() { return m_py; };
	bool Gethr() { return m_hit_right; };
	bool Getflag() { return hit_flag; };
	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//踏んでいるblockの種類を確認用
	int  m_block_type;

	float m_px, m_py;
	float m_vx, m_vy;
private:
	bool stay_flag;
	bool hit_flag;
};