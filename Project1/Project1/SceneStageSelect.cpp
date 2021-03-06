
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
CSceneStageSelect::CSceneStageSelect()
{

}

//デストラクタ
CSceneStageSelect::~CSceneStageSelect()
{

}

//ゲームタイトル初期化メソッド
void CSceneStageSelect::InitScene()
{

	CObjStageSelect* p = new CObjStageSelect();
	Objs::InsertObj(p, OBJ_STAGE_SELECT, 1);

	//SE情報の登録
	Audio::LoadAudio(0, L"素材/BGM/Select.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"素材/SE/button01.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(2, L"素材/SE/button02.wav", SOUND_TYPE::EFFECT);


	//画像情報を登録
	Draw::LoadImageW(L"素材/画像/ステージ選択背景.png", 0, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/画像/ステージ選択.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/仮/Animation.png", 2, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/画像/しずく(水).png", 3, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/しずく(なし).png", 4, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/背景.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/夕方背景.png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/夜背景.png", 7, TEX_SIZE_1024);
	
	Audio::Start(0);
}

//ゲームタイトル実行メソッド
void CSceneStageSelect::Scene()
{
	Input::UpdateXControlerConnected();
}