// 使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjGrowPlant.h"

CObjGrowPlant::CObjGrowPlant(float x, float y,int growcnt, bool flag)
{
	m_px = x;			//位置
	m_py = y;
	graphic = flag;		//true=花	false=ツタ
	count = growcnt;	//大きさ
}


void CObjGrowPlant::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;		//静止フレームを初期にする

	m_ani_max_time = 4;  //アニメーション間隔幅
	stay_flag = false;

	//当たり判定用のHitBoxを作成
	if (graphic == false)
	{
		Hits::SetHitBox(this, m_px, m_py, 64, 64 * count, ELEMENT_IVY, OBJ_PLANT, 1);
	}
	else if (graphic == true)
	{
		Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_FLOWER, OBJ_PLANT, 1);
	}
}

//アクション
void CObjGrowPlant::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{


		//ブロック情報を持ってくる
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

		//HitBoxの位置の変更
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());


	}
}

//ドロー
void CObjGrowPlant::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	if (graphic == false)
	{
		src.m_top = 128.0f;
		src.m_left = 0.0f;
		src.m_right = 128.0f;
		src.m_bottom = src.m_top + 0.0f;
	}
	else if (graphic==true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = src.m_top + 1024.0f;
	}

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//表示位置の設定
	if (graphic == false)
	{
		dst.m_top = m_py + block->GetScrollY();						
		dst.m_left = 128.0f + m_px + block->GetScroll();
		dst.m_right = -64.0f + m_px + block->GetScroll();
		dst.m_bottom = 64.0f*count + m_py + block->GetScrollY();
		Draw::Draw(10, &src, &dst, c, 0.0f);
	}
	else if (graphic==true)
	{
		dst.m_top = -32.0f+m_py + block->GetScrollY();						
		dst.m_left = -64.0f + m_px + block->GetScroll();
		dst.m_right = 128.0f + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py + block->GetScrollY();
		//描画
		Draw::Draw(20, &src, &dst, c, 0.0f);
	}
	}
	