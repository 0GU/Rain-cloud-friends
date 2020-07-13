// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjClear.h"

CObjClear::CObjClear(float m_hp, float cl_hp)
{
	hero_hp = m_hp;//主人公のＨＰ取得用
	cloud_hp = cl_hp;//雲のＨＰ取得用
}

void CObjClear::Init()
{
	key_flag = true;
	move_flag = false;
	scroll_flag = false;
	m_y1 = 0.0f;
	Clear_flag[0] = false;
	Clear_flag[1] = false;
	Clear_flag[2] = false;
}

//アクション
void CObjClear::Action()
{
	/*
	//主人公から体力の情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//雲から体力の情報を持ってくる
	CObjCloud* cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
	*/

	//if(CObjStage)
	if (hero_hp >= 0.75f && cloud_hp >= 0.75f)//主人公と雲の体力が一定以上の場合
	{
		Clear_flag[0] = true;
	}
	else if (hero_hp >= 0.75f || cloud_hp >= 0.75f)//主人公か雲の体力のどちらかが一定の場合
	{
		Clear_flag[1] = true;
	}

	else //どちらも一定以下の場合
	{
		Clear_flag[2] = true;
	}
	//黒画面スクロール
	if (scroll_flag == false)
	{
		m_y1 += 40.0f;
		if (m_y1 > 800.0f)
		{
			m_y1 = 800.0f;
			scroll_flag = true;
		}
	}

	if (Input::GetVKey('Z') == true ||Input::GetConButtons(0, GAMEPAD_A) && key_flag == true)
	{
		key_flag = false;
		scroll_flag = true;
		move_flag = true;
	}

	if (move_flag == true)
	{
		m_y1 -= 50.0f;
	}

	if (m_y1 == 0.0f)
	{
		Scene::SetScene(new CSceneStageSelect);
	}

	if (Input::GetVKey('Z') == false && Input::GetConButtons(0, GAMEPAD_A)==false&&key_flag == false)
	{
		key_flag = true;
	}
}

//ドロー
void CObjClear::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//白背景(仮)
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 16.0f;
	src.m_bottom = 16.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

	//StageClear
	src.m_top = 369.0f;
	src.m_left = 0.0f;
	src.m_right = 900.0f;
	src.m_bottom = 529.0f;

	dst.m_top = 50.0f;
	dst.m_left = 200.0f;
	dst.m_right = 1100.0f;
	dst.m_bottom = 211.0f;

	Draw::Draw(1, &src, &dst, c, 0.0f);

	//Excerent
	src.m_top = 147.0f;
	src.m_left = 0.0f;
	src.m_right = 815.0f;
	src.m_bottom = 300.0f;

	dst.m_top = 320.0f;
	dst.m_left = 650.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 470.0f;

	Draw::Draw(5, &src, &dst, c, 30.0f);

	//雫（仮）ここから----------------------------------------
	//1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right =512.0f;
	src.m_bottom = 512.0f;

	dst.m_top = 300.0f;
	dst.m_bottom = 500.0f;
	if (Clear_flag[0] == true)
	{
		dst.m_left = 20.0f;
		dst.m_right = 270.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	if (Clear_flag[1] == true)
	{
		//2
		dst.m_left = 200.0f;
		dst.m_right = 450.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	if (Clear_flag[2] == true)
	{
		//3
		dst.m_left = 380.0f;
		dst.m_right = 630.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	//ここまで------------------------------------------------
	//黒画面
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 800.0f + m_y1;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_y1;
	Draw::Draw(3, &src, &dst, c, 0.0f);
}