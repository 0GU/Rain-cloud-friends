
//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL/UserData.h"

//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "SceneGameMain.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameMain::CSceneGameMain(int num)
{
	stageselect = num;
}

//デストラクタ
CSceneGameMain::~CSceneGameMain()
{

}

//ゲームメイン初期化メソッド
void CSceneGameMain::InitScene()
{
	//外部データの読み込み(ステージ情報)
	unique_ptr<wchar_t> p;  //ステージ情報ポインター
	int size;				//ステージ情報の大きさ
	if(stageselect==1)
	p = Save::ExternalDataOpen(L"ギミック確認.csv", &size);//外部データ読み込み
	else if(stageselect==2)
	p = Save::ExternalDataOpen(L"ステージデータ.csv", &size);//外部データ読み込み

	int map[10][100];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;
		}
	}


	//SE情報の登録
	//Audio::LoadAudio(0, L"", SOUND_TYPE::BACK_MUSIC);
	//Audio::LoadAudio(1, L"", SOUND_TYPE::EFFECT);

	//画像情報を登録
	Draw::LoadImageW(L"素材/仮/image.png", 0, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/仮/mapcip.png", 1, TEX_SIZE_1024);

	//Audio::Start(0);

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero(stageselect);
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//stageオブジェクト作成
	CObjStage* objb = new CObjStage(map);
	Objs::InsertObj(objb, OBJ_STAGE, 9);

}

//ゲームメイン実行メソッド
void CSceneGameMain::Scene()
{

}