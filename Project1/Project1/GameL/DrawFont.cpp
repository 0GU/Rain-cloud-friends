#include <wchar.h>
#include <locale.h>
#include "DrawFont.h"
#include "DrawTexture.h"	//２Ｄ描画はDrawTextureに依存する

using namespace GameL;

#define SAFE_RELEASE(p)      { if (p) { (p)->Release();    (p)=nullptr;  }	}
#define SAFE_RESET(p)		 { if (p) { (p).reset(nullptr);				 }  }
//文字の解像度
#define FONT_SIZE	(64)
#define FONT_SHIFT	(8)

HFONT							CDrawFont::m_hFont;
HDC								CDrawFont::m_hdc;
HFONT							CDrawFont::m_oldFont;
TEXTMETRIC						CDrawFont::m_TM;
ID3D11Device*					CDrawFont::m_pDevice;
ID3D11DeviceContext*			CDrawFont::m_pDeviceContext;
D3D11_TEXTURE2D_DESC			CDrawFont::m_desc;
list< unique_ptr<CFontCharTex>>*CDrawFont::m_ListData;		//文字リスト


// CFontCharTexメソッド	---------------------------
 CFontCharTex::CFontCharTex()
{
	m_wc=L'\0';
	m_pTexture=nullptr;
	m_pTexResView=nullptr;
}

 CFontCharTex::~CFontCharTex()
{
	SAFE_RELEASE(m_pTexture) ;
	SAFE_RELEASE(m_pTexResView ); 
}
//------------------------------------------------

//コンストラクタ
void CDrawFont::Init(ID3D11Device* p_device,ID3D11DeviceContext* p_device_context)
{
	setlocale( LC_CTYPE, "jpn" );

	m_ListData= new list< unique_ptr<CFontCharTex>>;

	//使用デバイス登録
	m_pDevice		 = p_device;
	m_pDeviceContext = p_device_context;
	// フォント情報
	HFONT hFont = CreateFont(
		FONT_SIZE,
		0,0,0,0,
		FALSE,FALSE,FALSE,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		L"ＭＳ ゴシック"	//使用フォント
		);
	m_hdc = GetDC(NULL);
	m_oldFont = (HFONT)SelectObject(m_hdc, hFont);
	GetTextMetrics( m_hdc, &m_TM );

	m_hFont=hFont;
}

//クラスデリート
void CDrawFont::Delete()
{
	//リスト破棄
	ListDelete();
	// オブジェクトの開放
	DeleteObject(m_oldFont);
	DeleteObject(m_hFont);
	ReleaseDC(NULL,m_hdc);
	delete m_ListData;
}

//使用文字の事前登録メソッド
void CDrawFont:: SetStrTex(const wchar_t* init_str)
{
	//文字の初期登録
	for(unsigned int i=0 ; i< wcslen(init_str) ; i++) 
	{
		bool hit=false;
		//リストから検索
		for(auto itr = m_ListData->begin() ; itr != m_ListData->end() ; itr++ )
		{
			if((*itr)->m_wc == init_str[i] )
			{
				hit=true;
				break;
			}
		}

		//リストに文字を登録
		if(hit==false)
		{
			SetChar(init_str[i]);
		}
	}
}

//リスト文字削除メソッド
void CDrawFont::ListDelete()
{
	m_ListData->clear(); 
}

