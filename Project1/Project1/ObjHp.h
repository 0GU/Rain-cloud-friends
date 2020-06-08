#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjHp : public CObj
{
public:
	CObjHp() {};
	~CObjHp() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float x, y;
private:
	float he_hp;	//体力量：主人公
	float cl_hp;	//体力量：雲
};