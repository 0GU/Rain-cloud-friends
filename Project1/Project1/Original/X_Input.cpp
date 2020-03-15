#define GLOBAL_INSTANCE
#include <windowsx.h>
#include "DxLib.h"
#include "main.h"


//全画面表示用変数
int					TemporaryHandle;
LRESULT CALLBACK MyDlgProc( HWND, UINT, WPARAM, LPARAM);
HINSTANCE			hDialog;

//ループで必ず行う３大処理
int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;//プロセス処理がエラーなら-1を返す
	if(ClearDrawScreen()!=0)return -1;//画面クリア処理がエラーなら-1を返す
	Get_HitInputStateAll();  //現在のパッド入力処理を行う

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	int i;

	hDialog = hInstance;

	// タイトルを変更
	SetMainWindowText( "ゲームパッド入力　確認アプリ" );

	//ＤＸライブラリの動作ログ
	SetOutApplicationLogValidFlag(TRUE);

	
	//----------------------------------------
	//画面表示モードに関する初期動作設定
	//----------------------------------------	

	//ウィンドウモードの設定
	SetGraphMode( 640 , 480, 32);
	//ウィンドウモード反映
	ChangeWindowMode( TRUE );

	//DXライブラリの初期化 
	if( DxLib_Init() == -1 ){ return -1;}					//初期化失敗
	if( SetDrawScreen( DX_SCREEN_BACK )   ){ return -1;}	//裏画面準備失敗

	//キーアサインの初期化
	Init_key_state();

	while(ProcessLoop()==0){//メインループ


		//=====================
		//計算部分
		//=====================	

		Calc_KeyState();	//キーの入力状態をチェックする

		//=====================
		//描画部分
		//=====================
		DrawString( 50, 50, "押されたボタン", GetColor(255,255,255));
		for( i = 0 ; i < KEY_MAX ; i++ ){
			if( Input.key[i] > 0 ){
				if( XInput_PadNum != -1  ){
					DrawString( 50, 80, "XInput", GetColor(255,255,255));
					DrawString( 50, 100, ConfigPad.XI_Name[i], GetColor(255,255,255));
				}else{
					DrawString( 50, 80, "DirectInput", GetColor(255,255,255));
					DrawString( 50, 100, ConfigPad.DI_Name[i], GetColor(255,255,255));
				}
			}
		}

		DrawString( 440, 460, "Created by Axion 2016", GetColor(255,255,255));

		ScreenFlip();		//裏画面反映

		Sleep(100);

		//エスケープが入力されたらブレイク
		if(CheckStateKey(KEY_INPUT_ESCAPE)==1)break;


    }

    DxLib_End();//ＤＸライブラリ終了処理
    return 0;
}
