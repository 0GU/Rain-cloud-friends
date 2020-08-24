
//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL/UserData.h"
#include"GameL/WinInputs.h"

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
	else if (stageselect == 3)
		p = Save::ExternalDataOpen(L"セーブ確認用3.csv", &size);//外部データ読み込み
	int map[20][100];
	int count = 1;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			
			if (w >= 10)
			{
				count += 3;
			}
			else
			{
				count += 2;
			}
		}
	}


	//SE情報の登録
	Audio::LoadAudio(0, L"素材/BGM/Stage1仮.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"素材/BGM/風仮.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(2, L"素材/SE/ジャンプ.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(3, L"素材/SE/着地.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(4, L"素材/SE/ダメージ音.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(5, L"素材/SE/雨.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(6, L"素材/SE/被弾.wav", SOUND_TYPE::EFFECT);

	//画像情報を登録
	Draw::LoadImageW(L"素材/仮/image.png", 0, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/仮/mapcip.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/仮/Animation.png", 2, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/仮/Pose.png", 3, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/仮/選択.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/仮/蜘蛛.png", 5, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/仮/HP(透過).png", 6, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/仮/ito.png", 7, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/画像/雲のみ.png", 8, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/仮/スライム.png", 9, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/画像/植物ミニ.png", 10, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/画像/追尾敵0.png", 11, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/画像/妖精.png", 12, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/岩.png", 13, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/仮/Game背景仮.png", 22, TEX_SIZE_1024);
	if(stageselect==1)
	{
		Audio::Start(0);
		Audio::Start(1);
	}
	

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero(stageselect);
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//stageオブジェクト作成
	CObjStage* objb = new CObjStage(map);
	Objs::InsertObj(objb, OBJ_STAGE, 9);

	//Poseオブジェクト作成
	CObjPose* objp = new CObjPose(0,0);
	Objs::InsertObj(objp, OBJ_POSE, 11);

	//主人公オブジェクト作成
	CObjCloud* objc = new CObjCloud(stageselect);
	Objs::InsertObj(objc, OBJ_CLOUD, 10);

	//体力バーオブジェクト作成
	CObjHp* objh = new CObjHp();
	Objs::InsertObj(objh, OBJ_HP, 11);

	//主人公オブジェクト作成
	CObjSinEnemy* objs = new CObjSinEnemy(400,400);
	Objs::InsertObj(objs, OBJ_SINENEMY, 10);
}

//ゲームメイン実行メソッド
void CSceneGameMain::Scene()
{
	Input::UpdateXControlerConnected();
}