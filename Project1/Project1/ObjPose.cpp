// 使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include"GameL/Audio.h"

#include"GameHead.h"
#include"ObjPose.h"

CObjPose::CObjPose(float x, float y, int stage)
{
	m_px = x;			//位置
	m_py = y;

	stage_num = stage;
}

//イニシャライズ
void CObjPose::Init()
{
	delete_flag = false;
	stay_flag = false;
	select_num = 1;
	keyflag = true;

	m_ani_time = 0.0f;
	m_ani_max = 8.0f;
}

//アクション
void CObjPose::Action()
{
	//コントローラー用---------------------------------------
	if (Input::GetConButtons(0, GAMEPAD_START)&&stay_flag==false)
	{
		Audio::Start(20);
		stay_flag = true;
		Audio::Volume(-0.8, 0);
		Audio::Volume(-0.8, 1);
		Audio::Volume(-0.8, 23);
		Audio::Volume(-0.8, 24);
	}
	if (stay_flag == true)
	{

		if ((Input::GetConButtons(0, GAMEPAD_DPAD_UP) || Input::GetConVecStickLY(0) > 0.1f) && keyflag == true && select_num > 1 && select_num <= 3)
		{
			Audio::Start(21);
			keyflag = false;
			select_num--;
		}
		if ((Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) || Input::GetConVecStickLY(0) < -0.1f) == true && keyflag == true && select_num >= 1 && select_num < 3)
		{
			Audio::Start(21);
			keyflag = false;
			select_num++;
		}
		if (Input::GetConButtons(0, GAMEPAD_A) && keyflag == true == true)
		{
			Audio::Start(22);
			keyflag = false;
			switch (select_num)
			{
			case 1:
				Audio::Start(20);
				Audio::Volume(0.8, 0);
				Audio::Volume(0.8, 1);
				Audio::Volume(0.8, 23);
				Audio::Volume(0.8, 24);
				stay_flag = false;
				break;
			case 2:
				Scene::SetScene(new CSceneGameMain(stage_num));
				break;
			case 3:
				Scene::SetScene(new CSceneStageSelect);
				break;
			}

		}
	}

	//キーボード用-------------------------------------------
	if (Input::GetVKey('M') == true&&stay_flag==false)
	{
		Audio::Start(20);
		stay_flag = true;
		Audio::Volume(-0.8, 0);
		Audio::Volume(-0.8, 1);
		Audio::Volume(-0.8, 23);
		Audio::Volume(-0.8, 24);
		
	}
	if (stay_flag == true)
	{
		if (Input::GetVKey('Q') == true)
		{
			stay_flag = false;
		}
		if (Input::GetVKey(VK_UP) == true &&keyflag==true && select_num>1 &&select_num<=3)
		{
			Audio::Start(21);
			keyflag = false;
			select_num--;
		}
		if (Input::GetVKey(VK_DOWN) == true && keyflag == true &&select_num>=1 && select_num<3)
		{
			Audio::Start(21);
			keyflag = false;
			select_num++;
		}
		if ((Input::GetVKey(VK_RETURN) || Input::GetVKey ('Z')) && keyflag == true )
		{
			switch (select_num)
			{
			case 1:
				Audio::Start(20);
				Audio::Volume(0.8, 0);
				Audio::Volume(0.8, 1);
				Audio::Volume(0.8, 23);
				Audio::Volume(0.8, 24);

				stay_flag = false;
				break;
			case 2:
				Scene::SetScene(new CSceneGameMain(stage_num));
				break;
			case 3:
				Scene::SetScene(new CSceneStageSelect);
				break;
			}

		}
	}


	if (Input::GetVKey(VK_DOWN) == false && Input::GetVKey(VK_UP) == false &&
		Input::GetVKey('Z') == false && keyflag == false && Input::GetConButtons(0, GAMEPAD_A) == false &&
		Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) == false && Input::GetConButtons(0, GAMEPAD_DPAD_UP) == false &&
		Input::GetConVecStickLY(0) == false)
	{
		keyflag = true;
	}

	m_ani_time += 0.2f;
	if (m_ani_time >= 8.0f)
	{
		m_ani_time = 0.0f;
	}

}

//ドロー
void CObjPose::Draw()
{
	if (stay_flag == true)
	{
		//描画カラー情報
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src; //描画元切り取り位置
		RECT_F dst; //描画先表示位置

		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 505.0f;
		src.m_bottom = 305.0f;


		//表示位置の設定
		dst.m_top = 120.0f;
		dst.m_left = 320.0f;
		dst.m_right = 960.0f;
		dst.m_bottom = 580.0f;

		//描画
		Draw::Draw(3, &src, &dst, c, 0.0f);

		//描画カラー情報
		float c2[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src2; //描画元切り取り位置
		RECT_F dst2; //描画先表示位置
		//切り取り位置の設定
		src2.m_top = 0.0f;
		src2.m_left = 0.0f;
		src2.m_right = 64.0f;
		src2.m_bottom = 64.0f;

		if (select_num == 1)
		{
			//表示位置の設定
			dst2.m_top = 230.0f;
			dst2.m_left = 400.0f + m_ani_time;
			dst2.m_right = 464.0f + m_ani_time;
			dst2.m_bottom = 294.0f;
		}
		if (select_num == 2)
		{
			//表示位置の設定
			dst2.m_top = 360.0f;
			dst2.m_left = 400.0f + m_ani_time;
			dst2.m_right = 464.0f + m_ani_time;
			dst2.m_bottom = 426.0f;
		}
		
		if (select_num == 3)
		{
			//表示位置の設定
			dst2.m_top = 480.0f;
			dst2.m_left = 400.0f + m_ani_time;
			dst2.m_right = 464.0f + m_ani_time;
			dst2.m_bottom = 546.0f;
		}
		//描画
		Draw::Draw(4, &src2, &dst2, c2, 0.0f);
	}
}