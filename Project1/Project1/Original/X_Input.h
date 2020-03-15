
#include "DxLib.h"
#include <XInput.h>

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif

/*
	�萔�錾��
*/

//�p�b�h�֌W
#define PAD_MAX		16			//16�{�^���܂ŔF��

//�L�[���͊֌W
#define KEY_MAX		16			//�L�[�A�T�C���ő吔

#define KEY_UP		3
#define KEY_LEFT	1
#define KEY_DOWN	0
#define KEY_RIGHT	2
#define KEY_NUM_4	4
#define KEY_NUM_5	5
#define KEY_NUM_6	6
#define KEY_NUM_7	7
#define KEY_NUM_8	8
#define KEY_NUM_9	9
#define KEY_NUM_10	10
#define KEY_NUM_11	11
#define KEY_NUM_12	12
#define KEY_NUM_13	13
#define KEY_NUM_14	14
#define KEY_NUM_15	15


/*
	�\���̐錾��
*/

//�L�[���͂Ɋւ���\����
typedef struct{
	int key[PAD_MAX];			//�L�[����
    int pad[PAD_MAX];			//�p�b�h����
	int rpd_key[PAD_MAX];
	int rpd_timer[PAD_MAX];
	int Hold_ArrowKey;			//�����L�[�̓��͕ێ�
	int Hold_ArrowOld;			//�����L�[�̈ȑO�̏��
	int Hold_ArrowTime;			//�����L�[�̕ێ�����
	bool Control_Flag;			//�v���C���[�R���g���[���t���O
	bool LockFlag;				//�S�L�[���b�N
}input_t;

//�R���t�B�O�Ɋւ���\����
typedef struct{
	int		DxInput[PAD_MAX];	//�ݒ�\�ȕϐ�(DxInput)
	int		Dx_Default[PAD_MAX];//������Ԃ̕ϐ�
	char*	DI_Name[PAD_MAX];	//�{�^������(DxInput)
	int		XInput[PAD_MAX];	//�ݒ�\�ȕϐ�(XInput)
	int		XI_Default[PAD_MAX];//������Ԃ̕ϐ�
	char*	XI_Name[PAD_MAX];	//�{�^������(XInput)
}configpad_t;


/*
	�ϐ��錾��
*/

GLOBAL DWORD		XInput_PadNum;		//XInput(XBox360�p�R���g���[���[)�ڑ��ԍ�
GLOBAL input_t		Input;				//�]���̃f�o�C�X�̓��͏��
GLOBAL configpad_t	ConfigPad;			//�p�b�h�{�^���\����
GLOBAL int			configpad[PAD_MAX];	//�L�[�p�b�h�錾(DirectInput)
GLOBAL int			XInputPad[PAD_MAX];	//�L�[�p�b�h�錾(XInput)
GLOBAL int			PadType;			//�ڑ����̃p�b�h�̃^�C�v  ( 1 = XInput)
GLOBAL int			Key[KEY_MAX];		//���͒��̃L�[���

//�L�[�{�[�h����уp�b�h�̓��͂��`�F�b�N����֐�
void	Init_key_state();
void	Get_HitInputStateAll();
void	Calc_KeyState();
int		CheckStateKey(unsigned char Handle);


