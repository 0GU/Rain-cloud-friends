#define GLOBAL_INSTANCE
#include <windowsx.h>
#include "DxLib.h"
#include "main.h"


//�S��ʕ\���p�ϐ�
int					TemporaryHandle;
LRESULT CALLBACK MyDlgProc( HWND, UINT, WPARAM, LPARAM);
HINSTANCE			hDialog;

//���[�v�ŕK���s���R�又��
int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;//�v���Z�X�������G���[�Ȃ�-1��Ԃ�
	if(ClearDrawScreen()!=0)return -1;//��ʃN���A�������G���[�Ȃ�-1��Ԃ�
	Get_HitInputStateAll();  //���݂̃p�b�h���͏������s��

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	int i;

	hDialog = hInstance;

	// �^�C�g����ύX
	SetMainWindowText( "�Q�[���p�b�h���́@�m�F�A�v��" );

	//�c�w���C�u�����̓��샍�O
	SetOutApplicationLogValidFlag(TRUE);

	
	//----------------------------------------
	//��ʕ\�����[�h�Ɋւ��鏉������ݒ�
	//----------------------------------------	

	//�E�B���h�E���[�h�̐ݒ�
	SetGraphMode( 640 , 480, 32);
	//�E�B���h�E���[�h���f
	ChangeWindowMode( TRUE );

	//DX���C�u�����̏����� 
	if( DxLib_Init() == -1 ){ return -1;}					//���������s
	if( SetDrawScreen( DX_SCREEN_BACK )   ){ return -1;}	//����ʏ������s

	//�L�[�A�T�C���̏�����
	Init_key_state();

	while(ProcessLoop()==0){//���C�����[�v


		//=====================
		//�v�Z����
		//=====================	

		Calc_KeyState();	//�L�[�̓��͏�Ԃ��`�F�b�N����

		//=====================
		//�`�敔��
		//=====================
		DrawString( 50, 50, "�����ꂽ�{�^��", GetColor(255,255,255));
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

		ScreenFlip();		//����ʔ��f

		Sleep(100);

		//�G�X�P�[�v�����͂��ꂽ��u���C�N
		if(CheckStateKey(KEY_INPUT_ESCAPE)==1)break;


    }

    DxLib_End();//�c�w���C�u�����I������
    return 0;
}
