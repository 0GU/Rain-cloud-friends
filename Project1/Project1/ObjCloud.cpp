//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjCloud.h"
#include "GameL/DrawFont.h"

//使用するネームスペース
using namespace GameL;

CObjCloud::CObjCloud(int stage)
{
	stage_num = stage;
}

//イニシャライズ
void CObjCloud::Init()
{
	m_px = 100.0f;
	m_py = 500.0f;
	m_vx = 5.0f;
	m_vy = 5.0f;
	
	m_hp = 2.0f;
	
	stay_flag = false;
	rain_flag = false;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	
	//コントローラー用
	
	m_con_x = 0.0f;
	m_con_y = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 1;		//静止フレームを初期にする

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 96, 96, ELEMENT_PLAYER, OBJ_CLOUD, 1);

	key_flag = false;


	Audio_time = 0.0f;
	Audio_time_max = 1.0f;
	Audio_f = false;
}

//アクション
void CObjCloud::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	CObjStage* pbb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	
	m_con_num = Input::UpdateXControlerConnected();

	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		if (m_con_num == 0)//1Pプレイ時
		{
			m_con_x = Input::GetConVecStickRX(m_con_num) * 10;
			m_con_y = Input::GetConVecStickRY(m_con_num) * -10;
			if (m_con_x > 5.0f)
			{
				if (Audio_time == 0.00f)//着地中に効果音が一周する処理
				{
					Audio::Start(26);//移動効果音
				}
				Audio_time += 0.04f;//効果音流れてますよ~
				m_con_x = 5.0f;
			}

			if (m_con_x < -5.0f)
			{
				if (Audio_time == 0.00f)//着地中に効果音が一周する処理
				{
					Audio::Start(26);//移動効果音
				}
				Audio_time += 0.04f;//効果音流れてますよ~
				m_con_x = -5.0f;
			}

			if (m_con_y > 5.0f)
			{
				if (Audio_time == 0.00f)//着地中に効果音が一周する処理
				{
					Audio::Start(26);//移動効果音
				}
				Audio_time += 0.04f;//効果音流れてますよ~
				m_con_y = 5.0f;
			}

			if (m_con_y < -5.0f)
			{
				if (Audio_time == 0.00f)//着地中に効果音が一周する処理
				{
					Audio::Start(26);//移動効果音
				}
				Audio_time += 0.04f;//効果音流れてますよ~
				m_con_y = -5.0f;
			}

			if ((Input::GetConButtons(m_con_num, GAMEPAD_B) == true) && rain_flag == true && m_hp > 0.0f)
			{
				CObjRain* objr = new CObjRain(m_px, m_py + 64);
				Objs::InsertObj(objr, OBJ_RAIN, 10);
				rain_flag = false;
				Audio::Start(5);
				if (stage_num == 1)
				{
					m_hp -= 0.05f;	//hp減少
				}
				if (stage_num == 2)
				{
					m_hp -= 0.025f;	//hp減少
				}
				if (stage_num == 3)
				{
					m_hp -= 0.05f;	//hp減少
				}
				
			}
			if ((Input::GetConButtons(m_con_num, GAMEPAD_B) == false) && rain_flag == false)
			{
				rain_flag = true;
			}
			if (Input::GetConButtons(m_con_num, GAMEPAD_Y) == true &&key_flag==true)
			{
				key_flag = false;
				Audio::Start(11);
				m_px = hero->GetX() - pbb->GetScroll()+10;
				m_py = hero->GetY() - pbb->GetScrollY() - 150;//主人公の頭上の上に雲を召喚
			}
			m_px += m_con_x;
			m_py += m_con_y;
		}
		else if (m_con_num == 1)//2Pプレイ時
		{
			m_con_x = Input::GetConVecStickLX(1) * 10;
			m_con_y = Input::GetConVecStickLY(1) * -10;
			if (m_con_x > 5.0f)
			{
				if (Audio_time == 0.00f)//着地中に効果音が一周する処理
				{
					Audio::Start(26);//移動効果音
				}
				Audio_time += 0.04f;//効果音流れてますよ~
				m_con_x = 5.0f;
			}
				
			if (m_con_x < -5.0f)
			{
				if (Audio_time == 0.00f)//着地中に効果音が一周する処理
				{
					Audio::Start(26);//移動効果音
				}
				Audio_time += 0.04f;//効果音流れてますよ~
				m_con_x = -5.0f;
			}
				
			if (m_con_y > 5.0f)
			{
				if (Audio_time == 0.00f)//着地中に効果音が一周する処理
				{
					Audio::Start(26);//移動効果音
				}
				Audio_time += 0.04f;//効果音流れてますよ~
				m_con_y = 5.0f;
			}
				
			if (m_con_y < -5.0f)
			{
				if (Audio_time == 0.00f)//着地中に効果音が一周する処理
				{
					Audio::Start(26);//移動効果音
				}
				Audio_time += 0.04f;//効果音流れてますよ~
				m_con_y = -5.0f;
			}
				

			if (( Input::GetConButtons(m_con_num, GAMEPAD_B) == true) && rain_flag == true && m_hp > 0.0f)
			{
				CObjRain* objr = new CObjRain(m_px, m_py + 64);
				Objs::InsertObj(objr, OBJ_RAIN, 10);
				rain_flag = false;
				Audio::Start(5);
				m_hp -= 0.05f;	//hp減少
			}
			if ((Input::GetConButtons(m_con_num, GAMEPAD_B) == false) && rain_flag == false)
			{
				rain_flag = true;
			}
			if (Input::GetConButtons(m_con_num, GAMEPAD_Y) == true)
			{
				m_px = hero->GetX() - pbb->GetScroll();
				m_py = hero->GetY() - pbb->GetScrollY() - 100;//主人公の頭上の上に雲を召喚
				Audio::Stop(28);
			}
			m_px += m_con_x;
			m_py += m_con_y;
		}
		else
		{
			if (Input::GetVKey('C') == true  && rain_flag == true && m_hp > 0.0f)
			{
				CObjRain* objr = new CObjRain(m_px, m_py + 64);
				Objs::InsertObj(objr, OBJ_RAIN, 10);
				rain_flag = false;
				Audio::Start(5);
				m_hp -= 0.05f;	//hp減少
			}
			if (Input::GetVKey('C') == false   && rain_flag == false)
			{
				rain_flag = true;
			}
			if (Input::GetVKey(VK_SPACE) == true &&key_flag==true)
			{
				Audio::Start(11);
				key_flag = false;
				m_px = hero->GetX() - pbb->GetScroll();
				m_py = hero->GetY() - pbb->GetScrollY() - 100;//主人公の頭上の上に雲を召喚
			}
			if (Input::GetVKey('A') == true)
				m_px -= m_vx;
			if (Input::GetVKey('D') == true)
				m_px += m_vx;
			if (Input::GetVKey('W') == true)
				m_py -= m_vy;
			if (Input::GetVKey('S') == true)
				m_py += m_vy;
		}
		
		
		if (Input::GetVKey(VK_SPACE) == false && Input::GetConButtons(m_con_num, GAMEPAD_Y)==false &&key_flag == false)
		{
			key_flag = true;
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
		if (m_px + pbb->GetScroll() >= 1280 || m_px + pbb->GetScroll() <= -100 || m_py + 96.0f + pbb->GetScrollY() <= 0)
		{
			Audio_f = true;
			if (Audio_time == 0.00f)//着地中に効果音が一周する処理
			{
				Audio::Start(28);
			}
			
		}
		if (Audio_f == true)
		{
			Audio_time += 0.005f;//効果音流れてますよ~
		}
		if (Audio_time >= Audio_time_max)
		{
			Audio_time = 0.00f;
		}
	}
	
	
	//ブロックタイプ検知用の変数がないためのダミー
	int d;
	//ブロックとの当たり判定実行
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
		&m_vx, &m_vy, &d,false,96.0f,96.0f
	);
	m_vx = 5.0f;
	m_vy = 5.0f;
	//HitBoxの位置の変更
	hit->SetPos(m_px + pbb->GetScroll(), m_py + pbb->GetScrollY());
	
	
}

