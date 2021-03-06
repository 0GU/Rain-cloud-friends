//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL/DrawFont.h"
#include"GameL/Audio.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

CObjHero::CObjHero(int stage,float x,float y)
{
	reset = stage;
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjHero::Init()
{
	m_vx = 0.0f;			//移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f;		//右向き0.0f  左向き1.0f

	m_py_h = 0.0f;

	m_hp = 1.0f;			//体力（仮）
	m_hit_time = 0;		//ダメージ間隔

	m_ani_time = 0;
	m_ani_frame = 1;		//静止フレームを初期にする

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 3;  //アニメーション間隔幅

	m_enemynum = 0;	//接触物の種類判別用
	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	hit_flag = true;
	stay_flag = false;

	climb_flag = false;

	damageSE_flag = false;

	falldamage_flag = false;

	reset_falldamage_cacancel_flag = true;

	landing_flag = false;

	over_flag = false;

	m_block_type = 0;		//踏んでいるblockの種類を確認用


	stone_hit = false;//岩に当たっている状態を返す
	stone_wall_hit = false;//当たっている岩が壁にぶつかっているかを返す

	//コントローラー用仮変数
	m_con_x = 0.0f;
	m_con_y = 0.0f;

	m_con_flag = false;

	Audio_time = 0.0f;
	Audio_time_max = 1.0f;

	Audio_f = false;
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 40, 64, ELEMENT_PLAYER, OBJ_HERO, 1);

	//点滅処理
	hit_status=1.0f;
	hit_time_f = 0.1f;
	hit_f = false;
	keyflag = false;

	hero_stop_f=false;//主人公の待機時アニメーション判別用
	jump_f = false;//ジャンプ時アニメーション判別用
	stone_push_f = false;//岩を押してる判別

	stone_lock_r = false;//当たっている岩が右方向に移動不可かを返す
	stone_lock_l = false;//当たっている岩が左方向に移動不可かを返す

	//鍵フラグの初期化
	for (int i = 0; i < 10; i++)
	{
		Key_Pos[i] = false;
	}
}
//アクション
void CObjHero::Action()
{
	m_con_num = Input::UpdateXControlerConnected();
	if (m_hit_time > 0)
	{
		m_hit_time--;
		//点滅処理
		if (m_hit_time%2==0)//奇数
		{
			hit_status = 0.3f;
		}
		else//偶数
		{
			hit_status = 0.8f;
		}
		
	}
	else//点滅処理終了後元の透明度に戻る
	{
		hit_status = 1.0f;
	}

	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();

	//HPが0でリスタート（仮）
	if (m_hp <= 0.0f&&over_flag==false)
	{
		over_flag = true;
		m_ani_frame = 0;
		m_ani_time = 0;
		//Scene::SetScene(new CSceneGameMain(reset));
	}

	//ブロックとの当たり判定実行
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);


	//落下ダメージ処理-----------------------------------------------------------------------------------------------------------------------------
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	if (over_flag == false)
	{
		if (m_hit_down == true || hit->CheckElementHit(ELEMENT_IVY) == true)
		{
			
			if (falldamage_flag == false)
			{
				falldamage_flag = true;
				if ((m_py - m_py_h - block->GetScrollY()) / 64 >= 9 && reset_falldamage_cacancel_flag == false)
				{
					Audio::Stop(3);
					Audio::Start(4);
					m_hp -= 0.04 * (int)(m_py - m_py_h - block->GetScrollY()) / 64;
				}
			}
			reset_falldamage_cacancel_flag = false;
			m_py_h = m_py - block->GetScrollY();
		}

		if (m_hit_down == false)
		{
			falldamage_flag = false;
			landing_flag = false;
			if (m_py_h > m_py - block->GetScrollY())
			{
				m_py_h = m_py - block->GetScrollY();
			}
		}

		if (hit->CheckObjNameHit(OBJ_DOOR) != nullptr&&(Input::GetVKey(VK_UP) || Input::GetConVecStickLY(0) > 0.1f)&&m_hit_down==true)
		{
			reset_falldamage_cacancel_flag = true;
		}
		//----------------------------------------------------------------------------------------------------------------------------------------------
		//着地判定処理（効果音）
		if (m_hit_down == true)//着地すると
		{
			if (landing_flag == false)//着地フラグがfalseの場合
			{
				landing_flag = true;//着地しました
				if (landing_flag == true)//すると
				{
					Audio::Start(3);//着地効果音が再生されます
				}
				if (Audio_f == true)
				{
					Audio::Stop(3);
					Audio_f = false;
				}
			}

		}
		else
		{
			landing_flag = false;
		}
		if (stay_flag == false)
		{
			//コントローラー操作仮
			m_con_x = Input::GetConVecStickLX(0);
			m_con_y = Input::GetConVecStickLY(0);
			if (m_con_num==0 || m_con_num==1)
			{
				if (m_con_x == 0.0f )
				{
					m_con_flag = false;
				}

				if (Input::GetConButtons(0, GAMEPAD_A) == true)//Aボタンが押されると
				{
					if (m_hit_down == true)//着地している場合
					{
						//	hero_stop_f = false;
						Audio::Start(2);//ジャンプ効果音が再生
						m_vy = -9;//上がる
						m_ani_max_time = 6;//アニメーション速度を遅くする
					}
					if (m_hit_down == false)//地面から離れると
					{
						jump_f = true;//ジャンプしました
						m_ani_max_time = 4;//アニメーション速度を早くする
					}
					if (m_hit_up == true)//天井に当たった場合
					{
						Audio::Stop(2);//ジャンプの効果音を停止
					}
		
				}
				if (Input::GetConButtons(0, GAMEPAD_X) == true)//Xキーを押すと
				{
					//ダッシュ時の速度
					if (m_con_x > 0.8f)
					{
						if (Audio_time == 0.00f && m_hit_down == true)//着地中に効果音が一周する処理
						{
							if (hit->CheckObjNameHit(OBJ_SWANP) != nullptr)
								Audio::Start(30);
							else
								Audio::Start(25);
						}
						Audio_time += 0.04f;//効果音流れてますよ~
						hero_stop_f = false;
						m_con_x = 0.8f;
					}
						
					if (m_con_x < -0.8f)
					{
						if (Audio_time == 0.00f && m_hit_down == true)
						{
							if (hit->CheckObjNameHit(OBJ_SWANP) != nullptr)
								Audio::Start(30);
							else
								Audio::Start(25);
						}
						Audio_time += 0.04f;
						hero_stop_f = false;//主人公が動いています！
						m_con_x = -0.8f;

					}
						
					m_ani_max_time = 4.0f;
				}
				else
				{
					//通常速度
					if (m_con_x > 0.1f)
					{
						hero_stop_f = false;//主人公が動いています！
						m_con_x = 0.5f;
					}
					
					if (m_con_x < -0.1f)
					{
						hero_stop_f = false;//主人公が動いています！
						m_con_x = -0.5f;
					}
					m_ani_max_time = 5;
				}
				if (m_con_x > 0.0f)
				{
					if (Audio_time == 0.00f && m_hit_down==true)
					{
						if (hit->CheckObjNameHit(OBJ_SWANP) != nullptr)
							Audio::Start(30);
						else
							Audio::Start(25);
					}
					Audio_time += 0.04f;
					m_vx += m_con_x;
					m_posture = 1.0f;
					if (jump_f == false)
					{
						m_ani_time += 1;
					}
					m_con_flag = true;
				}
				if (m_con_x < 0.0f)
				{
					if (Audio_time == 0.00f && m_hit_down == true)
					{
						if (hit->CheckObjNameHit(OBJ_SWANP) != nullptr)
							Audio::Start(30);
						else
							Audio::Start(25);
					}
					Audio_time += 0.04f;
					m_vx += m_con_x;
					m_posture = 0.0f;
					if (jump_f == false)
					{
						m_ani_time += 1;
					}

					m_con_flag = true;
				}

				//昇降処理
				if (Input::GetConVecStickLY(0) > 0.0f && climb_flag == true && hit->CheckElementHit(ELEMENT_FLOWER) == true)
				{
					m_vy = 0.0f;
					jump_f = true;
				}
				else if (Input::GetConVecStickLY(0) == 0.0f && climb_flag == true && hit->CheckElementHit(ELEMENT_FLOWER) == false)
				{//操作なしの場合はその場所に留まる
					Audio::Stop(2);
					m_vy = 0.0f;
					jump_f = true;
				}
				else if (Input::GetConVecStickLY(0) > 0.1f && climb_flag == true /* && hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{
					if (Audio_time == 0.00f)
					{
						Audio::Start(12);
					}
					m_con_flag = true;
					Audio_time += 0.04f;
					m_vy = -3.0f;
					m_ani_time += 1;
					jump_f = true;
				}
				else if (Input::GetConVecStickLY(0) < -0.1f && climb_flag == true && m_hit_down == false/*&& hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{
					if (Audio_time == 0.00f)
					{
						Audio::Start(12);
					}
					m_con_flag = true;
					Audio_time += 0.04f;
					m_vy = +3.0f;
					m_ani_time += 1;
					Audio::Stop(2);
					jump_f = true;
				}
				else if (Input::GetConVecStickLY(0) < -0.1f && climb_flag == true && m_hit_down == true/*&& hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{
					m_ani_frame = 1;
					jump_f = true;
				}

			}
			if(m_con_num==5)
			{
				//Xキー入力でジャンプ
				if (Input::GetVKey('X') == true)
				{
					if (m_hit_down == true)
					{
					//	hero_stop_f = false;
						Audio::Start(2);
						m_vy = -9;
						m_ani_max_time = 4;
					}
					if (m_hit_down == false)
					{
						jump_f = true;
						m_ani_max_time = 4;
					}
				}

				//Zキー入力で速度アップ
				if (Input::GetVKey('Z') == true)
				{
					//ダッシュ時の速度
					m_speed_power = 0.8f;
					m_ani_max_time = 5;
				}
				else
				{
					//通常速度
					m_speed_power = 0.5f;
					m_ani_max_time = 10;
				}



				//キーの入力方向
				if (Input::GetVKey(VK_RIGHT) == true)
				{
					//Audio::Start(3);
					hero_stop_f = false;
					m_vx += m_speed_power;
					m_posture = 1.0f;
					if (jump_f == false)
					{
						m_ani_time += 1;
					}
					
				}

				else if (Input::GetVKey(VK_LEFT) == true)
				{
					hero_stop_f = false;
					m_vx -= m_speed_power;
					m_posture = 0.0f;

					if (jump_f == false)
					{
						m_ani_time += 1;
					}
				}




				//昇降処理
				if (Input::GetVKey(VK_UP) == true && climb_flag == true && hit->CheckElementHit(ELEMENT_FLOWER) == true)
				{
					//植物の一番上に当たっている場合は上に移動不可
					m_vy = 0.0f;
					jump_f = true;
				}
				else if (Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false && climb_flag == true && hit->CheckElementHit(ELEMENT_FLOWER) == false)
				{
					//操作なしの場合はその場所に留まる
					Audio::Stop(2);
					m_vy = 0.0f;
					jump_f = true;
				}
				else if (Input::GetVKey(VK_UP) == true && climb_flag == true /*&& hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{

					if (Audio_time == 0.00f)
					{
						Audio::Start(12);
					}

					Audio_time += 0.04f;
					m_vy = -3.0f;
					m_ani_time += 1;
					jump_f = true;
				}
				else if (Input::GetVKey(VK_DOWN) == true && climb_flag == true && m_hit_down==false/*&& hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{
					if (Audio_time == 0.00f)
					{
						Audio::Start(12);
					}
					Audio_time += 0.04f;
					m_vy = +3.0f;
					m_ani_time += 1;
					Audio::Stop(2);
					jump_f = true;
				}
				else if (Input::GetVKey(VK_DOWN) == true && climb_flag == true &&m_hit_down==true/*&& hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{

					m_ani_frame = 1;  //地面にぶつかっている際は静止フレームにする
				}
			}
			//1.
			//2.
			//3.
			if ((m_con_num != 5 && m_con_flag == false && climb_flag == false && m_con_x == 0.0f) ||
				(m_con_num != 5 && m_con_flag == false && climb_flag == true && m_con_y == 0.0f)  ||
				(m_con_num == 5 && climb_flag == false && Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false) ||
				(m_con_num == 5 && climb_flag == true  && Input::GetVKey(VK_UP)    == false && Input::GetVKey(VK_DOWN) == false))
			{
				hero_stop_f = true;
			}
			if (jump_f == true && climb_flag==false)
			{
				m_ani_frame == 0;
				m_ani_time += 1;

				if (m_ani_frame == 2 && (climb_flag==false||stone_push_f==false))
				{
					m_ani_frame = 2;
					m_ani_time = 0;
				}
			}
			//待機時の場合でかつ植物に触れていないかつ地面に着地している場合
			if (hero_stop_f == true && climb_flag == false && jump_f==false && stone_push_f==false )
			{
				m_ani_time += 1;

			}
			
			if (jump_f == true && m_hit_down == true)//ジャンプ後地面に着地した時
			{
				jump_f = false;
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
			m_vx += -(m_vx * 0.128);

			//自由落下調整　オブジェクトの揺れを防ぎつつ
			if (climb_flag == false /*|| Input::GetVKey(VK_UP) == false*/)
			{
				if (m_vy < 0.45)
				{
					m_vy += 0.4;
				}
				else
				{
					//落下する際は自由落下運動を使用する
					m_vy += 6.8 / (16.0f);
				}
			}

			//ここまでブロックとの当たり判定
			pb->BlockHit(&m_px, &m_py, true,
				&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
				&m_vx, &m_vy, &m_block_type, climb_flag, 64.0f, 64.0f
			);
			


			//高速移動によるBlock判定
			bool b;
			float pxx, pyy, r;

			if (pb->GetScroll() > 0)
				pb->SetScroll(0);


			m_enemynum = 0;//取得し続けるのを防ぐ

			
			//敵と当たっているか確認
			if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
			{
				m_enemynum = 1;
				EnemyHit(m_enemynum);
				
			}
			
			if (hit->CheckObjNameHit(OBJ_FIRE) != nullptr)
			{
				Audio_time += 0.05f;
				m_enemynum = 2;
				EnemyHit(m_enemynum);
			}

			if (hit->CheckObjNameHit(OBJ_SINENEMY) != nullptr)
			{
				m_enemynum = 3;
				EnemyHit(m_enemynum);
			}
			if (hit->CheckObjNameHit(OBJ_MAGIC) != nullptr)
			{
				m_enemynum = 4;
				EnemyHit(m_enemynum);
			}
			if (hit->CheckObjNameHit(OBJ_RUSH_ENEMY) != nullptr)
			{
				m_enemynum = 5;



				EnemyHit(m_enemynum);

			}
			//if (hit->CheckObjNameHit(OBJ_SWANP) != nullptr)
			//{
			//	m_enemynum = 6;
			//	EnemyHit(m_enemynum);
			//}
			if(m_enemynum==0||m_enemynum==6)//敵に当たっていなかったら再度SEなるようにする
			{
				damageSE_flag = false;
				
			}

			//昇降処理  一旦Input系の処理はここでは必要ない
			if (hit->CheckElementHit(ELEMENT_IVY) == true&&( (Input::GetVKey(VK_UP) == true|| Input::GetVKey(VK_DOWN)==true|| Input::GetConVecStickLY(0) != 0.0f)))	//蔓にあたっていて↑キー又は↓キーが押されたら昇降フラグをture
			{
				climb_flag = true;
			}
			else if (hit->CheckElementHit(ELEMENT_IVY) == false && hit->CheckElementHit(ELEMENT_FLOWER) == false && climb_flag == true)/* || Input::GetVKey(VK_UP) == false)*/	//昇降フラグをfalseにする処理
			{
				climb_flag = false;
			}

			//落下によるゲームオーバー＆リスタート
			if (m_py - block->GetScrollY() > 1300)
			{
				//場外に出たらリスタート
				Scene::SetScene(new CSceneOver(reset));
			}

			//ゴールブロックに触れると
			if (GetBT() == 3)
			{
				CObjCloud* cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
				CObjStageSelect* stage = (CObjStageSelect*)Objs::GetObj(OBJ_STAGE_SELECT);
				Scene::SetScene(new CSceneClear(m_hp, cloud->m_hp, reset));//HeroのHPと雲からm_hp(雲のＨＰ)とStage情報を持ってくる
			}
		

			if (hit->CheckElementHit(ELEMENT_GREEN) == true|| hit->CheckElementHit(ELEMENT_SWANP) == true||
				hit->CheckElementHit(ELEMENT_FIELD) == true)//主人公は沼には落ちない（ジャンプは不可）
			{
				if (m_hit_down == false&&m_vy>0.0f)
				{
					int py = (int)((m_py - pb->GetScrollY()) / 64) * 64;
					if (py == m_py - pb->GetScrollY())
						m_py = py + pb->GetScrollY() - 63.9f;
					else
						m_py = py + pb->GetScrollY() + 0.01f;
					m_vy = 0.0f;
					m_hit_down = true;
				}
			}


		//-ここから独自の判定------------------------------------------------------------------------------------
		//石との当たり判定------------------------------------------------------------------------------------------------------------------------------------------
		CObjStone* Stone = (CObjStone*)Objs::GetObj(OBJ_STONE);
		if (m_vy < -1.0f)
		{
			//ジャンプしてる場合は下記の影響を出ないようにする
		}
		//else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr&&Stone->GetPY() <= m_py + 64 - block->GetScrollY() && Stone->GetPY() + 32 >= m_py + 64 - block->GetScrollY())
		//{
		//	//主人公が敵の頭に乗ってるので、Vvecは0にして落下させない
		//	//また、地面に当たってる判定にする
		//	m_py = Stone->GetPY() + pb->GetScrollY() - 63;
		//	m_vy = 0.0f;
		//	m_hit_down = true;
		//}
		else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr && m_hit_down == true  && stone_hit == true )
		{
			if (stone_lock_r == true)
				if (m_vx < 0)
				{
					m_vx = 0;
					m_px += 5.5;
				}
			if (stone_lock_l == true)
				if (m_vx > 0)
				{
					m_vx = 0;
					m_px -= 5.5;
				}
			stone_push_f = true;
			m_vx /= 2;
		}
		else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr && m_hit_down == false && stone_hit == false)
		{
			//主人公が敵の頭に乗ってるので、Vvecは0にして落下させない
			//また、地面に当たってる判定にする
			int py = (int)((m_py - pb->GetScrollY()) / 64) * 64;
			if (py == m_py- pb->GetScrollY())
			{
				m_py = py + pb->GetScrollY() - 63;
			}
			else
			{
				m_py = py + pb->GetScrollY()+0.01f;
				Audio_f = true;
				m_vy = 0.0f;
			}
				
			m_hit_down = true;

		}
		else
		{
			stone_push_f = false;
		}

			//else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr &&
		//	((m_posture == 1 && Stone->GetPX_L() < m_px + 64 - block->GetScroll() && Stone->GetPX_R() > m_px + 64 - block->GetScroll()) ||
		//		m_posture == 0 && Stone->GetPX_R() > m_px - block->GetScroll() && Stone->GetPX_L() < m_px - block->GetScroll()))
		//{
		//
		//	if (Stone->Gethr()==false)
		//	{
		//		m_vx /= 2;
		//	}
		//	else if (Stone->Gethr() ==true)
		//	{
		//		m_vx = 0;
		//	}

		//}
		//-----------------------------------------------------------------------------------------------------------------------------------------------------------

		CObjTurtle* Turtle = (CObjTurtle*)Objs::GetObj(OBJ_TURTLE);
		if (m_vy < -1.0f)
		{
			//ジャンプしてる場合は下記の影響を出ないようにする
		}
		else if (hit->CheckElementHit(ELEMENT_TURTLE) == true && turtle_hit==true)
		{
			//主人公が敵の頭に乗ってるので、Vvecは0にして落下させない
			//また、地面に当たってる判定にする
			m_vy = 0.0f;
			m_hit_down = true;
		}
		else
		{
			turtle_hit = false;//どの亀とも当たっていないときにfalseにする
		}


			//位置の更新
			m_px += m_vx;
			m_py += m_vy;
			
			//後方スクロールライン
			if (m_px < 800 && m_vx < 0.0f)
			{
				if (pb->GetScroll() - m_vx < 0)
				{
					if (m_px - m_vx < 800)
					{
						m_px -= m_vx / 0.5;		//スクロールを加速させる分移動量を減らす
						pb->SetScroll(pb->GetScroll() -( m_vx*2));//通常よりスクロールを加速する
					}
					else if (m_px - m_vx >= 800)
					{
						m_px = 800;				//主人公はラインを超えないようにする
						pb->SetScroll(pb->GetScroll() - m_vx);
					}
				}
				else//一番後ろの場合　
				{
					if (m_px < 0)//主人公をステージ外に出さない
						m_px = 0;
					pb->SetScroll(0);//ステージ端以上にスクロールしない
				}
			}

			//前方スクロールライン
			else if (m_px > 400 && m_vx > 0.0f)
			{
				if (pb->GetScroll() > -5054)//ステージの一番端ではない
				{
					if (m_px - m_vx > 400)
					{
						m_px -= m_vx / 0.5;		//スクロールを加速させる分移動量を減らす
						pb->SetScroll(pb->GetScroll() - (m_vx * 2));//通常よりスクロールを加速する
					}
					else if (m_px - m_vx <= 400)
					{
						m_px = 400;				//主人公はラインを超えないようにする
						pb->SetScroll(pb->GetScroll() - m_vx);
					}
				}
				else
				{
					if (m_px >1216)//主人公をステージ外に出さない
						m_px = 1216;
					pb->SetScroll(-5054);//ステージ端以上にスクロールしない

				}
			}

			//ジャンプ中に一定以上の高さになると上方スクロール
			//一定ラインより上で横移動すると主人公の位置が一定になる、または限界値まで上方スクロール
			//y軸中央あたりより下に移動する場合は、主人公がy軸中央を維持するように下方向へスクロール、限界の場合はしない
			//

			//上方スクロールライン
			if (m_py < 200 && pb->GetScrollY() < 0 && m_vy < 0.0f)
			{
				m_py = 200;				//主人公はラインを超えないようにする
				pb->SetScrollY(pb->GetScrollY() - m_vy);	//主人公が本来動くべき分の値をm_scrollに加える
				if (pb->GetScrollY() > 0)//スクロールによって限界値を超えた場合、主人公のみ移動、スクロール固定
				{
					m_py -= pb->GetScrollY();
					pb->SetScrollY(0);
				}
			}
			//一定ライン以上で横移動したらスクロールを上にあげる
			else if (m_py < 350 && pb->GetScrollY() < 0 && fabs(m_vx) >= 0.3f&&m_vy==0.0f)
			{
				m_py += 2.0f;
				pb->SetScrollY(pb->GetScrollY() + 2.0f);
				if (pb->GetScrollY() > 0)
				{
					m_py -= pb->GetScrollY();
					pb->SetScrollY(0);
				}
			}

			//下方スクロールライン
			else if (m_py > 360&&pb->GetScrollY()>-560)
			{
				m_py = 360;			//主人公はラインを超えないようにする
				pb->SetScrollY(pb->GetScrollY() - m_vy);	//主人公が本来動くべき分の値をm_scrollに加える
				if (pb->GetScrollY() <= -560)//スクロールによって限界値を超えた場合、主人公のみ移動、スクロール固定
				{
					m_py -= (pb->GetScrollY() + 560);
					pb->SetScrollY(-560);
				}
			}

			//HitBoxの位置の変更
			hit->SetPos(m_px, m_py);
		}


	}
	else if (over_flag == true)//実験　死亡時のアニメーション
	{
		m_ani_time++;

		if (m_ani_time > m_ani_max_time * 3)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}
		if (m_ani_frame == 3 && m_ani_time >= m_ani_max_time * 3)
		{
			Scene::SetScene(new CSceneOver(reset));
		}
	}
	


	//効果音発生タイミング調整
	if (Audio_time >= Audio_time_max)
	{
		Audio_time = 0.00f;
	}
	//HitBoxの位置の変更
	hit->SetPos(m_px+24, m_py);

	if (Input::GetVKey('Q')==true)
	{
		pb->SetScroll(pb->GetScroll() - 10.0);
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
	float c[4] = { 1.0f,1.0f,1.0f,hit_status };
	float c2[4] = { 1.0f,0.0f,0.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	wchar_t str1[256];
	wchar_t str2[256];
	wchar_t str3[256];
	//表示位置の設定
	dst.m_top = -16.0f + m_py;
	dst.m_left = (84.0f * m_posture) + m_px;
	dst.m_right = (84 - 84.0f * m_posture) + m_px;
	dst.m_bottom = 74.0f + m_py;
	swprintf_s(str1, L"1P");
	Font::StrDraw(str1, m_px + 28, m_py - 45, 30, c2);
	//切り取り位置の設定
	if (over_flag == false&& hero_stop_f==false && jump_f== false&& stone_push_f==false &&(climb_flag==false||m_hit_down==true))//移動時
	{
		src.m_top = 0.0f;
		src.m_left = 32.0f + AniData[m_ani_frame] * 256;
		src.m_right = 224.0f + AniData[m_ani_frame] * 256;
		src.m_bottom = 256.0f;
		//描画
		Draw::Draw(15, &src, &dst, c, 0.0f);

	}
	else if (over_flag == true)//実験　死亡時のアニメーション描画
	{
		src.m_top = 0.0f;
		src.m_left = 1.0f + m_ani_frame * 247;
		src.m_right = 244.0f + m_ani_frame * 247;
		src.m_bottom = 245.0f;
		//描画
		Draw::Draw(17, &src, &dst, c, 0.0f);
	}
	else if (climb_flag == true)
	{
		src.m_top = 0.0f;
		src.m_left = 5.0f + m_ani_frame * 253;
		src.m_right = 257.0f + m_ani_frame * 253;
		src.m_bottom = 431.0f;
		if (m_posture == 1)
		{
			dst.m_left = m_px + 20.0f;
			dst.m_right = dst.m_left + 54.0f;
		}
		else
		{
			dst.m_left = m_px + 54.0f + 20.0f;
			dst.m_right = m_px + 20.0f;
		}
		//描画
		Draw::Draw(18, &src, &dst, c, 0.0f);

	}
	else if (over_flag == false && hero_stop_f == true && jump_f==false && stone_push_f==false (climb_flag == false || m_hit_down == true))//待機時が働いている場合
	{
		src.m_top = 0.0f;
		src.m_left = 5.0f + m_ani_frame * 253;
		src.m_right = 257.0f + m_ani_frame * 253;
		src.m_bottom = 480.0f;
		if (m_posture == 1)
		{
			dst.m_left = m_px + 40.0f + 20.0f;
			dst.m_right = m_px + 20.0f;
		}
		else
		{
			dst.m_left = m_px + 20.0f;
			dst.m_right = dst.m_left + 40.0f;

		}
		Draw::Draw(31, &src, &dst, c, 0.0f);
	}
	else if (over_flag == false && jump_f == true)//ジャンプ中
		{
		src.m_top = 0.0f;
		src.m_left = 5.0f + m_ani_frame * 253;
		src.m_right = 257.0f + m_ani_frame * 253;
		src.m_bottom = 360.0f;
		if (m_posture == 1)
		{
			dst.m_left = m_px + 64.0f + 20.0f;
			dst.m_right = m_px + 20.0f;
		}
		else
		{
			dst.m_left = m_px + 20.0f;
			dst.m_right = dst.m_left + 64.0f;

		}
		Draw::Draw(32, &src, &dst, c, 0.0f);
		}
	else if (over_flag == false && jump_f == false && stone_push_f == true)//岩を押している間
	{
		src.m_top = 0.0f;
		src.m_left = 5.0f + m_ani_frame * 260;
		src.m_right = 257.0f + m_ani_frame * 260;
		src.m_bottom = 528.0f;
		if (m_posture == 0)
		{
			dst.m_left = m_px + 15.0f;
			dst.m_right = dst.m_left + 49.0f;
		}
		else
		{
			dst.m_left = m_px + 49.0f + 15.0f;
			dst.m_right = m_px + 15.0f;
		}
		//描画
		Draw::Draw(33, &src, &dst, c, 0.0f);
	}
	//実験　岩を押しているときのアニメーション描画
	//src.m_top	= 1.0f;
	//src.m_left	= 1.0f + AniData[m_ani_frame] * 260;
	//src.m_right = 254.0f + AniData[m_ani_frame] * 255;
	//src.m_bottom= 438.0f;
	//dst.m_top	= 0.0f + m_py;
	//dst.m_left	= (64.0f * m_posture) + m_px;
	//dst.m_right = (64 - 64.0f * m_posture) + m_px;
	//dst.m_bottom= 64.0f + m_py;
	//Draw::Draw(19, &src, &dst, c, 0.0f);


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



	/*
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CObjStone* Stone = (CObjStone*)Objs::GetObj(OBJ_STONE);
	CObjCloud* Cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
	swprintf_s(str1, L"X=%f,Y=%f", m_px - block->GetScroll(),m_py-block->GetScrollY());
	Font::StrDraw(str1, 20, 20, 20, c);
	swprintf_s(str2, L"X=%f", Stone->GetPX_L());
	Font::StrDraw(str2, 20, 400, 20, c);
	swprintf_s(str3, L"X=%f", Cloud->GetX());
	Font::StrDraw(str3, 20, 300, 20, c);
	*/


}

void CObjHero::EnemyHit(int m_enemynum)
{
	CHitBox* hit = Hits::GetHitBox(this);
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//主人公が敵とどの角度で当たってるか確認
	HIT_DATA** hit_data = NULL;

	if (hit_flag == true)
	{
		if (m_enemynum == 1)
			hit_data = hit->SearchObjNameHit(OBJ_ENEMY);
		else if (m_enemynum == 2)
			hit_data = hit->SearchObjNameHit(OBJ_FIRE);
		else if (m_enemynum == 3)
			hit_data = hit->SearchObjNameHit(OBJ_SINENEMY);
		else if (m_enemynum == 4)
			hit_data = hit->SearchObjNameHit(OBJ_MAGIC);
		else if (m_enemynum == 5)
			hit_data = hit->SearchObjNameHit(OBJ_RUSH_ENEMY);
		else if (m_enemynum == 6)
			hit_data = hit->SearchObjNameHit(OBJ_SWANP);

		hit_flag = false;

		for (int i = 0; i < hit->GetCount(); i++)
		{

			//敵の左右に当たったら
			if (hit_data[i] != NULL)
			{
				//敵の左右に当たったら
				float r = hit_data[i]->r;
				if (r < 45 &&( r >= 0 || r>315)&&m_enemynum!=6)
				{
					if (m_hit_time == 0)
					{
						Audio::Start(4);
						if (m_enemynum == 2)
						{
							m_vx -=25.0f;//左に移動させる
							m_hit_time = 30;
						}
						else if (m_enemynum == 5)
						{
							m_vx -= 20.0f;
							m_vy = -5.0f;
							m_hit_time = 80;
						}
						else
						{
							m_vx -= 5.0f;//左に移動させる
							m_hit_time = 60;
						}
						
						m_hp -= 0.1f;//ダメージ
						hit_flag = false;
					}
				}
				if (r > 135 && r < 225 && m_enemynum != 6)
				{
				
					if (m_hit_time == 0)
					{
						Audio::Start(4);
						if (m_enemynum == 2)
						{
							m_vx += 25.0f;//右に移動させる
							m_hit_time = 30;
						}
						else if (m_enemynum == 5)
						{
							m_vx += 20.0f;//右に移動させる
							m_vy = -5.0f;
							m_hit_time = 80;
						}
						else
						{
							m_vx += 5.0f;//右に移動させる
							m_hit_time = 60;
						}

						m_hp -= 0.1f;//ダメージ
						hit_flag = false;
					}
				}
				if (r > 45 && r < 135 && m_enemynum != 6)
				{
					if (m_enemynum == 4)
					{
						m_hp -= 0.1;
					}
				}
				if (r >= 225 && r < 315)
				{
				 if (m_enemynum == 2)//炎だけ独立処理
					{
						if (m_hit_time == 0)
						{
							Audio::Start(4);
							m_vx -= 25.0f;//左に移動させる
							m_hit_time = 30;
							m_hp -= 0.1f;//ダメージ
							hit_flag = false;
						}
						
					}


					//頭に乗せる処理
					if (m_vy < -1.0f)
					{
						//ジャンプしてる場合は下記の影響を出ないようにする
					}
					if(m_enemynum==6)
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

		////位置の更新
//		m_px += m_vx;
//		m_py += m_vy;

		////HitBoxの位置の変更
//		hit->SetPos(m_px, m_py);

	}

}

int CObjHero::GetHitDown()
{
	if (m_hit_down == true)
		return m_enemynum;
	else
		return 0;
}


//CObjStone* Stone = (CObjStone*)Objs::GetObj(OBJ_STONE);
//if (m_vy < -1.0f)
//{
//	//ジャンプしてる場合は下記の影響を出ないようにする
//}
////else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr&&Stone->GetPY() <= m_py + 64 - block->GetScrollY() && Stone->GetPY() + 32 >= m_py + 64 - block->GetScrollY())
////{
////	//主人公が敵の頭に乗ってるので、Vvecは0にして落下させない
////	//また、地面に当たってる判定にする
////	m_py = Stone->GetPY() + pb->GetScrollY() - 63;
////	m_vy = 0.0f;
////	m_hit_down = true;
////}
//else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr && m_hit_down == false)
//{
//	//主人公が敵の頭に乗ってるので、Vvecは0にして落下させない
//	//また、地面に当たってる判定にする
//	int py = (int)((m_py - pb->GetScrollY()) / 64) * 64;
//	if (py == m_py)
//	{
//		m_py = py + pb->GetScrollY() - 64;
//	}
//	else
//	{
//		m_py = py + pb->GetScrollY();
//		Audio_f = true;
//	}
//
//
//	m_vy = 0.0f;
//	m_hit_down = true;
//
//}
//else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr && m_hit_down == true)
//{
//	if (Stone->GetlockflagR() == true)
//		if (m_vx < 0)
//		{
//			m_vx = 0;
//			m_px += 5.5;
//		}
//	if (Stone->GetlockflagL() == true)
//		if (m_vx > 0)
//		{
//			m_vx = 0;
//			m_px -= 5.5;
//		}
//	m_vx /= 2;
//}
