//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include"GameL/Audio.h"
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

	m_speed_power = 0.2f;//通常速度
	m_ani_max_time = 10;  //アニメーション間隔幅

	m_move = false;		 //true=右 false=左

	m_rush = false;//通常状態で初期化
	m_rush_time = 0;

	sleep_flag=false;//デバッグ用停止フラグ

	m_transparent = 0.0;//描画の透明度
	m_hp = 2;
	m_damege_flag = false;//被弾フラグ
	m_escaoe_flag = false;//逃走フラグ


	pos_init = m_px;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	m_swanp = false;
	stay_flag = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_RUSH_ENEMY, 1);

}

//アクション
void CObjRushEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//通常速度
		if (m_rush == false)
		{
			
			m_ani_max_time = 4;
		}

		//ブロック情報を持ってくる
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
		sl_x = block->GetScroll();
		sl_y = block->GetScrollY();

		//位置の更新用に主人公の位置を持ってくる
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		
		//突進状態変化
		CObjEnemy* enemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
		
		//HITBOX情報を持ってくる
		CHitBox* hit = Hits::GetHitBox(this);
		
		//落下
		if (m_py > 1000.0f)
		{
			;
		}

		//ブロック衝突で向き変更
		if (m_hit_left == true)
			m_move = false;
		if (m_hit_right == true)
			m_move = true;

		//デバッグ用停止フラグ
		if (Input::GetVKey('P') == true)
		{
			if (sleep_flag == false)
				sleep_flag = true;
		}
		else if (Input::GetVKey('O') == true)
		{
			if (sleep_flag == true)
				sleep_flag = false;
		}

		if (sleep_flag == false)
		{

			//逃走　徐々に透明化
			if (m_damege_flag == true)
			{
				m_transparent += 0.05;
			}

			//通常移動
			if (m_move == true && m_rush_time != 60)
			{
				m_vx += m_speed_power;
				m_posture = 1.0f;
				m_ani_time += 1;
			}
			else if (m_move == false && m_rush_time != 60)
			{
				m_vx -= m_speed_power;
				m_posture = 0.0f;
				m_ani_time += 1;
			}

			

			if (m_rush_time < 60 && hero->GetHitDown() != 5)
			{
				hx = hero->GetX();
				hy = hero->GetY();
				enemy->ModeChange(&m_px, &m_py, &hx, &hy, &pos_init, &m_rush, &m_move, false);
			
			}
				

			//突進状態　1秒溜め行動のあと突進する
			if (m_rush == true && m_rush_time < 60)
			{
				m_rush_time++;
				m_vx = 0.0f;
				if (m_rush_time == 60)
					m_rush_time++;
			}
			if (m_rush_time > 60)
			{

				//主人公の位置を通過したらブレーキかける
				if ((m_px + sl_x +75 > hx+64 && m_move == true) || (m_px + sl_x < hx && m_move == false))
				{
					if ((m_vx < 7.0f && m_move == true) || (m_vx > -7.0f && m_move == false))//一定速度以下で突進終了
					{
						m_rush_time = 0;
						m_rush = false;
						m_vx = 0.0f;
						//反転させる
						if (m_move == true)
							m_move = false;
						else
							m_move = true;
					}
				}
				else if (hero->GetHitDown() != 5)
				{
					if (m_move == true)
						m_vx += m_speed_power * 3.0f;
					if (m_move == false)
						m_vx += -m_speed_power * 3.0f;//
				}
				else if (m_rush == true)
				{
					if (m_vx > 9.0f)
						m_vx = 9.0f;
					if (m_vx < -9.0f)
						m_vx = -9.0f;
				}
			}
			//ダメージ処理
			if (m_py + block->GetScrollY() < hero->GetY() + 50)
			{
				//主人公の左側に当たった場合
				if (m_px + block->GetScroll() + 32 < hero->GetX() + 44)
				{

				}
				//主人公の右側に当たった場合
				//if (Re->GetX() + pb->GetScroll() > m_px + 32)
				else
				{

				}
			}


		}
		//アニメーション進める
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		if (m_ani_frame == 4)
		{
			m_ani_frame = 0;
		}

		//初期位置から一定距離離れたら方向転換
		if (m_rush == false)
		{
			if (pos_init - m_px >= 400)
				m_move = true;//右向きに変更

			if (pos_init - m_px <= -400)
				m_move = false;//左向きに変更
		}

		//摩擦
		m_vx += -(m_vx * 0.098);

		//自由落下速度
		m_vy += 9.8 / (16.0f);

		//ブロックタイプ検知用の変数がないためのダミー
		int d;
		//ブロックとの当たり判定実行
		block->BlockHit(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &d
		);

		//実験：沼から抜ける処理
		if (hit->CheckElementHit(ELEMENT_GREEN) == true)//沼から完全に抜ける
		{
			if (m_hit_down == false)
			{
				int py = (int)(m_py / 64) * 64;
				if (py == m_py)
					m_py = py - 64;
				else
					m_py = py;
				m_vy = 0.0f;
			}
		}
		else if (hit->CheckElementHit(ELEMENT_SWANP) == true)//半分だけ抜ける
		{
			int py = (int)(m_py / 64) * 64;
			if (py + 32 == m_py)//半分だけぬけている状態
				m_vx = 0.0f;//位置を維持
			else if (py == m_py && m_swanp == true)//一度完全に沼に落ちた場合にのみ半分ぬける
			{
				m_py = py - 32;
				m_vx = 0.0f;
				m_swanp = false;
			}
			else
				m_py = py;//沼に落ちていない場合は通過させる

			m_vy = 0.0f;
		}
		else if (hit->CheckElementHit(ELEMENT_FIELD) == true && m_hit_down == false)
		{
			m_swanp = true;//沼に完全に落ちた
		}


		//位置更新
		m_px += m_vx;
		m_py += m_vy;

		//if ((m_speed_power <= 5.0f && m_speed_power >= 0.0f && m_move == true) || (m_speed_power >= -5.0f && m_speed_power < 0.0f && m_move == false))
		//	m_rush_dist += m_speed_power;

		//HitBoxの位置の変更
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

		//実験　雨に当たると動作停止
		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
		{
			enemy->RainHit(&m_hp, &m_move, &m_damege_flag);
			m_rush = false;
		}

		//落下したら消滅
		if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		//逃走終了したら消滅
		if (m_escaoe_flag == true)
		{
			Audio::Start(27);
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		m_ani_time += 0.1;
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		if (m_ani_frame == 4)
		{
			m_ani_frame = 0;
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
	float c[4] = { 1.0f,1.0f,1.0f,1.0f - m_transparent };
	if (c[3] <= 0.0f)
		m_escaoe_flag = true;

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 244;
	src.m_right = 244.0f + AniData[m_ani_frame] * 244;
	src.m_bottom =180.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = (64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (64 - 64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 74.0f + m_py + block->GetScrollY();

	//描画
	Draw::Draw(14, &src, &dst, c, 0.0f);
}
