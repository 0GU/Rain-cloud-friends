#include "X_input.h"

#define XINPUT_MAX_CONTROLLERS 4			//XInput(XBox360�p�R���g���[���[)�̍ő�ڑ���
#define POV_NUMBUR 0						//�w�肷��n�b�g�X�C�b�`�̔ԍ�

DWORD				Find_XInputControler();	//XInput�p�R���g���[���̐ڑ����m�F

//DWORD				XInput_PadNum;			//XInput(XBox360�p�R���g���[���[)�ڑ��ԍ�
_XINPUT_STATE		XInput_State;			//XInput(XBox360�p�R���g���[���[)�̌��݂̏��
_XINPUT_GAMEPAD		XInput_Pad;				//XInput(XBox360�p�R���g���[���[)�̌��݂̏��
_XINPUT_KEYSTROKE	XInput_KeyStroke;		//XInput(XBox360�p�R���g���[���[)�̃L�[�X�g���[�N �f�[�^

unsigned int		stateKey[256];			//�L�[�{�[�h�̓��͏��
int					StateInput[KEY_MAX];	//�L�[�E�p�b�h�̓��͏��
int					StatePad[KEY_MAX];		//�p�b�h�̓��͏��(StatePad_D,StatePad_X)�̔�r����
int					StatePad_D[KEY_MAX];	//DirectInput�̓��͏��
int					StatePad_X[KEY_MAX];	//XInput(XBox360�p�R���g���[���[)�̓��͏��


void Init_key_state(){

	//�p�b�h�̓��͏�Ԃ�������
	memset( &StatePad  , 0, sizeof(StatePad));
	memset( &StatePad_D, 0, sizeof(StatePad_D));

	//================================================
	//�@��ʌ^�p�b�h�̏�����
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
	ConfigPad.DI_Name[KEY_NUM_4 ]	= "�P";
	ConfigPad.DI_Name[KEY_NUM_5 ]	= "�Q";
	ConfigPad.DI_Name[KEY_NUM_6 ]	= "�R";
	ConfigPad.DI_Name[KEY_NUM_7 ]	= "�S";
	ConfigPad.DI_Name[KEY_NUM_8 ]	= "�T";
	ConfigPad.DI_Name[KEY_NUM_9 ]	= "�U";
	ConfigPad.DI_Name[KEY_NUM_10]	= "�V";
	ConfigPad.DI_Name[KEY_NUM_11]	= "�W";
	ConfigPad.DI_Name[KEY_NUM_12]	= "�X";
	ConfigPad.DI_Name[KEY_NUM_13]	= "�P�O";
	ConfigPad.DI_Name[KEY_NUM_14]	= "�P�P";
	ConfigPad.DI_Name[KEY_NUM_15]	= "�P�Q";

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
	//�@XInput�Ή��p�b�h�̏�����
	//================================================

	XInput_PadNum = Find_XInputControler();	//�R���g���[���h�c�̎擾

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
	ConfigPad.XI_Name[KEY_NUM_4 ]	= "�`";
	ConfigPad.XI_Name[KEY_NUM_5 ]	= "�a";
	ConfigPad.XI_Name[KEY_NUM_6 ]	= "�w";
	ConfigPad.XI_Name[KEY_NUM_7 ]	= "�x";
	ConfigPad.XI_Name[KEY_NUM_8 ]	= "�k�s";
	ConfigPad.XI_Name[KEY_NUM_9 ]	= "�q�s";
	ConfigPad.XI_Name[KEY_NUM_10]	= "�k�R";
	ConfigPad.XI_Name[KEY_NUM_11]	= "�q�R";
	ConfigPad.XI_Name[KEY_NUM_12]	= "�k�a";
	ConfigPad.XI_Name[KEY_NUM_13]	= "�q�a";
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


//XInput�p�R���g���[���̐ڑ����m�F
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
	return ret;	//�R���g���[���h�c�l��Ԃ�

}

