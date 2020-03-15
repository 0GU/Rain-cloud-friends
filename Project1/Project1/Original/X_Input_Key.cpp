#include "X_input.h"

#define XINPUT_MAX_CONTROLLERS 4			//XInput(XBox360用コントローラー)の最大接続数
#define POV_NUMBUR 0						//指定するハットスイッチの番号

DWORD				Find_XInputControler();	//XInput用コントローラの接続を確認

//DWORD				XInput_PadNum;			//XInput(XBox360用コントローラー)接続番号
_XINPUT_STATE		XInput_State;			//XInput(XBox360用コントローラー)の現在の状態
_XINPUT_GAMEPAD		XInput_Pad;				//XInput(XBox360用コントローラー)の現在の状態
_XINPUT_KEYSTROKE	XInput_KeyStroke;		//XInput(XBox360用コントローラー)のキーストローク データ

unsigned int		stateKey[256];			//キーボードの入力状態
int					StateInput[KEY_MAX];	//キー・パッドの入力状態
int					StatePad[KEY_MAX];		//パッドの入力状態(StatePad_D,StatePad_X)の比較結果
int					StatePad_D[KEY_MAX];	//DirectInputの入力状態
int					StatePad_X[KEY_MAX];	//XInput(XBox360用コントローラー)の入力状態


