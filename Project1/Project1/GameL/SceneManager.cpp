#include <stdio.h>
#include <wchar.h>
#include "DirectXDevice.h"
#include "DrawTexture.h"
#include "DrawFont.h"
#include "Audio.h"
#include "SceneObjManager.h"
#include "SceneManager.h"
#include "HitBoxManager.h"
#include "MultiThread.h"
#include "WinInputs.h"

using namespace GameL;

#define SAFE_DELETE(p) { if(p){ delete (p);    (p)=nullptr;  }  }

//FPS表示設定
#ifdef _DEBUG
	#define HIT_DRAW	(true)	//当たり判定表示(デバック用)
	#define DRAW_FPS	(true)	//FPS表示
#else
	#define HIT_DRAW	(false)	//当たり判定非表示(リリース用)
	#define DRAW_FPS	(false)	//FPS非表示
#endif

CScene*			CSceneManager::m_NewScene;			//新しいシーン情報
CScene*			CSceneManager::m_Scene;				//現在のシーン情報
unsigned long	CSceneManager::m_TimeStart;
unsigned long	CSceneManager::m_TimeEnd;
unsigned long	CSceneManager::m_Time;
int				CSceneManager::m_TimeCount;


//登録してるシーンを実行する
void CSceneManager::GameLoop()
{
	m_TimeCount++;	
	m_TimeStart=timeGetTime();
	
	CDirectXDeviec::ViewClear();
	CDirectXDeviec::ViewDraw2D();

	Swap();			//シーン切り替え
	SceneAction();	//シーンアクション実行
	SceneDraw();	//シーン描画
	
	m_TimeEnd=timeGetTime();
	m_Time+= m_TimeEnd - m_TimeStart;

	//FPS----------------
	if(DRAW_FPS)
	{
		static wchar_t  c[8];
		static float cl[4]={1.0f,1.0f,1.0f,1.0f};
		if(m_TimeCount>100)
		{
			swprintf_s(c,L"%d",m_Time/100);
			m_Time=0;
			m_TimeCount=0;
		}
		CDrawFont::StrDraw(c,0,0,16,cl);
	}
	//-------------------

	CDirectXDeviec::ViewFlip();		//スワップ
}

void CSceneManager::SceneAction()
{
	if(m_Scene!=NULL) 
		m_Scene->Scene(); //シーンの進行
	//シーンの中にいるオブジェクト情報	
	CSceneObjManager::ObjAction();
	//当たり判定実行
	CHitBoxManager::AllHitCheck();
}

void CSceneManager::SceneDraw()
{
	//シーンの中にいる描画オブジェクト情報
	CSceneObjManager::ObjDraw();
	//当たり判定表示
	if(HIT_DRAW)
	{
		CHitBoxManager::DrawHitBox();
	}
}

//初期化
void CSceneManager::Init()
{
	m_TimeStart=m_TimeEnd=timeGetTime();
	m_Time		= 0;
    m_TimeCount	= 0;
	m_Scene		= nullptr;
	m_NewScene	= nullptr;
}

void CSceneManager::SetScene(CScene* scene)
{
	m_NewScene=scene;
}

CScene* CSceneManager::GetScene()
{
	return m_Scene;
}

void CSceneManager::Delete()
{
	SAFE_DELETE(m_Scene);
}

//シーン切り替え
void CSceneManager::Swap()
{
	if(m_Scene == m_NewScene)
	{
		if(m_Scene == nullptr)
		{
			CMultiThread::End();
		}

		return ;
	}

	if(m_Scene!=nullptr)
	{
		//シーン切り替えによるデータの破棄
		//テクスチャ・グラフィック・オブジェクト・ヒットボックス情報の削除
		CHitBoxManager::DeleteAllListData();
		CSceneObjManager::ListDeleteSceneObj();
		CDrawTexture::DeleteImage(); 
		CAudio::DeleteAudio();
		CDrawFont::ListDelete();
		SAFE_DELETE(m_Scene);
	}

	if(m_NewScene==nullptr)
	{
		SAFE_DELETE(m_Scene);
		CMultiThread::End();
		return ;
	}
	m_Scene=m_NewScene;
	m_Scene->InitScene();		//シーンの初期化
}