#pragma once

//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

#include <memory>
#include <vector>
#include <algorithm>
#include <D3D11.h> 
#include <d3dCompiler.h>


using namespace std;

namespace GameL
{
	//テクスチャイメージサイズ　８乗ｵﾝﾘ-設定
	enum TEX_SIZE
	{
		TEX_SIZE_64   =	  64,
		TEX_SIZE_128  =	 128,
		TEX_SIZE_256  =	 256,
		TEX_SIZE_512  =	 512,
		TEX_SIZE_1024 =	1024,
		TEX_SIZE_2048 = 2048,
		TEX_SIZE_4096 = 4096,
	};

	//２Ｄ描画専用RECTのFLOAT型
	struct RECT_F
	{
		float m_top;
		float m_left;
		float m_right;
		float m_bottom;
	};

	//テクスチャ保存用クラス
	class C_TEX_DATA
	{
		public :
			C_TEX_DATA();
			~C_TEX_DATA();

			ID3D11ShaderResourceView** GetTexData();
			float	GetTexSizeH();
			float	GetTexSizeW();
			void SetTexData(ID3D11ShaderResourceView* tex);
			void SetTexSize(float  size_w,float size_h);
		private:
			ID3D11ShaderResourceView* m_pSRV;
			float 	m_tex_size_w;
			float	m_tex_size_h;
	};

	//テクスチャ読み込み・表示・削除クラス
	typedef class CDrawTexture
	{
		public :
			//描画用オブジェクト破棄
			static void DeleteDrawTexture();
			static void InitDraw(ID3D11Device* p_device,ID3D11DeviceContext* p_device_context,int w,int h,int img_max);	//初期化
			static void LoadImage(const wchar_t* name,int id,TEX_SIZE hw);			//グラフィック読み込み　サイズは定数で指定
			static void DeleteImage();											//グラフィック破棄
			static void Draw(int id,RECT_F* src,RECT_F* dst,float col[4],float r); //登録テクスチャ描画
			static void DrawStr(ID3D11ShaderResourceView* ptex_res_view,float x,float y,float size,float col[4]);//文字描画
			static void DrawHitBox(float x,float y,float h,float w,float col[4]);//当たり判定描画

		private:
			static void Set2DDraw();	//２D使用設定

			//デバイス
			static ID3D11DeviceContext* m_pDeviceContext;
			static ID3D11Device*		m_pDevice; 

			//テクスチャ情報
			static vector<shared_ptr<C_TEX_DATA>> vec_tex_data;

			//ウィンドウ情報
			static int m_width ;
			static int m_height; 

			//取得イメージ最大数
			static int m_img_max;

			//シェーダ関係
			static ID3D11VertexShader* m_pVertexShader;		//バーテックスシェーダー
			static ID3D11PixelShader*  m_pPixelShader;		//ピクセルシェーダー
			static ID3D11SamplerState* m_pSampleLinear;		//テクスチャーサンプラー
			static ID3D11InputLayout*  m_pVertexLayout;		//頂点入力レイアウト
			//バッファ
			static ID3D11Buffer* m_pVertexBuffer;			//２Ｄポリゴン用バーティクスバッファ
			static ID3D11Buffer* m_pConstantBuffer;			//アプリ←→シェーダー架け橋 コンスタントバッファ
			static ID3D11Buffer* m_pIndexBuffer;			//インデックスバッファ
	}Draw;

};