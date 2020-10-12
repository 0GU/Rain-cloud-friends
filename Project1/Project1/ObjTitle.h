#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：タイトル
class CObjTitle : public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float x, y;
	float m_y1;//黒画面用(仮)
private:
	int hoge;//仮
	float m_scroll;
	bool  move_flag;
	bool scroll_flag;//ははっ
	bool key_flag;//キー押し確認用
	bool select_flag;//上下判定用
	bool description_flag;//説明画面表示用

};