//ドロー
void CObjCloud::Draw()
{
	int AniData[4] =
	{
		1,0,2,0
	};

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float c2[4] = { 0.0f,0.0f,1.0f,1.0f };
	wchar_t str1[256];
	wchar_t str2[256];
	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	CObjStage* pbb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	swprintf_s(str1, L"2P");
	Font::StrDraw(str1, m_px + 32 + pbb->GetScroll(), m_py - 32 + pbb->GetScrollY(), 30, c2);
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 218.0;
	src.m_right = 218.0f + AniData[m_ani_frame] * 218.0;
	src.m_bottom = 132.5f;

	

	//表示位置の設定
	dst.m_top = m_py + pbb->GetScrollY();
	dst.m_left = m_px + pbb->GetScroll();
	dst.m_right = m_px + 96.0f + pbb->GetScroll();
	dst.m_bottom = m_py + 96.0f + pbb->GetScrollY();

	//描画
	Draw::Draw(8, &src, &dst, c, 0.0f);
	if (m_px + pbb->GetScroll()>=1280 || m_px + pbb->GetScroll() <= -100 || m_py + 96.0f + pbb->GetScrollY() <= 0)
	{
		if (Audio_time == 0.00f)//着地中に効果音が一周する処理
		{
			Audio::Start(28);
		}	
		Audio_time += 0.005f;//効果音流れてますよ~
		
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 150.0f;

		//表示位置の設定
		dst.m_top = 200.0f;
		dst.m_left = 300.0f;
		dst.m_right = 1000.0f;
		dst.m_bottom = 400.0f;
		//描画
		Draw::Draw(38, &src, &dst, c, 0.0f);
	}
}