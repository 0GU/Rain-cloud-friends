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

//イニシャライズ
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

	title_flag = false;

	bool set_Stage[3] = { false, false ,false };
	bool set_Stage2[3] = { false, false ,false };
	bool set_Stage3[3] = { false, false ,false };
	Save::Open();

	/*for (int i = 0; i < 3; i++)
	{*/
	//perfrct
	if (((UserData*)Save::GetData())->Stage_1[0] == true)
	{
		set_Stage[0] = true;
	}
	if (((UserData*)Save::GetData())->Stage_2[0] == true)
	{
		set_Stage2[0] = true;
	}
	if (((UserData*)Save::GetData())->Stage_3[0] == true)
	{
		set_Stage3[0] = true;
	}

	//great
	if (((UserData*)Save::GetData())->Stage_1[1] == true)
	{
		set_Stage[1] = true;
	}
	if (((UserData*)Save::GetData())->Stage_2[1] == true)
	{
		set_Stage2[1] = true;
	}

	if (((UserData*)Save::GetData())->Stage_3[1] == true)
	{
		set_Stage3[1] = true;
	}

	//good
	if (((UserData*)Save::GetData())->Stage_1[2] == true)
	{
		set_Stage[2] = true;
	}
	if (((UserData*)Save::GetData())->Stage_2[2] == true)
	{
		set_Stage2[2] = true;
	}
	if (((UserData*)Save::GetData())->Stage_3[2] == true)
	{
		set_Stage3[2] = true;
	}
	//}
	//フラグを初期化
	memcpy(Clear_flag, set_Stage, sizeof(bool) * (3));
	memcpy(Clear_flag2, set_Stage2, sizeof(bool) * (3));
	memcpy(Clear_flag3, set_Stage3, sizeof(bool) * (3));
}

