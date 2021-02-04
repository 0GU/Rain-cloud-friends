#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjSand : public CObj
{
public:
	CObjSand(float x, float y);
	~CObjSand() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float m_px, m_py;
	void RainHit(int* hp, bool* damege);
	//blockとの衝突状態確認用
	bool m_hit_up = false;
	bool m_hit_down = false;
	bool m_hit_left = false;
	bool m_hit_right = false;
private:
	int hoge;//仮
	bool m_hit_rain;//雨に当たったか当たっていないか
	float m_fade_num;//徐々にフェードアウトする値を入れる
};

