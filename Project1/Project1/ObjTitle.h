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

	float m_fade;//黒画面用(仮)
private:
	bool  move_flag;//２回目ぼフェードを動かす用
	bool m_fade_f;//フェードインアウト判別用フラグ
	bool key_flag;//キー押し確認用
	bool select_flag;//上下判定用
	bool description_flag;//説明画面表示用

	//矢印キー描画用---------------------------
	float m_ani_time;//アニメーション時間
	float m_ani_max;//アニメーション最大値
	int m_con_num;//コントローラー判別用変数
};