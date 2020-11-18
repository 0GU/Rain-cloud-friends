// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"
#include"GameL/Audio.h"

#include"GameHead.h"
#include"ObjSwanp.h"

CObjSwanp::CObjSwanp(float x, float y)
{
	m_px = x;			//位置
	m_py = y;

}

void CObjSwanp::Init()
{
	m_swanp_time = 0;
	m_hp = 3;
	m_swanp_flag = false;
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GREEN, OBJ_SWANP, 1);
}

//アクション
void CObjSwanp::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CHitBox* hit = Hits::GetHitBox(this);

	if (stay_flag == false)
	{
		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
		{
			m_swanp_flag = true;
			m_swanp_time = 300;
			//HitBoxの属性を変更
			Hits::DeleteHitBox(this);//保有するHitBoxに削除する
			Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_RED, OBJ_SWANP, 1);
		}
		if (m_swanp_flag == true)
		{
			if (m_swanp_time == 0)
			{
				m_swanp_flag = false;
				//HitBoxの属性を変更
				Hits::DeleteHitBox(this);//保有するHitBoxに削除する
				Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GREEN, OBJ_SWANP, 1);
			}
			m_swanp_time--;
		}
		//HitBoxの位置の変更
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());
	}
}

//ドロー
void CObjSwanp::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float sc[4] = { 0.8f,0.8f,0.8f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	//表示位置の設定
	dst.m_top = m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//描画
	if (m_swanp_flag == true)
		Draw::Draw(30, &src, &dst, sc, 0.0f);
	else
		Draw::Draw(30, &src, &dst, c, 0.0f);

}