void Init_key_state(){

	//パッドの入力状態を初期化
	memset( &StatePad  , 0, sizeof(StatePad));
	memset( &StatePad_D, 0, sizeof(StatePad_D));

	//================================================
	//　一般型パッドの初期化
	//================================================
	ConfigPad.Dx_Default[KEY_DOWN  ]	= PAD_INPUT_DOWN;
	ConfigPad.Dx_Default[KEY_LEFT  ]	= PAD_INPUT_LEFT;
	ConfigPad.Dx_Default[KEY_RIGHT ]	= PAD_INPUT_RIGHT;
	ConfigPad.Dx_Default[KEY_UP	   ]	= PAD_INPUT_UP;
	ConfigPad.Dx_Default[KEY_NUM_4 ]	= PAD_INPUT_1;
	ConfigPad.Dx_Default[KEY_NUM_5 ]	= PAD_INPUT_2;
	ConfigPad.Dx_Default[KEY_NUM_6 ]	= PAD_INPUT_3;
	ConfigPad.Dx_Default[KEY_NUM_7 ]	= PAD_INPUT_4;
	ConfigPad.Dx_Default[KEY_NUM_8 ]	= PAD_INPUT_5;
	ConfigPad.Dx_Default[KEY_NUM_9 ]	= PAD_INPUT_6;
	ConfigPad.Dx_Default[KEY_NUM_10]	= PAD_INPUT_7;
	ConfigPad.Dx_Default[KEY_NUM_11]	= PAD_INPUT_8;
	ConfigPad.Dx_Default[KEY_NUM_12]	= PAD_INPUT_9;
	ConfigPad.Dx_Default[KEY_NUM_13]	= PAD_INPUT_10;
	ConfigPad.Dx_Default[KEY_NUM_14]	= PAD_INPUT_11;
	ConfigPad.Dx_Default[KEY_NUM_15]	= PAD_INPUT_12;

	ConfigPad.DI_Name[KEY_DOWN  ]	= "DOWN";
	ConfigPad.DI_Name[KEY_LEFT  ]	= "LEFT";
	ConfigPad.DI_Name[KEY_RIGHT ]	= "RIGHT";
	ConfigPad.DI_Name[KEY_UP    ]	= "UP";
	ConfigPad.DI_Name[KEY_NUM_4 ]	= "１";
	ConfigPad.DI_Name[KEY_NUM_5 ]	= "２";
	ConfigPad.DI_Name[KEY_NUM_6 ]	= "３";
	ConfigPad.DI_Name[KEY_NUM_7 ]	= "４";
	ConfigPad.DI_Name[KEY_NUM_8 ]	= "５";
	ConfigPad.DI_Name[KEY_NUM_9 ]	= "６";
	ConfigPad.DI_Name[KEY_NUM_10]	= "７";
	ConfigPad.DI_Name[KEY_NUM_11]	= "８";
	ConfigPad.DI_Name[KEY_NUM_12]	= "９";
	ConfigPad.DI_Name[KEY_NUM_13]	= "１０";
	ConfigPad.DI_Name[KEY_NUM_14]	= "１１";
	ConfigPad.DI_Name[KEY_NUM_15]	= "１２";

	ConfigPad.DxInput[KEY_DOWN	]	= ConfigPad.Dx_Default[KEY_DOWN  ];
	ConfigPad.DxInput[KEY_LEFT	]	= ConfigPad.Dx_Default[KEY_LEFT  ];
	ConfigPad.DxInput[KEY_RIGHT	]	= ConfigPad.Dx_Default[KEY_RIGHT ];
	ConfigPad.DxInput[KEY_UP	]	= ConfigPad.Dx_Default[KEY_UP	 ];
	ConfigPad.DxInput[KEY_NUM_4	]	= ConfigPad.Dx_Default[KEY_NUM_4 ];
	ConfigPad.DxInput[KEY_NUM_5 ]	= ConfigPad.Dx_Default[KEY_NUM_5 ];
	ConfigPad.DxInput[KEY_NUM_6 ]	= ConfigPad.Dx_Default[KEY_NUM_6 ];
	ConfigPad.DxInput[KEY_NUM_7	]	= ConfigPad.Dx_Default[KEY_NUM_7 ];
	ConfigPad.DxInput[KEY_NUM_8	]	= ConfigPad.Dx_Default[KEY_NUM_8 ];
	ConfigPad.DxInput[KEY_NUM_9	]	= ConfigPad.Dx_Default[KEY_NUM_9 ];
	ConfigPad.DxInput[KEY_NUM_10]	= ConfigPad.Dx_Default[KEY_NUM_10];
	ConfigPad.DxInput[KEY_NUM_11]	= ConfigPad.Dx_Default[KEY_NUM_11];
	ConfigPad.DxInput[KEY_NUM_12]	= ConfigPad.Dx_Default[KEY_NUM_12];
	ConfigPad.DxInput[KEY_NUM_13]	= ConfigPad.Dx_Default[KEY_NUM_13];
	ConfigPad.DxInput[KEY_NUM_14]	= ConfigPad.Dx_Default[KEY_NUM_14];
	ConfigPad.DxInput[KEY_NUM_15]	= ConfigPad.Dx_Default[KEY_NUM_15];


	//================================================
	//　XInput対応パッドの初期化
	//================================================

	XInput_PadNum = Find_XInputControler();	//コントローラＩＤの取得

	ConfigPad.XI_Default[KEY_DOWN  ]	= XINPUT_GAMEPAD_DPAD_DOWN;
	ConfigPad.XI_Default[KEY_LEFT  ]	= XINPUT_GAMEPAD_DPAD_LEFT;
	ConfigPad.XI_Default[KEY_RIGHT ]	= XINPUT_GAMEPAD_DPAD_RIGHT;
	ConfigPad.XI_Default[KEY_UP    ]	= XINPUT_GAMEPAD_DPAD_UP;
	ConfigPad.XI_Default[KEY_NUM_4 ]	= XINPUT_GAMEPAD_A;
	ConfigPad.XI_Default[KEY_NUM_5 ]	= XINPUT_GAMEPAD_B;
	ConfigPad.XI_Default[KEY_NUM_6 ]	= XINPUT_GAMEPAD_X;
	ConfigPad.XI_Default[KEY_NUM_7 ]	= XINPUT_GAMEPAD_Y;
	ConfigPad.XI_Default[KEY_NUM_8 ]	= 0x00;
	ConfigPad.XI_Default[KEY_NUM_9 ]	= 0x00;
	ConfigPad.XI_Default[KEY_NUM_10]	= XINPUT_GAMEPAD_LEFT_THUMB;
	ConfigPad.XI_Default[KEY_NUM_11]	= XINPUT_GAMEPAD_RIGHT_THUMB;
	ConfigPad.XI_Default[KEY_NUM_12]	= XINPUT_GAMEPAD_LEFT_SHOULDER;
	ConfigPad.XI_Default[KEY_NUM_13]	= XINPUT_GAMEPAD_RIGHT_SHOULDER;
	ConfigPad.XI_Default[KEY_NUM_14]	= XINPUT_GAMEPAD_START;
	ConfigPad.XI_Default[KEY_NUM_15]	= XINPUT_GAMEPAD_BACK;
	

	ConfigPad.XI_Name[KEY_DOWN  ]	= "DOWN";
	ConfigPad.XI_Name[KEY_LEFT  ]	= "LEFT";
	ConfigPad.XI_Name[KEY_RIGHT ]	= "RIGHT";
	ConfigPad.XI_Name[KEY_UP    ]	= "UP";
	ConfigPad.XI_Name[KEY_NUM_4 ]	= "Ａ";
	ConfigPad.XI_Name[KEY_NUM_5 ]	= "Ｂ";
	ConfigPad.XI_Name[KEY_NUM_6 ]	= "Ｘ";
	ConfigPad.XI_Name[KEY_NUM_7 ]	= "Ｙ";
	ConfigPad.XI_Name[KEY_NUM_8 ]	= "ＬＴ";
	ConfigPad.XI_Name[KEY_NUM_9 ]	= "ＲＴ";
	ConfigPad.XI_Name[KEY_NUM_10]	= "Ｌ３";
	ConfigPad.XI_Name[KEY_NUM_11]	= "Ｒ３";
	ConfigPad.XI_Name[KEY_NUM_12]	= "ＬＢ";
	ConfigPad.XI_Name[KEY_NUM_13]	= "ＲＢ";
	ConfigPad.XI_Name[KEY_NUM_14]	= "START";
	ConfigPad.XI_Name[KEY_NUM_15]	= "BACK";


	ConfigPad.XInput[KEY_DOWN  ]	= ConfigPad.XI_Default[KEY_DOWN  ];
	ConfigPad.XInput[KEY_LEFT  ]	= ConfigPad.XI_Default[KEY_LEFT  ];
	ConfigPad.XInput[KEY_RIGHT ]	= ConfigPad.XI_Default[KEY_RIGHT ];
	ConfigPad.XInput[KEY_UP    ]	= ConfigPad.XI_Default[KEY_UP    ];
	ConfigPad.XInput[KEY_NUM_4 ]	= ConfigPad.XI_Default[KEY_NUM_4 ];
	ConfigPad.XInput[KEY_NUM_5 ]	= ConfigPad.XI_Default[KEY_NUM_5 ];
	ConfigPad.XInput[KEY_NUM_6 ]	= ConfigPad.XI_Default[KEY_NUM_6 ];
	ConfigPad.XInput[KEY_NUM_7 ]	= ConfigPad.XI_Default[KEY_NUM_7];
	ConfigPad.XInput[KEY_NUM_8 ]	= ConfigPad.XI_Default[KEY_NUM_8 ];
	ConfigPad.XInput[KEY_NUM_9 ]	= ConfigPad.XI_Default[KEY_NUM_9 ];
	ConfigPad.XInput[KEY_NUM_10]	= ConfigPad.XI_Default[KEY_NUM_10];
	ConfigPad.XInput[KEY_NUM_11]	= ConfigPad.XI_Default[KEY_NUM_11];
	ConfigPad.XInput[KEY_NUM_12]	= ConfigPad.XI_Default[KEY_NUM_12];
	ConfigPad.XInput[KEY_NUM_13]	= ConfigPad.XI_Default[KEY_NUM_13];
	ConfigPad.XInput[KEY_NUM_14]	= ConfigPad.XI_Default[KEY_NUM_14];
	ConfigPad.XInput[KEY_NUM_15]	= ConfigPad.XI_Default[KEY_NUM_15];
	
}


