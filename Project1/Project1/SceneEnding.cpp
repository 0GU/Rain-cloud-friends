//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include"GameL/WinInputs.h"
//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "GameHead.h"

//コンストラクタ
CSceneEnding::CSceneEnding()
{

}

//デストラクタ
CSceneEnding::~CSceneEnding()
{

}

//ゲームタイトル初期化メソッド
void CSceneEnding::InitScene()
{
	CObjEnding* e = new CObjEnding;
	Objs::InsertObj(e, OBJ_ENDING, 1);
	//画像情報の登録
	Draw::LoadImageW(L"素材/画像/エンディング.png", 0, TEX_SIZE_1024);

	//BGMセット
	Audio::LoadAudio(0, L"素材/BGM/Ending.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::Start(0);
}

//ゲームタイトル実行メソッド
void CSceneEnding::Scene()
{
	Input::UpdateXControlerConnected();
}