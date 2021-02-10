#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjDoor : public CObj
{
public:
	CObjDoor(float x,float y,int d_num,int binary);
	~CObjDoor() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	

private:
	float m_x, m_y;
	int num;
	int bin;

	bool flag;
	bool stay_flag;

};