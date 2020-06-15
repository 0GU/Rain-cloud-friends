// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjChaseEnemy.h"

void CObjChaseEnemy::Init()
{
	m_vx = 0.0f;			//移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;		//右向き0.0f  左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;		//静止フレームを初期にする

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	m_move = true;		 //true=右 false=左

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	stay_flag = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);

}

//アクション
void CObjChaseEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//落下
		if (m_py > 1000.0f)
		{
			;
		}
		//通常速度
		m_speed_power = 0.5f;
		m_ani_max_time = 4;

		//ブロック衝突で向き変更
		if (m_hit_left == true)
		{
			m_move = true;
		}
		if (m_hit_right == true)
		{
			m_move = false;
		}


		//方向
		if (m_move == false)
		{
			m_vx += m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (m_move == true)
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


		//摩擦
		m_vx += -(m_vx * 0.098);

		//自由落下速度
		m_vy += 9.8 / (16.0f);

		//ブロックタイプ検知用の変数がないためのダミー
		int d;
		//ブロックとの当たり判定実行
		CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
		pb->BlockHit(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &d
		);


		//位置の更新
		m_px += m_vx;
		m_py += m_vy;

		//ブロック情報を持ってくる
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

		//HitBoxの位置の変更
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

	}

}

//ドロー
void CObjChaseEnemy::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 0.0f;
	src.m_bottom = 0.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 0.0f;
	dst.m_bottom = 0.0f;


}