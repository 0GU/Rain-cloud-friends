#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjDoormanager : public CObj
{
public:
	CObjDoormanager() {};
	~CObjDoormanager() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetPos(int D_num, int binary, float x, float y);
	void MoveDoor(int D_num, int binary);
	
private:
	bool Key[10];
	 float pos[10][2][2];//[ドア番号][対になっているドアの識別][ドアの座標]
	
};