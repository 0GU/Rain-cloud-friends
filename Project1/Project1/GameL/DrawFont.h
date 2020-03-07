#pragma once

//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

#include <memory>
#include <list>
#include <algorithm>
#include <D3D11.h> 
#include <d3dCompiler.h>

using namespace std;

namespace GameL
{

	//フォント一文字のテクスチャ情報
	class CFontCharTex
	{
		friend class CDrawFont;
		public:
			CFontCharTex();
			~CFontCharTex();
		private:
			wchar_t					  m_wc;				//使用されている文字(検索用)
			ID3D11Texture2D*		  m_pTexture;		//文字のテクスチャ情報
			ID3D11ShaderResourceView* m_pTexResView;	//テクスチャをシェーダに送る入り口
	};


	//フォント表示クラス
	typedef class CDrawFont
	{
		public:
			static void Init(ID3D11Device* p_device,ID3D11DeviceContext* p_device_context);	//初期化
			static void Delete();														//クラス削除
			static void SetStrTex(const wchar_t* init_str);									//事前予約文字リスト作成
			static void ListDelete();													//文字リスト削除
			static void StrDraw(const wchar_t* str,float x,float y,float size,float color[4]);	//文字列描画

		private:
			static list< unique_ptr<CFontCharTex>>::iterator SetChar(wchar_t c);		//フォントリスト追加メソッド
		
			static HFONT		m_hFont;
			static HDC			m_hdc;
			static HFONT		m_oldFont;
			static TEXTMETRIC	m_TM;
 		
			static ID3D11Device*		m_pDevice;
			static ID3D11DeviceContext* m_pDeviceContext;
			static D3D11_TEXTURE2D_DESC m_desc;

			//フォント情報を格納リスト
			static list< unique_ptr<CFontCharTex>>*	m_ListData;		//文字リスト
	}Font;

};