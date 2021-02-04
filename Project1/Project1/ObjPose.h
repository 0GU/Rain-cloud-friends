#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjPose : public CObj
{
public:
	CObjPose(float x, float y,int stage);
	~CObjPose() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	bool GetFlag() { return stay_flag; }
	int stage_num;
private:

	float m_px;
	float m_py;
	bool delete_flag;
	bool stay_flag;
	bool keyflag;//
	int select_num;//ポーズの選択カウント

	float m_ani_time;//アニメーション時間
	float m_ani_max;//アニメーション最大値

};