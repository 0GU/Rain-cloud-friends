#pragma once
#include <Windows.h>

namespace GameL
{
	//ゲームパットボタン定数
	static	constexpr auto GAMEPAD_DPAD_UP{ 0x0001 };
	static	constexpr auto GAMEPAD_DPAD_DOWN{ 0x0002 };
	static	constexpr auto GAMEPAD_DPAD_LEFT{ 0x0004 };
	static	constexpr auto GAMEPAD_DPAD_RIGHT{ 0x0008 };
	static	constexpr auto GAMEPAD_START{ 0x0010 };
	static	constexpr auto GAMEPAD_BACK{ 0x0020 };
	static	constexpr auto GAMEPAD_LEFT_THUMB{ 0x0040 };
	static	constexpr auto GAMEPAD_RIGHT_THUMB{ 0x0080 };
	static	constexpr auto GAMEPAD_LEFT_SHOULDER{ 0x0100 };
	static	constexpr auto GAMEPAD_RIGHT_SHOULDER{ 0x0200 };
	static	constexpr auto GAMEPAD_A{ 0x1000 };
	static	constexpr auto GAMEPAD_B{ 0x2000 };
	static	constexpr auto GAMEPAD_X{ 0x4000 };
	static	constexpr auto GAMEPAD_Y{ 0x8000 };
	typedef class CWinInputs
	{
		public :
			static bool WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam);//ウィンドウプロジーシャーコールバック関数登録用
			static bool GetVKey(int v_key);
			static bool GetMouButtonL();
			static bool GetMouButtonR();
		
			static int GetPosX();
			static int GetPosY();

			static int UpdateXControlerConnected();

			static void Refresh();
			static void Init();
		
		static	float GetConVecStickLX(int id);				//アナログL方向キー情報取得Y 戻り値(-1.0～1.0)
		static	float GetConVecStickLY(int id);				//アナログL方向キー情報取得X 戻り値(-1.0～1.0)
		static	float GetConVecStickRX(int id);				//アナログR方向キー情報取得Y 戻り値(-1.0～1.0)
		static	float GetConVecStickRY(int id);				//アナログR方向キー情報取得X 戻り値(-1.0～1.0)
		static	bool  GetConButtons(int id, int button);	//コントローラのボタン情報取得
		static	void  SetVibration(int id, int wL, int wR);	//バイブレーション設定

		private:
			static int   m_x,m_y;		//マウス座標
			static bool  m_ButtonL;		//マウスクリック
			static bool  m_ButtonR;
			static BYTE m_KeyBoard[256];//キーボード配列
	}Input;
};