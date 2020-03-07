//削除されていないメモリを出力にダンプする
#include <crtdbg.h>
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

      #define new DBG_NEW
   #endif
#endif  // _DEBUG

//LIB
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d11.lib") 
#pragma comment(lib, "d3dCompiler.lib")
#pragma comment(lib, "XAudio2.lib")

//メインヘッダ
#include <stdio.h>
#include <process.h>
#include <Windows.h>

#include "SetWindow.h"
#include "DirectXDevice.h"
#include "DrawTexture.h"
#include "WinInputs.h"
#include "Audio.h"
#include "MultiThread.h"
#include "DrawFont.h"
#include "SceneManager.h"
#include "SceneObjManager.h"
#include "HitBoxManager.h"
#include "UserData.h"

#include "..\GameHead.h"
#include "..\main.h"

using namespace GameL;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Main関数
int APIENTRY wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR szCmdLine,int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	wchar_t  name []={GAME_NAME};	//ウィンドウ＆タイトルネーム
	MSG  msg;						//メッセージハンドル
	
	//ＣＯＭ初期化
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	//ウィンドウステータス
	WNDCLASSEX wcex = {
	   sizeof(WNDCLASSEX),
	   CS_HREDRAW | CS_VREDRAW,
	   WndProc,0, 0,hInstance,
	   NULL, NULL,(HBRUSH)(COLOR_WINDOW+1),
	   NULL,name,NULL
	};

	//ウィンドウクラス作成
	RegisterClassEx( &wcex );

	//ウィンドウ作成初期化
	LSetWindow::NewWindow(WINDOW_SIZE_W,WINDOW_SIZE_H,name,hInstance);
	
	//DirectXデバイス作成初期化
	float color[]=BACK_COLOR;
	CDirectXDeviec::InitDevice(LSetWindow::GethWnd(), PIXEL_SIZE_W, PIXEL_SIZE_H,color);

	//２Ｄ用テクスチャイメージ読み込み初期化
	CDrawTexture::InitDraw(CDirectXDeviec::GetDevice(),CDirectXDeviec::GetDeviceContext(),
		PIXEL_SIZE_W, PIXEL_SIZE_H,SCENE_IMG_MAX);
	
	//インプット初期化
	CWinInputs::Init();

	//オーディオ初期化
	CAudio::Init(SCENE_AUDIO_MAX);

	//フォント初期化
	CDrawFont::Init(CDirectXDeviec::GetDevice(),CDirectXDeviec::GetDeviceContext());

	//オブジェクトマネージャー
	CSceneObjManager::Init();

	//当たり判定初期化
	CHitBoxManager::Init();

	//ユーザーデータ
	UserData user_data;
	memset(&user_data,0x00,sizeof(CUserData));
	CUserData::Init(&user_data,sizeof(UserData));

	//初期シーン読み込み
	#ifdef SET_GAME_START
		CSceneManager::SetScene(new SET_GAME_START() );
	#else
		CSceneManager::SetScene(nullptr);
	#endif

	//マルチスレッド起動
	CMultiThread::Init(&CSceneManager::GameLoop);

	//メッセージループ
	do
	{

		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			
			TranslateMessage( &msg );
			DispatchMessage(&msg);
		}
		
		//シーン無しで強制終了
		if(CMultiThread::GetEnd()==false)
		{
			break;
		}

	}while( msg.message != WM_QUIT );
	

	CMultiThread::Delete();
	CUserData::Delete();
	CHitBoxManager::Delete();
	CSceneObjManager::Delete();
	CSceneManager::Delete();
	CDrawFont::Delete();
	CDrawTexture::DeleteDrawTexture();
	CAudio::Delete();
	CDirectXDeviec::ShutDown();
	CoUninitialize();//ＣＯＭ解除
	
	//この時点で開放されていないメモリの情報の表示
	_CrtDumpMemoryLeaks();
	
	return true;
}

//コールバック関数
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//マウス情報取得用
	CWinInputs::WmInput(hWnd, &uMsg, &lParam);
    
	switch (uMsg)
	{
		case WM_KEYDOWN:		//ESCキーで終了
			switch (wParam)
			{
				case VK_ESCAPE:
					CMultiThread::End();
					LSetWindow::DeleteWindow();
					PostQuitMessage(0);	
				break;
			}
		break;
		case WM_CLOSE:			// ウィンドウを閉じる場合
			CMultiThread::End();
			PostQuitMessage(0);	
			break;
		case WM_DESTROY:		// 終了する場合
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


