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
	int m_selectnum;//仮
	bool m_key_f;//仮
	float m_fade;//黒画面用(仮)

	bool  move_flag;//黒画面スイッチ
	bool m_fade_f;;//フェードインアウト判別用フラグ
	bool Clear_flag[3];//クリアフラグ仮（本番は配列でクリアの種類を分ける予定）
	bool Clear_flag2[3];//クリアフラグ仮（本番は配列でクリアの種類を分ける予定）
	bool Clear_flag3[3];//クリアフラグ仮（本番は配列でクリアの種類を分ける予定）
	bool title_flag;//タイトル移行用フラグ

	float m_ani_time;
	float m_ani_max;
};