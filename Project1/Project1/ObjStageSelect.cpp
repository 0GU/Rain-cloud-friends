//使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjStageSelect.h"
#include<Windows.h>

void CObjStageSelect::Init()
{
	//初期化
	stageflag = 1;
	keyflag = true;

	m_y1 = 0.0f;
	m_y2 = 0.0f;

	m_scroll = 0.0f;
	move_flag = false;
	scroll_flag = false;
}

//アクション
void CObjStageSelect::Action()
{

	//背景スクロール
	if (scroll_flag == false)
	{
		m_y1 += 50.0f;
		if (m_y1 > 800.0f)
		{
			m_y1 = 800.0f;
		}
	}
	

		


	if (Input::GetVKey(VK_RIGHT)==true&&keyflag==true)
	{
		keyflag = false;
		Audio::Start(1);
		if (stageflag == 3)
		{
			;//何もしない
		}
		else
		{
			stageflag+=1;
		}
	}
	 if (Input::GetVKey(VK_LEFT)==true&&keyflag==true)
	{
		keyflag = false;
		Audio::Start(1);
		if (stageflag == 1)
		{
			;//何もしない
		}
		else
		{
			stageflag-=1;
		}
		
		
	}
	

	if (Input::GetVKey('X') == true && keyflag == true)
	{
		keyflag = false;
		Audio::Start(2);
		;//titleシーンに移行
	}


	if (Input::GetVKey('Z') == true &&  stageflag == 2)
	{
		keyflag = false;
		Audio::Stop(0);
		Audio::Start(2);
		scroll_flag = true;
		move_flag = true;
	}
	if (move_flag == true)
	{
		m_y1 -= 50.0f;
	}
	if (m_y1 == 0.0f)
	{
		Scene::SetScene(new CSceneGameMain());//そのステージに移行
	}
	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false &&
		Input::GetVKey('X') == false && Input::GetVKey('Z') == false && keyflag == false)
	{
		keyflag = true;

	}



}

//ドロー
void CObjStageSelect::Draw()
{
	

	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//hoge背景1
	src.m_top = ZERO_G;
	src.m_left = ZERO_G;
	src.m_right = HD_RIGIT;
	src.m_bottom = HD_BUTTOM;

	dst.m_top = ZERO_G;
	dst.m_left = ZERO_G;
	dst.m_right = HD_RIGIT;
	dst.m_bottom = HD_BUTTOM;
	Draw::Draw(0, &src, &dst, c, 0.0f);
	
	//Stage1選択
	if (stageflag == 1)
	{
		//stage1
		src.m_right = 300.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 350.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//stage2
		src.m_left = 301.0f;
		src.m_right = 601.0f;

		dst.m_left = 500.0f;
		dst.m_right = 800.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//stage3
		dst.m_left = 900.0f;
		dst.m_right = 1200.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	//Stage2選択
	if (stageflag == 2)
	{
		
		//stage1
		src.m_top = ZERO_G;
		src.m_left = 301.0f;
		src.m_right = 601.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 350.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		// stage2
		
		src.m_left = ZERO_G;
		src.m_right = 300.0f;
	

		dst.m_top = 350.0f;
		dst.m_left = 500.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
		

		//stage3
		src.m_left = 301.0f;
		src.m_right = 601.0f;

		dst.m_left = 900.0f;
		dst.m_right = 1200.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	//Stage3選択
	if (stageflag == 3)
	{
		//stage1
		src.m_top = ZERO_G;
		src.m_left = 301.0f;
		src.m_right = 601.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 350.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//stage2
		dst.m_left = 500.0f;
		dst.m_right = 800.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//stage3
		src.m_left = ZERO_G;
		src.m_right = 300.0f;


		dst.m_left = 900.0f;
		dst.m_right = 1200.0f;

		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	
	//Stage1
	src.m_top = 321.0f;
	src.m_left = 0.0f;
	src.m_right = 301.0f;
	src.m_bottom = 421.0f;

	dst.m_top = 201.0f;
	dst.m_left = 100.0f;
	dst.m_right = 401.0f;
	dst.m_bottom = 321.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);


	//Stage2
	src.m_top = 321.0f;
	src.m_left = 302.0f;
	src.m_right = 602.0f;
	src.m_bottom = 421.0f;

	dst.m_top = 201.0f;
	dst.m_left = 500.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 321.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);


	//Stage3
	src.m_top = 321.0f;
	src.m_left = 603.0f;
	src.m_right = 903.0f;
	src.m_bottom = 421.0f;

	dst.m_top = 201.0f;
	dst.m_left = 900.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 321.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//ステージ選択
	src.m_top = 423.0f;
	src.m_left = 0.0f;
	src.m_right = 801.0f;
	src.m_bottom = 544.0f;

	dst.m_top = 50.0f;
	dst.m_left = 250.0f;
	dst.m_right = 1050.0f;
	dst.m_bottom = 171.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//下の説明文
	src.m_top = 200.0f;
	src.m_left = .0f;
	src.m_right = 800.0f;
	src.m_bottom = 320.0f;

	dst.m_top = 580.0f;
	dst.m_left = 200.0f;
	dst.m_right = 1100.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//下の説明文
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 16.0f;
	src.m_bottom = 16.0f;

	dst.m_top = 800.0f + m_y1;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_y1;
	Draw::Draw(2, &src, &dst, c, 0.0f);
}