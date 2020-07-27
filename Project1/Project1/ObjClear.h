#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjClear : public CObj
{
public:
	CObjClear(float m_hp, float cl_hp,int stage) ;
	~CObjClear() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float hero_hp;
	float cloud_hp;
	float x, y;
private:
	int hoge;//仮

	bool key_flag;//キー押し確認用
	float m_y1;//黒画面位置(仮)
	bool  move_flag;
	bool scroll_flag;
	bool Clear_flag[3];//1:Excerent 2:Great 3:Good
	int stageselect;
};