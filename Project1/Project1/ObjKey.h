#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjKey : public CObj
{
public:
	CObjKey(float x, float y, int k_num);
	~CObjKey() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	int GetKnum();


private:
	float m_x, m_y;
	int Key_num;

	bool delete_flag;
};