#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjSwanp : public CObj
{
public:
	CObjSwanp(float x, float y);
	~CObjSwanp() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetFlag(bool b) { m_swanp_flag = b; m_swanp_time = 300; }//実験　沼ブロック
	bool GetFlag() { return m_swanp_flag; }

private:
	float m_px;			//位置
	float m_py;
	int m_hp;
	bool m_swanp_flag;
	int m_swanp_time;
	bool stay_flag;
};