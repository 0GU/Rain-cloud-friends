
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
CSceneTitle::CSceneTitle()
{
	
}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームタイトル初期化メソッド
void CSceneTitle::InitScene()
{
	CObjTitle* p = new CObjTitle;
	Objs::InsertObj(p, OBJ_TITLE, 1);

	//画像情報を登録
	Draw::LoadImageW(L"素材/仮/タイトル.png", 0, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/画像/title.png", 1, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/仮/Animation.png", 2, TEX_SIZE_64);

	//SE情報の登録
	Audio::LoadAudio(0, L"素材/BGM/rain1.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"素材/SE/button01.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(2, L"素材/SE/button02.wav", SOUND_TYPE::EFFECT);

	Audio::Start(0);

}

//ゲームタイトル実行メソッド
void CSceneTitle::Scene()
{
	Input::UpdateXControlerConnected();
}