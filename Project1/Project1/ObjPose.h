#pragma once
//使用するヘッダー
#include"GameL/SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


//オブジェクト：ステージセレクト
class CObjPose : public CObj
{
public:
	CObjPose(float x, float y);
	~CObjPose() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	
private:

	float m_px;
	float m_py;
	bool delete_flag;
	bool stay_flag;
};