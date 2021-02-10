// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjSand.h"
CObjSand::CObjSand(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}

void CObjSand::Init()
{
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_BLUE, OBJ_SAND, 1);
	m_hit_rain = false;//雨に当たていない
	m_fade_num = 1.0f;
}

//アクション
void CObjSand::Action()
{
	int d=0;
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CHitBox* hit = Hits::GetHitBox(this);

	//位置の更新用に主人公の位置を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());


	//実験　雨に当たると動作停止
	if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
	{
		Audio::Stop(31);
		Audio::Start(31);
		m_hit_rain = true;
	}
	//逃走　徐々に透明化
	if (m_hit_rain == true)
	{
		m_fade_num -= 0.05;
	}
	if (m_fade_num <= 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		block->DeleteSand(m_py / 64.0f, m_px / 64.0f);//プレイヤーの座標をブロック分(64px)で割ったブロックを削除
	}
}

//ドロー
void CObjSand::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade_num };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//砂ブロックの位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//表示位置の設定
	dst.m_top = m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	Draw::Draw(35, &src, &dst, c, 0);
}

//実験　雨に当たると動作停止
void CObjSand::RainHit(int* hp, bool* damege)
{
	*hp -= 1;
	if (*hp <= 0)
		*damege = true;
}