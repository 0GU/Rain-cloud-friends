#include "SetWindow.h"
using namespace GameL;

//削除されていないメモリを出力にダンプする
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG
HWND LSetWindow:: m_hWnd;
int  LSetWindow:: m_width;
int  LSetWindow:: m_height;

//ウィンドウ作成
void LSetWindow::NewWindow(int w,int h,wchar_t* name,HINSTANCE hInstance)
{
	m_width =w;
	m_height=h;

	int width  = m_width + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	int height = m_height + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	//ウィンドウ作成
	if( !( m_hWnd = CreateWindow( name, name, 
		WS_OVERLAPPEDWINDOW & ~( WS_MAXIMIZEBOX | WS_SIZEBOX ),
		CW_USEDEFAULT, 0,  width, height, 0, 0, hInstance, 0) ) )
	{
		 return ;
	}

	ShowWindow( m_hWnd, SW_SHOW );

}

//ウィンドウ破棄
void LSetWindow::DeleteWindow()
{

	DestroyWindow(m_hWnd);	// ウィンドウを破棄し登録を解除
}