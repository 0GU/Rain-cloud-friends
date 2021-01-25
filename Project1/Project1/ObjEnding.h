#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjEnding : public CObj
{
public:
	CObjEnding() {};
	~CObjEnding() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float x, y;
private:
	int hoge;//仮
	bool key_flag;
	bool  move_flag;//２回目ぼフェードを動かす用
	bool m_fade_f;//フェードインアウト判別用フラグ
	float m_fade;//フェード値
};