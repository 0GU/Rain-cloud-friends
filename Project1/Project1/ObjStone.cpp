// 使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjStone.h"

CObjStone::CObjStone(float x, float y)
{
	m_px = x;			//位置
	m_py = y;

}



void CObjStone::Init()
{

	stay_flag = false;
	m_vx = 0;
	m_vy = 10;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	stay_flag = false;
	hit_flag = false;
	lock_flag_r = false;
	lock_flag_l = false;
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 128, 64, ELEMENT_RED, OBJ_STONE, 1);
}

//アクション
void CObjStone::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

		//ブロック情報を持ってくる
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{

		//自由落下調整　オブジェクトの揺れを防ぎつつ
		if (m_vy<0.45)
		{
			m_vy += 0.15;
		}
		//落下する際は自由落下運動を使用する
		else
		{
			m_vy += 9.8 / (16.0f);
		}
			

		//主人公と当たっている
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetX()-block->GetScroll() + 64 > m_px && 
			hero->GetX() - block->GetScroll() < m_px + 124 && fabs(hero->GetY()-block->GetScrollY() - m_py) <=0.2f)
		{
			hero->SetSthit(true);
			m_vx = hero->GetVX() ;

			//岩が押されてない時は埋まるのを防ぐため押し出す
			if (m_px > hero->GetX() - block->GetScroll() && hero->GetVX() < 0.1f)
				hero->SetX(hero->GetX() - 0.35f);//岩押し中の移動量の関係でこれが限界
			else if (m_px < hero->GetX() - block->GetScroll() && hero->GetVX() > -0.1f)
				hero->SetX(hero->GetX() + 0.35f); 
			
			if (m_vx >= 0.1f)
			{
				m_vx += 0.0f;
			}
		}
		else if(hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			hero->SetSthit(false);
		}

		//ブロックとの当たり判定実行

		block->BlockHitStone(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &m_block_type
		);
	
		if (m_hit_left==true)
		{
			hero->SetStlockL(true);
		}
		else if (m_hit_right == true)
		{
			hero->SetStlockR(true);
		}
		
		if (m_hit_up==false)
		{
			hero->SetStlockL(false);
			hero->SetStlockR(false);
		}
		//実験：沼から抜ける処理
		if (hit->CheckElementHit(ELEMENT_GREEN) == true)//沼から完全に抜ける
		{
			if (m_hit_down == false)
			{
				int py = (int)(m_py / 64) * 64;
				if (py != m_py)
					m_py = py+0.01f;
				m_vy = 0.0f;
			}
		}



		//HitBoxの位置の変更
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());


		//位置の更新
		m_px += m_vx;
		m_py += m_vy;
		m_vx = 0;

	}
}

//ドロー
void CObjStone::Draw()
{

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f ;
	src.m_right = 512.0f ;
	src.m_bottom = src.m_top + 512.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//表示位置の設定
	dst.m_top = -32.0f+m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = 160.0f + m_px + block->GetScroll();
	dst.m_right = -24.0f + m_px + block->GetScroll();
	dst.m_bottom = 72.0f + m_py + block->GetScrollY();

	//描画
	Draw::Draw(13, &src, &dst, c, 0.0f);
}