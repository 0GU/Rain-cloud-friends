#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ゲームオーバー
class CObjOver : public CObj
{
public:
	CObjOver(int stagenum) ;
	~CObjOver() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float x, y;
private:
	int restart;//リスタート用
	float m_y1;//黒画面位置(仮)
	int selectnum;//選択場所
	int selectnum_c;//選択場所（確認画面）

	bool keyflag;//キー状態　true:押している
	bool  move_flag;//画面移行中
	bool scroll_flag;//スクロール用　true:停止　false:実行中
	bool check_flag;//確認用

	int m_con_num;//仮
};