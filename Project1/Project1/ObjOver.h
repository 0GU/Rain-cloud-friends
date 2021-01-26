#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ゲームオーバー
class CObjOver : public CObj
{
public:
	CObjOver(int stagenum);
	~CObjOver() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float x, y;
private:
	int restart;//リスタート用
	int selectnum;//選択場所
	int selectnum_c;//選択場所（確認画面）

	bool  move_flag;//２回目ぼフェードを動かす用
	bool m_fade_f;//フェードインアウト判別用フラグ
	bool key_flag;//キー押し確認用
	bool  move_flag2;//２回目ぼフェードを動かす用
	bool scroll_flag;//スクロール用　true:停止　false:実行中
	bool check_flag;//確認用
	float m_fade;//黒画面用(仮)
	int m_con_num;//仮
	float m_ani_time;//アニメーション時間
	float m_ani_max;//アニメーション最大値
};
