//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

CObjHero::CObjHero(int stage)
{
	reset = stage;
}

//イニシャライズ
void CObjHero::Init()
{
	m_px = 70.0f;			//位置
	m_py = 64.0f;
	m_vx = 0.0f;			//移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;		//右向き0.0f  左向き1.0f

	m_hp = 1.0f;			//体力（仮）
	m_hit_time = 0;		//ダメージ間隔

	m_ani_time = 0;
	m_ani_frame = 1;		//静止フレームを初期にする

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	hit_flag = true;
	stay_flag = false;

	m_block_type = 0;		//踏んでいるblockの種類を確認用

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	if (m_hit_time > 0)
		m_hit_time--;

	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	//落下によるゲームオーバー＆リスタート
	if (m_py > 1000.0f)
	{

		//場外に出たらリスタート
		Scene::SetScene(new CSceneGameMain(reset));
	}
	//HPが0でリスタート（仮）
	if (m_hp <= 0.0f)
	{
		Scene::SetScene(new CSceneGameMain(reset));

	}

	//ブロックとの当たり判定実行
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	pb->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
		&m_vx, &m_vy, &m_block_type
	);
	if (stay_flag == false)
	{
		//Xキー入力でジャンプ
		if (Input::GetVKey('X') == true)
		{
			if (m_hit_down == true)
			{
				m_vy = -20;
			}
		}

		//Zキー入力で速度アップ
		if (Input::GetVKey('Z') == true)
		{
			//ダッシュ時の速度
			m_speed_power = 1.1f;
			m_ani_max_time = 2;
		}
		else
		{
			//通常速度
			m_speed_power = 0.5f;
			m_ani_max_time = 4;
		}



		//キーの入力方向
		if (Input::GetVKey(VK_RIGHT) == true)
		{
			m_vx += m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}

		else if (Input::GetVKey(VK_LEFT) == true)
		{
			m_vx -= m_speed_power;
			m_posture = 0.0f;
			m_ani_time += 1;
		}
		else
		{
			m_ani_frame = 1;  //キー入力が無い場合は静止フレームにする
			m_ani_time = 0;
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

		//高速移動によるBlock判定
		bool b;
		float pxx, pyy, r;
		CObjStage* pbb = (CObjStage*)Objs::GetObj(OBJ_STAGE);

		if (pbb->GetScroll() > 0)
			pbb->SetScroll(0);

		

		//自身のHitBoxを持ってくる
		CHitBox* hit = Hits::GetHitBox(this);
		//敵と当たっているか確認
		if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
		{
			int enemynum = 1;
			EnemyHit(enemynum);
		}
		if (hit->CheckObjNameHit(OBJ_FIRE) != nullptr)
		{
			int enemynum = 2;
			EnemyHit(enemynum);
		}


		//位置の更新
		m_px += m_vx;
		m_py += m_vy;

		//HitBoxの位置の変更
		hit->SetPos(m_px, m_py);
	}

	
}

//ドロー
void CObjHero::Draw()
{
	int AniData[4] =
	{
		1,0,2,0,
	};

	//描画カラー情報
	float c[4] = { 1.0f,0.5f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f * m_posture) + m_px;
	dst.m_right = (64 - 64.0f * m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//交点
	float cc[4] = { 1.0f,0.0f,0.0f,1.0f };
	src.m_top = 0.0f;
	src.m_left = 320.0f;
	src.m_right = 320.0f + 64.0f;
	src.m_bottom = 64.0f;
	dst.m_top = py;
	dst.m_left = px;
	dst.m_right = dst.m_left + 10.0f;
	dst.m_bottom = dst.m_top + 10.0f;
	Draw::Draw(0, &src, &dst, cc, 0.0f);

}

void CObjHero::EnemyHit(int enemynum)
{
	CHitBox* hit = Hits::GetHitBox(this);
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//主人公が敵とどの角度で当たってるか確認
	HIT_DATA** hit_data = NULL;

	if (hit_flag == true)
	{
		if (enemynum == 1)
			hit_data = hit->SearchObjNameHit(OBJ_ENEMY);
		else if (enemynum == 2)
			hit_data = hit->SearchObjNameHit(OBJ_FIRE);


		hit_flag = false;

		for (int i = 0; i < hit->GetCount(); i++)
		{

			//敵の左右に当たったら
			if (hit_data[i] != NULL)
			{
				//敵の左右に当たったら
				float r = hit_data[i]->r;
				if (r < 45 && r >= 0 || r>315)
				{
					m_vx = -5.0f;//左に移動させる
					if (m_hit_time == 0)
					{
						m_hit_time = 60;
						m_hp -= 0.1f;//ダメージ
					}
				}
				if (r > 135 && r < 225)
				{
					m_vx = +5.0f;//右に移動させる
					if (m_hit_time == 0)
					{
						m_hit_time = 60;
						m_hp -= 0.1f;//ダメージ
					}
				}
				if (r >= 225 && r < 315)
				{
					//敵の移動方向を主人公の位置に加算
					if (enemynum == 1)
						m_px += ((CObjEnemy*)hit_data[i]->o)->GetVx();
					

					CObjStage* b = (CObjStage*)Objs::GetObj(OBJ_STAGE);
					//後方スクロールライン
					if (m_px < 80)
					{
						m_px = 80;
						b->SetScroll(b->GetScroll() + 5.0);
					}

					//前方スクロールライン
					if (m_px > 300)
					{
						m_px = 300;
						b->SetScroll(b->GetScroll() - 5.0);
					}

					//頭に乗せる処理
					if (m_vx < -1.0f)
					{
						//ジャンプしてる場合は下記の影響を出ないようにする
					}
					else
					{
						//主人公が敵の頭に乗ってるので、Vvecは0にして落下させない
						//また、地面に当たってる判定にする
						m_vy = 0.0f;
						m_hit_down = true;
					}
				}
			}
		}

		if (hit_flag == false)
		{
			hit_flag = true;
		}

		//位置の更新
		m_px += m_vx;
		m_py += m_vy;

		//HitBoxの位置の変更
		hit->SetPos(m_px, m_py);

	}

}
