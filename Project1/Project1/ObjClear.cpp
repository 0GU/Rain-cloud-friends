// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjClear.h"

CObjClear::CObjClear(float m_hp, float cl_hp,int stage)
{
	hero_hp = m_hp;//主人公のＨＰ取得用
	cloud_hp = cl_hp;//雲のＨＰ取得用
	stageselect = stage;
}

void CObjClear::Init()
{
	key_flag = true;
	move_flag = false;
	m_fade_flag = false;
	m_fade = 0.01f;
	m_fade_time = 0.03f;
	Clear_flag[0] = false;
	Clear_flag[1] = false;
	Clear_flag[2] = false;

	Save::Open();
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
	//クリア状態の管理

	if (hero_hp >= 0.5f && cloud_hp >= 0.5f)//主人公と雲の体力が一定以上の場合
	{
		Clear_flag[0] = true;
		Clear_flag[1] = true;
		Clear_flag[2] = true;
	}
    if (hero_hp >= 0.5f || cloud_hp >= 0.5f)//主人公か雲の体力のどちらかが一定の場合
	{
		Clear_flag[1] = true;
		Clear_flag[2] = true;
	}

	if(hero_hp <= 0.5f || cloud_hp <= 0.5f) //どちらも一定以下の場合
	{
		Clear_flag[2] = true;
	}
	

	if (Clear_flag[0] == true)//Perfect
	{
		switch(stageselect)
		{
		case 1:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_1[0] = true;
			break;
		case 2:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_2[0] = true;
			break;
		case 3:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_3[0] = true;
			break;
		}
	}
	if (Clear_flag[1] == true)//Great
	{
		switch (stageselect)
		{
		case 1:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_1[1] = true;
			break;
		case 2:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_2[1] = true;
			break;
		case 3:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_3[1] = true;
			break;
		}
	}
	if (Clear_flag[2] == true)//Good
	{
		switch (stageselect)
		{
		case 1:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_1[2] = true;
			break;
		case 2:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_2[2] = true;
			break;
		case 3:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_3[2] = true;
			Scene::SetScene(new CSceneEnding);
			break;
		}
	}



	//フェードイン
	if (m_fade_flag == false)
	{
		key_flag = false;

		m_fade += m_fade_time;
		if (m_fade >= 1.0f)
		{
			m_fade = 1.0f;
			m_fade_flag = true;
			key_flag = true;
		}
	}

	if (Input::GetVKey('Z') == true ||Input::GetConButtons(0, GAMEPAD_A) && key_flag == true)
	{
		key_flag = false;
		m_fade_flag = true;
		move_flag = true;
	}

	if (move_flag == true)
	{
		m_fade -= m_fade_time;
	}

	if (m_fade <= -0.0f)
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
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//白背景(仮)
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1280.0f;
	src.m_bottom = 720.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

	//Stage
	src.m_top = 438.0f;
	src.m_left = 1.0f;
	src.m_right = 450.0f;
	src.m_bottom = 579.0f;

	dst.m_top = 50.0f;
	dst.m_left = 200.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 200.0f;

	Draw::Draw(5, &src, &dst, c, 0.0f);


	//Clear
	src.m_top = 585.0f;
	src.m_left = 1.0f;
	src.m_right = 604.0f;
	src.m_bottom = 720.0f;

	dst.m_top = 50.0f;
	dst.m_left = 700.0f;
	dst.m_right = 1100.0f;
	dst.m_bottom = 200.0f;

	Draw::Draw(5, &src, &dst, c, 0.0f);

	if (Clear_flag[0] == true)
	{
		//Excerent
		src.m_top = 155.0f;
		src.m_left = 0.0f;
		src.m_right = 810.0f;
		src.m_bottom = 292.0f;

		dst.m_top = 370.0f;
		dst.m_left = 650.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 570.0f;

		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
	
	if (Clear_flag[1] == true &&Clear_flag[0]==false)
	{
		//Great
		src.m_top = 298.0f;
		src.m_left = 0.0f;
		src.m_right = 410.0f;
		src.m_bottom = 432.0f;

		dst.m_top = 370.0f;
		dst.m_left = 650.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 570.0f;

		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
	
	if (Clear_flag[2] == true && Clear_flag[1] == false && Clear_flag[0] == false)
	{
		//Good
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 510.0f;
		src.m_bottom = 149.0f;

		dst.m_top = 370.0f;
		dst.m_left = 650.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 565.0f;

		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
	

	//雫（仮）ここから----------------------------------------
	//1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right =512.0f;
	src.m_bottom = 512.0f;

	dst.m_top = 400.0f;
	dst.m_bottom = 600.0f;
	if (Clear_flag[2] == true)
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
	if (Clear_flag[0] == true)
	{
		//3
		dst.m_left = 380.0f;
		dst.m_right = 630.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	//ここまで------------------------------------------------
	//黒画面
/*	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 800.0f + m_fade;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_fade;
	Draw::Draw(3, &src, &dst, c, 0.0f);*/
}