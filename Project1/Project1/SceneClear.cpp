
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
CSceneClear::CSceneClear()
{

}

//デストラクタ
CSceneClear::~CSceneClear()
{

}

//ゲームタイトル初期化メソッド
void CSceneClear::InitScene()
{
	CObjClear* p = new CObjClear();
	Objs::InsertObj(p, OBJ_CLEAR, 1);
	//SE情報の登録
	Audio::LoadAudio(0, L"素材/BGM/rain1.wav", SOUND_TYPE::BACK_MUSIC);

	//画像情報を登録
	Draw::LoadImageW(L"素材/仮/White.png", 0, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/仮/StageClear.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/仮/Shizuku.png", 2, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/仮/Animation.png", 3, TEX_SIZE_64);
}

//ゲームタイトル実行メソッド
void CSceneClear::Scene()
{

}