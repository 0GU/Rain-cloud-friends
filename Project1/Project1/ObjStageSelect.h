#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjStageSelect : public CObj
{
public:
	CObjStageSelect() {};
	~CObjStageSelect() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	int stageflag;//仮
	bool keyflag;//仮
	float m_y1;//黒画面用(仮)
	float m_y2;

	float m_scroll;
	bool  move_flag;
	bool scroll_flag;//ははっ
};