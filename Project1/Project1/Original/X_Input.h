
#include "DxLib.h"
#include <XInput.h>

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif

/*
	定数宣言部
*/

//パッド関係
#define PAD_MAX		16			//16ボタンまで認識

//キー入力関係
#define KEY_MAX		16			//キーアサイン最大数

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
	構造体宣言部
*/

//キー入力に関する構造体
typedef struct{
	int key[PAD_MAX];			//キー入力
    int pad[PAD_MAX];			//パッド入力
	int rpd_key[PAD_MAX];
	int rpd_timer[PAD_MAX];
	int Hold_ArrowKey;			//方向キーの入力保持
	int Hold_ArrowOld;			//方向キーの以前の状態
	int Hold_ArrowTime;			//方向キーの保持時間
	bool Control_Flag;			//プレイヤーコントロールフラグ
	bool LockFlag;				//全キーロック
}input_t;

//コンフィグに関する構造体
typedef struct{
	int		DxInput[PAD_MAX];	//設定可能な変数(DxInput)
	int		Dx_Default[PAD_MAX];//初期状態の変数
	char*	DI_Name[PAD_MAX];	//ボタン名称(DxInput)
	int		XInput[PAD_MAX];	//設定可能な変数(XInput)
	int		XI_Default[PAD_MAX];//初期状態の変数
	char*	XI_Name[PAD_MAX];	//ボタン名称(XInput)
}configpad_t;


/*
	変数宣言部
*/

GLOBAL DWORD		XInput_PadNum;		//XInput(XBox360用コントローラー)接続番号
GLOBAL input_t		Input;				//従来のデバイスの入力状態
GLOBAL configpad_t	ConfigPad;			//パッドボタン構造体
GLOBAL int			configpad[PAD_MAX];	//キーパッド宣言(DirectInput)
GLOBAL int			XInputPad[PAD_MAX];	//キーパッド宣言(XInput)
GLOBAL int			PadType;			//接続中のパッドのタイプ  ( 1 = XInput)
GLOBAL int			Key[KEY_MAX];		//入力中のキー情報

//キーボードおよびパッドの入力をチェックする関数
void	Init_key_state();
void	Get_HitInputStateAll();
void	Calc_KeyState();
int		CheckStateKey(unsigned char Handle);


