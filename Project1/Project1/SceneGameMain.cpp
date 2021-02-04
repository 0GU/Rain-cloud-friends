
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
	p = Save::ExternalDataOpen(L"Stage1x.csv", &size);//外部データ読み込み
	else if(stageselect==2)
	p = Save::ExternalDataOpen(L"Stage2.csv", &size);//外部データ読み込み
	else if (stageselect == 3)
		p = Save::ExternalDataOpen(L"ギミック確認.csv", &size);//外部データ読み込み
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
	Audio::LoadAudio(6, L"素材/SE/消火.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(7, L"素材/SE/成長.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(8, L"素材/SE/発射音.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(9, L"素材/SE/警告.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(10, L"素材/SE/瀕死.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(11, L"素材/SE/瞬間移動.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(12, L"素材/SE/上る.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(20, L"素材/SE/ポーズ.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(21, L"素材/SE/button01.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(22, L"素材/SE/button02.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(23, L"素材/BGM/夕方.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(24, L"素材/BGM/夜.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(25, L"素材/SE/移動音.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(26, L"素材/SE/雲移動音.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(27, L"素材/SE/逃走.wav", SOUND_TYPE::EFFECT);
	//画像情報を登録
	Draw::LoadImageW(L"素材/画像/testtt.png", 0, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/仮/mapcip.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/仮/Animation.png", 2, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/画像/ポーズ画像.png", 3, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/仮/選択.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/仮/蜘蛛.png", 5, TEX_SIZE_64);
	Draw::LoadImageW(L"素材/仮/HP(透過).png", 6, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/画像/雫.png", 7, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/画像/雲のみ.png", 8, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/仮/スライム.png", 9, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/画像/植物ミニ.png", 10, TEX_SIZE_128);
	Draw::LoadImageW(L"素材/画像/追尾敵0.png", 11, TEX_SIZE_2048);
	Draw::LoadImageW(L"素材/画像/妖精2.png", 12, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/岩.png", 13, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/イノシシ2.png", 14, TEX_SIZE_256);
	Draw::LoadImageW(L"素材/仮/test女の子.png", 15, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/ジャンプ.png", 16, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/死亡.png", 17, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/植物完成.png", 18, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/植物成長後花.png", 20, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/押す.png", 19, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/背景.png", 22, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/夕方背景.png", 23, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/夜背景.png", 24, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/HP枠.png", 25, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/HP.png", 26, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/仮/ito.png", 27, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/土ブロック.png", 30, TEX_SIZE_1024);//実験　ぬかるみ床用
	Draw::LoadImageW(L"素材/画像/待機修正.png", 31, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/ジャンプ.png", 32, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/押す修正版.png", 33, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/看板.png", 34, TEX_SIZE_256);
	Draw::LoadImageW(L"素材/画像/砂.png", 35, TEX_SIZE_512);
	Draw::LoadImageW(L"素材/画像/亀2.png", 36, TEX_SIZE_512);
	Draw::LoadImageW(L"素材/画像/テキストボックス.png", 45, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/テキストボックス2.png", 46, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/テキストボックス3.png", 47, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/テキストボックス4.png", 48, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/テキストボックス5.png", 49, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/テキストボックス6.png", 50, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/テキストボックス7.png", 51, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/テキストボックス8.png", 52, TEX_SIZE_1024);
	Draw::LoadImageW(L"素材/画像/テキストボックス9.png", 53, TEX_SIZE_1024);


	if(stageselect==1)
	{
		Audio::Start(0);
		Audio::Start(1);
	}
	if (stageselect == 2)
	{
		Audio::Start(23);
		Audio::Start(1);
	}
	if (stageselect == 3)
	{
		Audio::Start(24);
		Audio::Start(1);
	}
	//Audio::Start(0);

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero(stageselect);
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//stageオブジェクト作成
	CObjStage* objb = new CObjStage(map,stageselect);
	Objs::InsertObj(objb, OBJ_STAGE, 9);

	//Poseオブジェクト作成
	CObjPose* objp = new CObjPose(0,0,stageselect);
	Objs::InsertObj(objp, OBJ_POSE, 11);

	//主人公オブジェクト作成
	CObjCloud* objc = new CObjCloud(stageselect);
	Objs::InsertObj(objc, OBJ_CLOUD, 10);

	//体力バーオブジェクト作成
	CObjHp* objh = new CObjHp();
	Objs::InsertObj(objh, OBJ_HP, 11);

	CObjDoormanager* objd = new CObjDoormanager();
	Objs::InsertObj(objd, OBJ_DOORMANAGER, 10);

	//実験　亀
/*	CObjTurtle* objt = new CObjTurtle(400,600);
	Objs::InsertObj(objt, OBJ_TURTLE, 12);

	//実験　亀
	CObjTurtle* objt2 = new CObjTurtle(480, 600);
	Objs::InsertObj(objt2, OBJ_TURTLE, 12);
	*/
}

//ゲームメイン実行メソッド
void CSceneGameMain::Scene()
{
	Input::UpdateXControlerConnected();
}