//アクション
void CObjStageSelect::Action()
{
	Save::Open();

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


	//ここからステージコマンド------------------(コントローラー用）
	if (Input::GetConButtons(0, GAMEPAD_DPAD_RIGHT)&& keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);
		if (stageflag == 3)
		{
			;//何もしない
		}
		else
		{
			stageflag += 1;
		}
	}

	if (Input::GetConButtons(0,GAMEPAD_DPAD_LEFT)&& keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);
		if (stageflag == 1)
		{
			;//何もしない
		}
		else
		{
			stageflag -= 1;
		}


	}

	if ( Input::GetConButtons(0, GAMEPAD_B) && keyflag == true && scroll_flag == true)
	{

		keyflag = false;
		Audio::Start(2);
		title_flag = true;
		move_flag = true;


	}
	if (Input::GetConButtons(0, GAMEPAD_A) && stageflag == 1 && keyflag == true && scroll_flag == true)//Stage1
	{
		keyflag = false;
		Audio::Stop(0);
		if (move_flag == false)//音が多重になるため黒幕が上がる前に一回だけ動かす
		{
			Audio::Start(2);
		}


		move_flag = true;
	}
	if ( Input::GetConButtons(0, GAMEPAD_A) && stageflag == 2 && keyflag == true && scroll_flag == true)//Stage2
	{
		keyflag = false;
		Audio::Stop(0);
		if (move_flag == false)
		{
			Audio::Start(2);
		}

		move_flag = true;
	}
	if (Input::GetConButtons(0, GAMEPAD_A) && stageflag == 3 && keyflag == true && scroll_flag == true)//Stage3
	{
		keyflag = false;
		Audio::Stop(0);
		if (move_flag == false)
		{
			Audio::Start(2);
		}

		move_flag = true;
	}


	//キーボード用--------------------------------------------------------------
	if (Input::GetVKey(VK_RIGHT) && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);
		if (stageflag == 3)
		{
			;//何もしない
		}
		else
		{
			stageflag += 1;
		}
	}
	if (Input::GetVKey(VK_LEFT) == true && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);
		if (stageflag == 1)
		{
			;//何もしない
		}
		else
		{
			stageflag -= 1;
		}


	}


	if (Input::GetVKey('X') == true && keyflag == true && scroll_flag == true)
	{
		
		keyflag = false;
		Audio::Start(2);
		title_flag=true;
		move_flag = true;
		
	
	}


	if (Input::GetVKey('Z') == true  && stageflag == 1 && keyflag == true && scroll_flag == true)//Stage1
	{
		keyflag = false;
		Audio::Stop(0);
		if (move_flag == false)//音が多重になるため黒幕が上がる前に一回だけ動かす
		{
			Audio::Start(2);
		}
		

		move_flag = true;
	}
	if (Input::GetVKey('Z') == true  && stageflag == 2 && keyflag == true && scroll_flag == true)//Stage2
	{
		keyflag = false;
		Audio::Stop(0);
		if (move_flag == false)
		{
			Audio::Start(2);
		}

		move_flag = true;
	}
	if (Input::GetVKey('Z') == true  && stageflag == 3 && keyflag == true && scroll_flag == true)//Stage3
	{
		keyflag = false;
		Audio::Stop(0);
		if (move_flag == false)
		{
			Audio::Start(2);
		}

		move_flag = true;
	}
	//ここまで------------------------




	if (move_flag == true)
	{
		m_y1 -= 40.0f;
	}

	if (m_y1 == 0.0f)
	{
		m_y1 = 0.0f;
		if (title_flag == true)
		{
			Scene::SetScene(new CSceneTitle);//titleシーンに移行
		}
		else
		{
			Scene::SetScene(new CSceneGameMain(stageflag));//そのステージに移行
		}
		
	}

	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false &&
		Input::GetVKey('X') == false && Input::GetVKey('Z') == false && Input::GetVKey('B') == false &&
		Input::GetConButtons(0, GAMEPAD_DPAD_RIGHT)==false && Input::GetConButtons(0, GAMEPAD_DPAD_LEFT) == false&&
		keyflag == false
		)
	{

		keyflag = true;

	}

	//

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

	dst.m_top = 630.0f;
	dst.m_left = 200.0f;
	dst.m_right = 1100.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//--------------ここから雫
	//雫（あり）
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//配列が逆
	//Stage1
	if (Clear_flag[2] == true || Clear_flag[1] == true || Clear_flag[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 120.0f;
		dst.m_right = 220.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag[1] == true || Clear_flag[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 200.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 280.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);

	}
	//Stage2
	if (Clear_flag2[2] == true || Clear_flag2[1] == true || Clear_flag2[0] == true)
	{

		dst.m_top = 560.0f;
		dst.m_left = 520.0f;
		dst.m_right = 620.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag2[1] == true || Clear_flag2[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 600.0f;
		dst.m_right = 700.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag2[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 680.0f;
		dst.m_right = 780.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	//Stage3
	if (Clear_flag3[2] == true  || Clear_flag3[1] == true || Clear_flag3[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 920.0f;
		dst.m_right = 1020.0f;
		dst.m_bottom = 620.0f;


		Draw::Draw(3, &src, &dst, c, 0.0f);
	}

	if (Clear_flag3[1] == true || Clear_flag3[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 1000.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag3[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 1080.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------------------------------------
	//雫(なし）
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	//stage1
	if (Clear_flag[2] == false && Clear_flag[1] == false && Clear_flag[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 120.0f;
		dst.m_right = 220.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);

	}
	if (Clear_flag[1] == false && Clear_flag[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 200.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	if (Clear_flag[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 280.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}

	//stage2
	if (Clear_flag2[2] == false && Clear_flag2[1] == false && Clear_flag2[0] == false)
	{

		dst.m_top = 560.0f;
		dst.m_left = 520.0f;
		dst.m_right = 620.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	if (Clear_flag2[1] == false && Clear_flag2[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 600.0f;
		dst.m_right = 700.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	if (Clear_flag2[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 680.0f;
		dst.m_right = 780.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//stage3

	if (Clear_flag3[2] == false && Clear_flag3[1] == false && Clear_flag3[0] == false)
	{

		dst.m_top = 560.0f;
		dst.m_left = 920.0f;
		dst.m_right = 1020.0f;
		dst.m_bottom = 620.0f;


		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	if (Clear_flag3[1] == false && Clear_flag3[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 1000.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	if (Clear_flag3[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 1080.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}

	//-------------------ここまで

	//黒画面
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 800.0f + m_y1;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_y1;
	Draw::Draw(2, &src, &dst, c, 0.0f);
}