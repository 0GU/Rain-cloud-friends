//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRushEnemy.h"

//使用するネームスペース
using namespace GameL;

CObjRushEnemy::CObjRushEnemy(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}


//イニシャライズ
void CObjRushEnemy::Init()
{
	m_vx = 0.0f;			//移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;		//右向き0.0f  左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;		//静止フレームを初期にする

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	m_move = false;		 //true=右 false=左


	pos_init = m_px;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	stay_flag = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 75, 60, ELEMENT_ENEMY, OBJ_ENEMY, 1);

}

//アクション
void CObjRushEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//通常速度
		m_speed_power = 0.5f;
		m_ani_max_time = 4;

		//ブロック情報を持ってくる
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

		//落下
		if (m_py > 1000.0f)
		{
			;
		}


		//ブロック衝突で向き変更
		if (m_hit_left == true)
		{
			m_move = false;
		}
		if (m_hit_right == true)
		{
			m_move = true;
		}

		//方向
		if (m_move == true)
		{
			m_vx += m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (m_move == false)
		{
			m_vx -= m_speed_power;
			m_posture = 0.0f;
			m_ani_time += 1;
		}

		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		if (m_ani_frame == 4)
		{
			m_ani_frame = 0;
		}

		if (pos_init - m_px >= 400)
			m_move = true;//右向きに変更

		if (pos_init - m_px <= -400)
			m_move = false;//左向きに変更


		//摩擦
		m_vx += -(m_vx * 0.098);

		//自由落下速度
		m_vy += 9.8 / (16.0f);

		//ブロックタイプ検知用の変数がないためのダミー
		int d;
		//ブロックとの当たり判定実行
		block->BlockHit(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &d,false,75.0f,60.0f
		);

		//位置更新
		m_px += m_vx;
		m_py += m_vy;

		//HitBoxの位置の変更
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

		//落下したら消滅
		if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}

	}

}

//ドロー
void CObjRushEnemy::Draw()
{
	int AniData[4] =
	{
		1,0,2,0,
	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 215.0f;
	src.m_bottom =235.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = (75.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (75 - 75.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 60.0f + m_py + block->GetScrollY();

	//描画
	Draw::Draw(14, &src, &dst, c, 0.0f);
}