//フォントリスト追加メソッド
list< unique_ptr<CFontCharTex>>::iterator CDrawFont::SetChar(wchar_t c)
{
	//文字フォント情報
	BYTE* ptr;
	DWORD size;
	GLYPHMETRICS GM;
	CONST MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};

	//文字作成用
	UINT code = 0;
	int  s=FONT_SHIFT;

	//テクスチャ操作
	D3D11_MAPPED_SUBRESOURCE mapped;
	BYTE* pBits;

	//フォント登録用動的メモリ作成
	unique_ptr<CFontCharTex> font_tex(new CFontCharTex());
	
	//識別文字コード登録
	memcpy(&font_tex->m_wc,&c,sizeof(wchar_t));
	code=font_tex->m_wc;

	//空テクスチャ作成
	memset( &m_desc, 0, sizeof( m_desc ) );
	m_desc.MipLevels = 1;
	m_desc.ArraySize = 1;
	m_desc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_desc.SampleDesc.Count= 1;						// サンプリングは1ピクセルのみ
	m_desc.Usage     = D3D11_USAGE_DYNAMIC;			// CPU書き込み可能
	m_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// シェーダリソース
	m_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUから書き込みアクセス可
	m_desc.Height    = FONT_SIZE;					// 縦のサイズ
	m_desc.Width	 = FONT_SIZE;					// 横のサイズ
	
	// ビットマップ取得
	size = GetGlyphOutline(m_hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
	ptr  = new BYTE[size];
	GetGlyphOutline(m_hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	//テクスチャクリエイト
	m_pDevice->CreateTexture2D( &m_desc, 0, &font_tex->m_pTexture  );

	// テクスチャ情報を取得する
	D3D11_TEXTURE2D_DESC texDesc;
	font_tex->m_pTexture->GetDesc( &texDesc );

	// ShaderResourceViewの情報を作成する
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory( &srvDesc, sizeof(srvDesc) );
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	m_pDevice->CreateShaderResourceView( font_tex->m_pTexture,&srvDesc, &font_tex->m_pTexResView);

	//テクスチャロック
	m_pDeviceContext->Map(font_tex->m_pTexture,0,D3D11_MAP_WRITE_DISCARD,0,&mapped);
	pBits = (BYTE*)mapped.pData;

	// フォント情報の書き込み
	int iOfs_x = GM.gmptGlyphOrigin.x;	
	int iOfs_y = m_TM.tmAscent - GM.gmptGlyphOrigin.y;	// iOfs_x, iOfs_y : 書き出し位置(左上)
	int iBmp_w = GM.gmBlackBoxX + (4-(GM.gmBlackBoxX%4))%4;	
	int iBmp_h = GM.gmBlackBoxY;						// iBmp_w, iBmp_h : フォントビットマップの幅高
	int Level = 17;										// Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
	DWORD Alpha, Color;

	memset(pBits,0x00,sizeof(DWORD)*FONT_SIZE*FONT_SIZE);
	//FillMemory(pBits , sizeof(pBits), 0);
	for(int y=iOfs_y; y<iOfs_y+iBmp_h; y++)
	{
		for(unsigned int x=iOfs_x; x<iOfs_x+GM.gmBlackBoxX; x++)
		{
			Alpha =( 255 * ptr[ x - iOfs_x + iBmp_w * ( y - iOfs_y ) ] ) / ( Level - 1);
			Color = 0x00ffffff | (Alpha<<24);
			memcpy((BYTE*)pBits + (y<<s) + (x<<2), &Color, sizeof(DWORD));
		}
	}

	//アンロック
	m_pDeviceContext->Unmap(font_tex->m_pTexture,D3D11CalcSubresource( 0, 0, 1 ));

	//文字ビットマップデータ削除
	delete[] ptr;

	//リスト登録
	m_ListData->push_front(move(font_tex));
	
	return m_ListData->begin(); 
}


//文字列描画メソッド
void CDrawFont::StrDraw(const wchar_t* str,float x,float y,float size,float color[4])
{
	list<unique_ptr<CFontCharTex>>::iterator itr;	//登録文字検索用
	bool hit;										//登録ヒットしているかチェック

	//文字列表示
	float j=0.0f;
	for(unsigned int i=0 ; i<  wcslen(str) ; i++) 
	{
		hit=false;
		//リストから検索
		for(auto itr_i = m_ListData->begin() ; itr_i != m_ListData->end() ; itr_i++ )
		{
			if((*itr_i)->m_wc == str[i] )
			{
				hit=true;
				itr=itr_i;
				break;
			}
		}
				
		//リストに文字を登録
		if(hit==false)
		{
			itr=SetChar(str[i]);
		}
		
		//描画
		Draw::DrawStr((*itr)->m_pTexResView,x+j,y,size,color);

		//大文字か小文字で次の描画位置を変える
		char mc[3];
		int len;
		wctomb_s(&len,mc,sizeof(wchar_t),(*itr)->m_wc); 
		if( len==1)
		{
			j+=size/2.0f;
		}
		else
		{
			j+=size;
		}

	}

}