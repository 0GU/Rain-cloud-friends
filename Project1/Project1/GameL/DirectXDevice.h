#pragma once
#include <Windows.h>
#include <D3D11.h> 
#include <d3dCompiler.h>

namespace GameL
{

	//DirectXDeviceの初期化・削除クラス
	typedef class CDirectXDeviec
	{
		public :
			static void ViewClear();								// 画面のクリア
			static void ViewDraw2D();								// 画面を２Dモードに切り替える
			static void ViewFlip();									// 画面スワップチェンジ
			static HRESULT APIENTRY  InitDevice(HWND hWnd,int w,int h,float* c);	// デバイス初期化メソッド
			static void ShutDown();													// デバイスシャットダウン

			static ID3D11Device*		GetDevice()		   { return m_pDevice;		  }
			static ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }

		private:

			static ID3D11Device*           m_pDevice;				// D3D11デバイス
			static ID3D11DeviceContext*    m_pDeviceContext;		// D3D11デバイスコンテキスト
			static ID3D11RasterizerState*  m_pRS;					// D3D11ラスタライザー
			static ID3D11RasterizerState*  m_pRS3D;					// D3D11ラスタライザー3D
			static ID3D11RenderTargetView* m_pRTV;					// D3D11レンダーターゲット
			static ID3D11DepthStencilView* m_pDSV;					// D3D11深度ステンシルビュー
			static D3D_FEATURE_LEVEL       m_FeatureLevel;			// D3D機能レベル
			static ID3D11BlendState*	   m_pBlendState;			// ブレンドステータス
			static IDXGIAdapter*           m_pDXGIAdapter;			// DXGIアダプター
			static IDXGIFactory*           m_pDXGIFactory;			// DXGIファクトリー
			static IDXGISwapChain*         m_pDXGISwapChain;		// DXGIスワップチェーン
			static IDXGIOutput**           m_ppDXGIOutputArray;		// DXGI出力群
			static UINT                    m_nDXGIOutputArraySize;	// DXGI出力群サイズ
			static IDXGIDevice1*		   m_pDXGIDevice;			// DXGIデバイス
			static int m_width ;
			static int m_height;
			static float* m_back_color;
	}Deviec;

};

