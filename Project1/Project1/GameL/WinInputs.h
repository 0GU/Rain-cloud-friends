#pragma once
#include <Windows.h>

namespace GameL
{
	typedef class CWinInputs
	{
		public :
			static bool WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam);//ウィンドウプロジーシャーコールバック関数登録用
			static bool GetVKey(int v_key);
			static bool GetMouButtonL();
			static bool GetMouButtonR();
		
			static int GetPosX();
			static int GetPosY();

			static void Refresh();
			static void Init();
		

		private:
			static int   m_x,m_y;		//マウス座標
			static bool  m_ButtonL;		//マウスクリック
			static bool  m_ButtonR;
			static BYTE m_KeyBoard[256];//キーボード配列
	}Input;
};