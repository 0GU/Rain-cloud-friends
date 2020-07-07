#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームオーバー
class CSceneOver :public CScene
{
public:
	CSceneOver(int stage) ;
	~CSceneOver() ;
	void InitScene();//ゲームタイトルの初期化メソッド
	void Scene();	 //ゲームタイトルの実行中メソッド
private:
	int stagenum;
};