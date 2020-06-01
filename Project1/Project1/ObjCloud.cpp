//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjCloud.h"

//使用するネームスペース
using namespace GameL;

CObjCloud::CObjCloud(int stage)
{
	reset = stage;
}

//イニシャライズ
void CObjCloud::Init()
{
	m_px = 100.0f;
	m_py = 100.0f;
	m_vx = 1.0f;
	m_vy = 1.0f;
}

//アクション
void CObjCloud::Action()
{
	if (Input::GetVKey('A') == true)
		m_px -= m_vx;
	if (Input::GetVKey('D')== true)
		m_px += m_vx;
	if (Input::GetVKey('W') == true)
		m_py -= m_vy;
	if (Input::GetVKey('S') == true)
		m_py += m_vy;
}

//ドロー
void CObjCloud::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;


	//表示位置の設定
	dst.m_top = m_py;
	dst.m_left = m_px;
	dst.m_right = m_px + 64.0f;
	dst.m_bottom = m_py + 64.0f;

	//描画
	Draw::Draw(4, &src, &dst, c, 0.0f);
}