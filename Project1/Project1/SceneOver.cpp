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
CSceneOver::CSceneOver(int stage)
{
	stagenum = stage;
}

//デストラクタ
CSceneOver::~CSceneOver()
{

}

//ゲームオーバー初期化メソッド
void CSceneOver::InitScene()
{
	CObjOver* over = new CObjOver(stagenum);
	Objs::InsertObj(over, OBJ_OVER, 1);

	//SE情報の登録
	Audio::LoadAudio(0, L"素材/BGM/Select.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"素材/SE/button01.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(2, L"素材/SE/button02.wav", SOUND_TYPE::EFFECT);

	Draw::LoadImageW(L"素材/仮/Animation.png", 3, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/仮/Over(仮、透過).png", 0, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/ゲームオーバー(仮).png", 1, TEX_SIZE_1024);

	
}

//ゲームオーバー実行メソッド
void CSceneOver::Scene()
{

}