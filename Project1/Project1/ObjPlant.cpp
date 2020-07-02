// 使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjPlant.h"

CObjPlant::CObjPlant(float x, float y,int count)
{
	m_px = x;			//位置
	m_py = y;
	grow = count;		//成長させる大きさ

}


void CObjPlant::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;		//静止フレームを初期にする

	m_ani_max_time = 4;  //アニメーション間隔幅
	stay_flag = false;
	grow_flag = true;
	HP = 3;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_RED, OBJ_PLANT, 1);
}

//アクション
void CObjPlant::Action()
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

		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)	//雨が当たるとHP減少
		{
			HP -= 1;
		}
		if (HP <= 0&&grow_flag==true)					//HP0で成長
		{
				
					CObjGrowPlant* obj = new CObjGrowPlant(m_px,m_py-grow*64,grow,true);	//花の部分のオブジェクト作成
					Objs::InsertObj(obj, OBJ_PLANT, 10);
			
					CObjGrowPlant* objs = new CObjGrowPlant(m_px, m_py - (grow-1) * 64,grow, false);	//ツタの部分のオブジェクト作成
					Objs::InsertObj(objs, OBJ_PLANT, 10);

			grow_flag = false;
			this->SetStatus(false);//自身に削除命令を出す
			Hits::DeleteHitBox(this);//保有するHitBoxに削除する
		}
	}
}

//ドロー
void CObjPlant::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f  ;
	src.m_right = 128.0f;
	src.m_bottom = src.m_top + 128.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//表示位置の設定
	dst.m_top = m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//描画
	Draw::Draw(10, &src, &dst, c, 0.0f);
}