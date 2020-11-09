#include"GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include"GameL\HitBoxManager.h"
#include"GameHead.h"
#include"ObjSinEnemy.h"


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSinEnemy::CObjSinEnemy(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjSinEnemy::Init()
{
	m_r = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_charge_time = 0.0f;
	m_atk_time = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 1;		//静止フレームを初期にする

	m_ani_max_time = 4;  //アニメーション間隔幅

	m_transparent = 0.0;//描画の透明度
	m_hp = 2;
	m_damege_flag = false;//被弾フラグ
	m_escaoe_flag = false;//逃走フラグ


	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	stay_flag = false;
	m_move = false;

	m_atk_flag = false;
	m_charge_flag = false;

	sleep_flag = false;//デバッグ用停止フラグ

	pos_init = m_x;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_ENEMY, OBJ_SINENEMY, 1);
}

//アクション
void CObjSinEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
		CObjEnemy* enemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
		//弾発射角度用に主人公の位置を持ってくる
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float hx = hero->GetX();
		float hy = hero->GetY();

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
			//攻撃状態変化
			enemy->ModeChange(&m_x, &m_y, &hx, &hy, &pos_init, &m_atk_flag, &m_move, true);

			//攻撃間隔進める
			if (m_atk_flag == true && m_charge_flag == false && m_atk_time <= 360)
			{
				m_atk_time++;
			}
			//5秒間隔で発射
			if (m_atk_time >= 360)
			{
				m_atk_time = 0;
				//m_charge_flag = true;
				//弾発射
				CObjMagic* objm = new CObjMagic(m_x - 16, m_y - 16, m_move);
				Objs::InsertObj(objm, OBJ_MAGIC, 11);


			}

			//&& 間に障害物ある判定
		}

		//初期位置から一定距離離れたら方向転換
		if (m_atk_flag == false)
		{
			if (pos_init - m_x >= 400)
				m_move = true;//右向きに変更

			if (pos_init - m_x <= -400)
				m_move = false;//左向きに変更
		}
	
		//ブロック衝突で向き変更
		if (m_hit_right == true && m_atk_flag == false)
		{
			m_move = true;
		}
		if (m_hit_left == true && m_atk_flag == false)
		{
			m_move = false;
		}
		//逃走　徐々に透明化
		if (m_damege_flag == true)
		{
			m_transparent += 0.01;
		}

		//方向
		if (m_move == true)
		{
			m_vx = 2.0;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (m_move == false)
		{
			m_vx = -2.0f;
			m_posture = 0.0f;
			m_ani_time += 1;
		}


		//ブロックタイプ検知用の変数がないためのダミー
		int d;
		//ブロックとの当たり判定実行
		block->BlockHit(&m_x, &m_y, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &d
		);

		//通常時
		if (m_atk_flag == false)
		{
			//角度加算
			m_r += 1.0f;

			//360°で初期値に戻す
			if (m_r > 360.0f)
				m_r = 0.0f;

			//移動方向
			m_vy = sin(3.14 / 180 * m_r);//sinθを求めてm_vyに入れる

			//速度をつける
			m_vy *= 2.0f;

			//摩擦
			m_vx += -(m_vx * 0.098);

			//移動ベクトルを座標に加算する
			m_x += m_vx;
			m_y += m_vy;
		}

		//HitBoxの位置の変更
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_x + block->GetScroll(), m_y + block->GetScrollY());

		//実験　雨に当たると動作停止
		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
		{
			enemy->RainHit(&m_hp, &m_move, &m_damege_flag);
			m_atk_flag = false;
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
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}

	}
}
//ドロー
void CObjSinEnemy::Draw()
{
	//描画カラー情報　R=RED G=Green　B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f - m_transparent };
	if (c[3] <= 0.0f)
		m_escaoe_flag = true;

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 650.0f;
	src.m_bottom = 750.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//表示位置の設定
	dst.m_top	= 0.0f						+ m_y + block->GetScrollY();
	dst.m_left	=(64.0f * m_posture)		+ m_x + block->GetScroll();
	dst.m_right =(64 - 64.0f * m_posture)	+ m_x + block->GetScroll();
	dst.m_bottom= 64.0f						+ m_y + block->GetScrollY();

	//0番目に登録したグラフィックをsrc・dst・cの情報を元に描画
	Draw::Draw(12, &src, &dst, c, 0.0f);
}