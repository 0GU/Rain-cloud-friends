//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include"GameL/Audio.h"

#include "GameHead.h"
#include "ObjEnemy.h"

//使用するネームスペース
using namespace GameL;

CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}


//イニシャライズ
void CObjEnemy::Init()
{
	m_vx = 0.0f;			//移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;		//右向き0.0f  左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;		//静止フレームを初期にする

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅
	m_transparent = 0.0;//描画の透明度
	m_hp = 2;
	m_move = false;		 //true=右 false=左
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
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);

}

//アクション
void CObjEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//通常速度
		m_speed_power = 0.3f;
		m_ani_max_time = 4;
		
		//ブロック情報を持ってくる
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
		CHitBox* hit = Hits::GetHitBox(this);

		//落下
		if (m_py > 1000.0f)
		{
			;
		}
		
		if (m_damege_flag == false)//実験　雨に当たるとその場で停止
		{
			//一定間隔でジャンプ
		/*	if (m_hit_down == true)
			{
				m_vy -= 10.0f;
			}
			*/
			//ブロック衝突で向き変更
			if (m_hit_left == true)
			{
				m_move = false;
			}
			if (m_hit_right == true)
			{
				m_move = true;
			}
		}
		//逃走　徐々に透明化
		if (m_damege_flag == true)
		{
			
			m_transparent += 0.05;
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
		if (m_vx <= -3.0f)
		{
			m_vx = -3.0f;
		}
		if (m_vx >= 3.0f)
		{
			m_vx = 3.0f;
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
		//m_vx  *= 0.9f;
		//m_vx += -(m_vx * 0.098);
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

		//沼に落ちた状態では移動不可にする
		if (m_swanp == true)
			m_vx = 0.0f;

		//位置更新
		m_px += m_vx;
		m_py += m_vy;

		//HitBoxの位置の変更
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

		//実験　雨に当たると動作停止
		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
		{
			RainHit(&m_hp, &m_move, &m_damege_flag);
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

	}
	
}

//ドロー
void CObjEnemy::Draw()
{
	int AniData[4] =
	{
		1,0,2,0,
	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.5f,1.0f-m_transparent };
	if (c[3] <= 0.0f)
		m_escaoe_flag = true;


	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

//切り取り位置の設定
	src.m_top = 1.0f;
	src.m_left = 1.0f + AniData[m_ani_frame] * 63;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = src.m_top + 64.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = (64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (64 - 64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//描画
	Draw::Draw(9, &src, &dst, c, 0.0f);
}

//ModeChange関数
//引数1 float* x		:敵objのX位置
//引数2 float* y		:敵objのY位置
//引数3 float* hx		:主人公objのX位置
//引数4 float* hy		:主人公objのY位置
//引数5 float* pos_init	:敵objの初期位置
//引数6 bool* mode		:敵のモードの状態を返す(true=特殊状態 false=通常状態)
//引数7 bool* posture	:敵の向きを返す(true=右 false=左)
//引数8 bool  searchY	:遠距離敵用　上下の索敵範囲を広げる
//主人公と敵の位置に応じてモードの切り替えを行う関数
void CObjEnemy::ModeChange(float* x, float* y, float* hx, float* hy, float* pos_init, bool* mode, bool* posture, bool searchY)
{
	int range = 1;

	if (searchY == true)
		range = 4;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	float sl_x = block->GetScroll();
	float sl_y = block->GetScrollY();

	//主人公が一定距離内にいたら
	//1行目:左に一定距離　2行目:右に一定距離　3行目:上下に一定距離
	if (((*x + sl_x - *hx <= 400.0f && *x + sl_x - *hx > 0.0f && *posture == false) ||
		(*x + sl_x - *hx >= -400.0f && *x + sl_x - *hx < 0.0f && *posture == true)) &&
		fabs(*y + sl_y - *hy) <= 180 * range )
	{
		*mode = true;
	}

	//向き変更と解除
	if (*mode == true && *posture == false)//左向き追跡
	{
		if (*x + sl_x - *hx >= 400)//距離離れた
		{
			*mode = false;
		}
		else if (*x + sl_x - *hx <= 0)//右に回り込まれた
		{
			*posture = true;
		}
	}
	else if (*mode == true && *posture == true)//右向き追跡
	{
		if (*x + sl_x - *hx <= -400)//距離離れた
		{
			*mode = false;
		}
		else if (*x + sl_x - *hx >= 0)//左に回り込まれた
		{
			*posture = false;
		}
	}
	if (*mode == true && (*y +sl_y - *hy >= 200 * range || *y + sl_y - *hy <= -200 * range))//上下で距離離れた
	{
		*mode = false;
	}
}

//実験　雨に当たると動作停止
void CObjEnemy::RainHit(int* hp, bool* move, bool *damege)
{
	*hp -= 1;
	if (*hp <= 0)
		*damege = true;

	if (*move == true)
		*move = false;
	else
		*move = true;
}