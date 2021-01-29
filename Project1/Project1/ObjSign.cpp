// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjSign.h"
#include "GameL/DrawFont.h"

CObjSign::CObjSign(float x, float y,int i)
{
	m_px = x;			//位置
	m_py = y;
	sign_num = i;
}
void CObjSign::Init()
{
	m_hit_f = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ITEM, OBJ_SIGN, 1);

}

//アクション
void CObjSign::Action()
{
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());
	//看板
	CObjHero* h = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_hit_f = true;
	}
	else
	{
		m_hit_f = false;
	}
	
}

//ドロー
void CObjSign::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	dst.m_top = m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();
	//描画
	Draw::Draw(34, &src, &dst, c, 0.0f);
	wchar_t str[256];
	if (m_hit_f == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 500.0f;
		src.m_bottom = 300.0f;
		dst.m_top =125.0f;						//↓描画に対してスクロールの影響を与える
		dst.m_left =50.0f;
		dst.m_right = 550.0f;
		dst.m_bottom = 425.0f;
		Draw::Draw(35+sign_num, &src, &dst, c, 0.0f);
	}
}