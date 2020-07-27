#pragma once
#pragma once
#pragma once
#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：クリア
class CSceneClear :public CScene
{
public:
	CSceneClear(float m_hp, float cl_hp,int stage);//主人公のＨＰと雲のＨＰ
	~CSceneClear() ;
	void InitScene();//ゲームタイトルの初期化メソッド
	void Scene();	 //ゲームタイトルの実行中メソッド
private:
	float hero_hp;
	float cloud_hp;
	int stageselect;
};