//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjTurtle.h"

//使用するネームスペース
using namespace GameL;

CObjTurtle::CObjTurtle(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}


//イニシャライズ
void CObjTurtle::Init()
{
	m_vx = 0.0f;			//移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;		//右向き0.0f  左向き1.0f

	m_ani_time = 0;
	m_ani_frame = 1;		//静止フレームを初期にする

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 10;  //アニメーション間隔幅
	m_transparent = 0.0;//描画の透明度
	m_hp = 2;
	m_move = true;		 //true=右 false=左
	m_damege_flag = false;//被弾フラグ
	m_escaoe_flag = false;//逃走フラグ
	m_block_type = 0;		//踏んでいるblockの種類を確認用
	m_swanp = false;
	pos_init = m_px;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	stay_flag = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_TURTLE, 1);

}

//アクション
void CObjTurtle::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//通常速度
		m_speed_power = 0.1f;
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



		//方向　デバッグのため移動停止中
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

		//摩擦
		m_vx += -(m_vx * 0.098);

		//自由落下速度
		m_vy += 9.8 / (16.0f);

		//ブロックとの当たり判定実行
		block->BlockHit(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &m_block_type
		);



		//沼との判定--------------------------
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
					if (hit->GetStatus()->e==ELEMENT_TURTLE)
				{
					//HitBoxの属性を　通常状態　へ変更　乗れなくする
					Hits::DeleteHitBox(this);//保有するHitBoxに削除する
					Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_TURTLE, 1);
				}
	}
		else if (hit->CheckElementHit(ELEMENT_SWANP) == true)//半分だけ抜ける
		{
			int py = (int)(m_py / 64) * 64;
			if (py + 32 == (int)m_py)//半分だけぬけている状態
				m_vx = 0.0f;//位置を維持
			else if (py == m_py&&m_swanp==true)//一度完全に沼に落ちた場合にのみ半分ぬける
			{
				m_py = py - 32;
				m_vx = 0.0f;
				m_swanp = false;
				//HitBoxの属性を　ぬかるみ状態　へ変更　主人公が上に乗れるようにする
				Hits::DeleteHitBox(this);//保有するHitBoxに削除する
				Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_TURTLE, OBJ_TURTLE, 1);
			}
			else
			{
				m_py = py;//沼に落ちていない場合は通過させる
			}
			m_vy = 0.0f;
		}
		else if (hit->CheckElementHit(ELEMENT_FIELD) == true/*&&m_hit_down==false*/)
		{
			m_swanp = true;//沼に完全に落ちた
		}

		//沼に落ちた状態では移動不可にする
		if (m_swanp == true&&m_hit_down==true)
			m_vx = 0.0f;

		//-----------------------------------------------

		//主人公との判定---------
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		
		//亀が半分埋まっている時のみ当たり判定を取る
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && hit->GetStatus()->e == ELEMENT_TURTLE &&
			m_py <= hero->GetY() - block->GetScrollY()+64 && m_py + 32 >= hero->GetY() + 64 - block->GetScrollY())
		{
			hero->SetX(hero->GetX() + m_vx);
			hero->SetY(m_py + block->GetScrollY() - 63);
			hero->SetTurhit(true);//当たっている状態を返す
		}
		//-------------------------

		//位置更新
		m_px += m_vx;
		m_py += m_vy;

		//HitBoxの位置の変更
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

		//落下したら消滅
		if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
		{
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
void CObjTurtle::Draw()
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
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 256;
	src.m_right = 256.0f + AniData[m_ani_frame] * 256;
	src.m_bottom = 155.0f;
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//表示位置の設定
	dst.m_top = 0.0f + m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = (72.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (72 - 64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 120.0f + m_py + block->GetScrollY();

	//描画
	Draw::Draw(36, &src, &dst, c, 0.0f);
}