//�p�b�h(XInput)�̓��͏�Ԃ��擾
WORD Get_XInputPadState(DWORD PadNum){

	static DWORD dwPacketNumber_old;
	WORD wButtons = XInput_State.Gamepad.wButtons;

	XInputGetState( PadNum, &XInput_State);	
	if( XInput_State.dwPacketNumber - dwPacketNumber_old != 0 ){
		wButtons = XInput_State.Gamepad.wButtons;
	}
	dwPacketNumber_old = XInput_PadNum;	//�p�b�h�̏�Ԃ�ۑ�

	return wButtons;

}

//�w��̃L�[�������ꂽ����Ԃ�
int CheckStateKey(unsigned char Handle){
        return stateKey[Handle];
}


//�����P�ƈ����Q�̂����傫�����������P�ɑ������
int Input_A_or_B(int a, int b){
	int ret = a;
	
	if( a > b ){ ret = a;}else{ ret = b;}

	return ret;
}



//�L�[�{�[�h����уp�b�h�̓��͂��`�F�b�N����֐�
void Get_HitInputStateAll(){
	static DWORD	dwPacketNumber_old;
	static int		XInputCheckTimer = 0;
	char	KeyStateBuf[256];
	int		i;
	int		PadInput_D	= 0;
	int		PadInput_X	= 0;
	int		ArrowState	= 0;
    int		mul			= 1;

	//�L�[���͕�-----------------------------
	GetHitKeyStateAll( KeyStateBuf );
	for(int i=0;i<256;i++){
		if(KeyStateBuf[i] == 1){
			stateKey[i]++;
		}else{
			stateKey[i]=0;
		}
	}

	XInput_PadNum = Find_XInputControler();	//�w�����������R���g���[���h�c�̎擾

	//�p�b�h���͕�-----------------------------
	if( XInput_PadNum != -1 ){
		//XInput
		PadInput_X = Get_XInputPadState(XInput_PadNum);		//�p�b�h�̓��͏�Ԃ��擾
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
		PadInput_D = GetJoypadInputState( DX_INPUT_PAD1);	//�p�b�h�̓��͏�Ԃ��擾
		for(i=0;i<KEY_MAX;i++){
			if( PadInput_D & ConfigPad.DxInput[i]){
				StatePad_D[i]++;
			}else{
				StatePad_D[i] = 0;
			}
		}
		PadType = 0;
	}

	//�ǂ���̓��͂�������������
    for(i=0;i<KEY_MAX;i++){
		StatePad[i] = Input_A_or_B( StatePad_D[i ], StatePad_X[i]);
    }

		//�Q�[���p�b�h�̓���
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

//�n���ꂽ�p�b�h�L�[�ԍ��̓��͏�Ԃ�Ԃ��B�Ԃ�l��-1�Ȃ�s��
int CheckStateInput(unsigned int Handle){
    if(0<=Handle && Handle<PAD_MAX){
        return StateInput[Handle];
    }
    else{
		printfDx(_T("CheckStatePad�ɓn�����l���s���ł�\n"));
        return -1;
    }
}

//�L�[�̓��͂����������𒲂ׂ�
bool Check_StatetAnyInput(bool arrow){
	bool ret = false;
	int i;

	if( arrow != false ){
		//�L�[���̓`�F�b�N�i�A���[�L�[���܂ށj
		for( i = 0 ; i < KEY_MAX ; i++ ){
			if( StateInput[i] == 1 ){ ret = true;}
		}
	}else{
		//�L�[���̓`�F�b�N
		for( i = 4 ; i < KEY_MAX ; i++ ){
			if( StateInput[i] == 1 ){ ret = true;}
		}
	}
	return ret;
}


//�L�[�̓��͏�Ԃ��`�F�b�N����
void Calc_KeyState(){
	int i;

	//�L�[���̓`�F�b�N
	for( i = 0 ; i < PAD_MAX ; i++ ){
		if( CheckStateInput(i) != 0 ){
			Input.key[i]++;			//�L�[�������Ă���ԃJ�E���g�A�b�v
		}else{
			Input.key[i] = 0;		//�L�[��b���ƂO�ɂȂ�
		}
	}

}


//���͒��̃L�[�����擾����
void Get_InputKey(input_t input){
	int i;
	for( i = 0 ; i < KEY_MAX ; i++ ){
		Key[i] = input.key[i];
	}

}

