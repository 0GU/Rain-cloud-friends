
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
	Audio::LoadAudio(0, L"BGM/rain1.wav", SOUND_TYPE::BACK_MUSIC);

	Audio::Start(0);
}

//ゲームタイトル実行メソッド
void CSceneStageSelect::Scene()
{

}