//XInput用コントローラの接続を確認
DWORD Find_XInputControler(){

	DWORD dwResult;
	DWORD ret = -1;

	for (DWORD i = 0 ; i< XINPUT_MAX_CONTROLLERS ; i++ ){
		_XINPUT_STATE state;
		ZeroMemory( &state, sizeof(_XINPUT_STATE) );  // Simply get the state of the controller from XInput. 
		dwResult = XInputGetState( i, &state );
		if( dwResult == ERROR_SUCCESS ){
			// Controller is connected
			ret = i;
			break;
		}else{
			// Controller is not connected
		}
	}
	return ret;	//コントローラＩＤ値を返す

}

//パッド(XInput)の入力状態を取得
WORD Get_XInputPadState(DWORD PadNum){

	static DWORD dwPacketNumber_old;
	WORD wButtons = XInput_State.Gamepad.wButtons;

	XInputGetState( PadNum, &XInput_State);	
	if( XInput_State.dwPacketNumber - dwPacketNumber_old != 0 ){
		wButtons = XInput_State.Gamepad.wButtons;
	}
	dwPacketNumber_old = XInput_PadNum;	//パッドの状態を保存

	return wButtons;

}

//指定のキーが押されたかを返す
int CheckStateKey(unsigned char Handle){
        return stateKey[Handle];
}


//引数１と引数２のうち大きい方を引数１に代入する
int Input_A_or_B(int a, int b){
	int ret = a;
	
	if( a > b ){ ret = a;}else{ ret = b;}

	return ret;
}



