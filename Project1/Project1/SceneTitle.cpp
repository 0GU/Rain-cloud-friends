
//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "GameHead.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{
	CObjTitle* p = new CObjTitle;
	Objs::InsertObj(p, OBJ_TITLE, 1);
}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームタイトル初期化メソッド
void CSceneTitle::InitScene()
{


}

//ゲームタイトル実行メソッド
void CSceneTitle::Scene()
{

}