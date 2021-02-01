#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjSign : public CObj
{
public:
	CObjSign(float x, float y,int i) ;
	~CObjSign() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	float x, y;
private:
	float m_px;			//位置
	float m_py;
	int sign_num;//看板の種類判別用
	bool m_hit_f;//当たっているかどうか
};