//キーボードおよびパッドの入力をチェックする関数
void Get_HitInputStateAll(){
	static DWORD	dwPacketNumber_old;
	static int		XInputCheckTimer = 0;
	char	KeyStateBuf[256];
	int		i;
	int		PadInput_D	= 0;
	int		PadInput_X	= 0;
	int		ArrowState	= 0;
    int		mul			= 1;

	//キー入力部-----------------------------
	GetHitKeyStateAll( KeyStateBuf );
	for(int i=0;i<256;i++){
		if(KeyStateBuf[i] == 1){
			stateKey[i]++;
		}else{
			stateKey[i]=0;
		}
	}

	XInput_PadNum = Find_XInputControler();	//ＸｉｎｐｕｔコントローラＩＤの取得

	//パッド入力部-----------------------------
	if( XInput_PadNum != -1 ){
		//XInput
		PadInput_X = Get_XInputPadState(XInput_PadNum);		//パッドの入力状態を取得
		for(i=0;i<KEY_MAX;i++){
			if( PadInput_X & ConfigPad.XInput[i]){
				StatePad_X[i]++;
			}else{
				StatePad_X[i] = 0;
			}
		}
		PadType = 1;
	}else{
		//DirectInput
		PadInput_D = GetJoypadInputState( DX_INPUT_PAD1);	//パッドの入力状態を取得
		for(i=0;i<KEY_MAX;i++){
			if( PadInput_D & ConfigPad.DxInput[i]){
				StatePad_D[i]++;
			}else{
				StatePad_D[i] = 0;
			}
		}
		PadType = 0;
	}

	//どちらの入力があったか判定
    for(i=0;i<KEY_MAX;i++){
		StatePad[i] = Input_A_or_B( StatePad_D[i ], StatePad_X[i]);
    }

		//ゲームパッドの入力
        StateInput[KEY_LEFT		] = StatePad[KEY_LEFT  ];
        StateInput[KEY_UP		] = StatePad[KEY_UP    ];
        StateInput[KEY_RIGHT	] = StatePad[KEY_RIGHT ];
        StateInput[KEY_DOWN		] = StatePad[KEY_DOWN  ];
        StateInput[KEY_NUM_4	] = StatePad[KEY_NUM_4 ];
		StateInput[KEY_NUM_5	] = StatePad[KEY_NUM_5 ];
        StateInput[KEY_NUM_6	] = StatePad[KEY_NUM_6 ];
		StateInput[KEY_NUM_7	] = StatePad[KEY_NUM_7 ];
		StateInput[KEY_NUM_9	] = StatePad[KEY_NUM_9 ];
		StateInput[KEY_NUM_10	] = StatePad[KEY_NUM_10];
		StateInput[KEY_NUM_11	] = StatePad[KEY_NUM_11];
		StateInput[KEY_NUM_12	] = StatePad[KEY_NUM_12];
		StateInput[KEY_NUM_13	] = StatePad[KEY_NUM_13];
		StateInput[KEY_NUM_14	] = StatePad[KEY_NUM_14];
		StateInput[KEY_NUM_15	] = StatePad[KEY_NUM_15];

}

//渡されたパッドキー番号の入力状態を返す。返り値が-1なら不正
int CheckStateInput(unsigned int Handle){
    if(0<=Handle && Handle<PAD_MAX){
        return StateInput[Handle];
    }
    else{
		printfDx(_T("CheckStatePadに渡した値が不正です\n"));
        return -1;
    }
}

//キーの入力があったかを調べる
bool Check_StatetAnyInput(bool arrow){
	bool ret = false;
	int i;

	if( arrow != false ){
		//キー入力チェック（アローキーを含む）
		for( i = 0 ; i < KEY_MAX ; i++ ){
			if( StateInput[i] == 1 ){ ret = true;}
		}
	}else{
		//キー入力チェック
		for( i = 4 ; i < KEY_MAX ; i++ ){
			if( StateInput[i] == 1 ){ ret = true;}
		}
	}
	return ret;
}


//キーの入力状態をチェックする
void Calc_KeyState(){
	int i;

	//キー入力チェック
	for( i = 0 ; i < PAD_MAX ; i++ ){
		if( CheckStateInput(i) != 0 ){
			Input.key[i]++;			//キーを押している間カウントアップ
		}else{
			Input.key[i] = 0;		//キーを話すと０になる
		}
	}

}


//入力中のキー情報を取得する
void Get_InputKey(input_t input){
	int i;
	for( i = 0 ; i < KEY_MAX ; i++ ){
		Key[i] = input.key[i];
	}

}

