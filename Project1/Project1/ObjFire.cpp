// 使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjFire.h"

CObjFire::CObjFire(float x, float y)
{
	m_px = x;			//位置
	m_py = y;

}

void CObjFire::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;		//静止フレームを初期にする

	m_ani_max_time = 4;  //アニメーション間隔幅

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_RED, OBJ_FIRE, 1);
}

//アクション
void CObjFire::Action()
{
	m_ani_time++;
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 6)
	{
		m_ani_frame = 0;
	}

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);
}

//ドロー
void CObjFire::Draw()
{
	int AniData[6] =
	{
		0,1,2,1,0,3
	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 60.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = src.m_top + 128.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//表示位置の設定
	dst.m_top = -64.0f + m_py;						//↓描画に対してスクロールの影響を与える
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f  + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(1, &src, &dst, c, 0.0f);
}