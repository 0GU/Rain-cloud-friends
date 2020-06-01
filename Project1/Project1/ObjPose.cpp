// 使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjPose.h"

CObjPose::CObjPose(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}

//イニシャライズ
void CObjPose::Init()
{
	delete_flag = false;
	stay_flag = false;
	select_flag = false;
}

//アクション
void CObjPose::Action()
{
	if (Input::GetVKey('M') == true)
	{
		stay_flag = true;
	}
	if (stay_flag == true)
	{
		if (Input::GetVKey('Q') == true)
		{
			stay_flag = false;
		}
		if (Input::GetVKey(VK_UP) == true)
		{
			select_flag = false;
		}
		if (Input::GetVKey(VK_DOWN) == true)
		{
			select_flag = true;
		}
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (select_flag == false)
				stay_flag = false;
			if(select_flag==true)
				Scene::SetScene(new CSceneStageSelect());//そのステージに移行
		}
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
		src.m_right = 64.0f;
		src.m_bottom = 40.0f;


		//表示位置の設定
		dst.m_top = 180.0f;
		dst.m_left = 320.0f;
		dst.m_right = 960.0f;
		dst.m_bottom = 640.0f;

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

		if (select_flag == false)
		{
			//表示位置の設定
			dst2.m_top = 180.0f;
			dst2.m_left = 320.0f;
			dst2.m_right = 384.0f;
			dst2.m_bottom = 244.0f;
		}
		if (select_flag == true)
		{
			//表示位置の設定
			dst2.m_top = 576.0f;
			dst2.m_left = 320.0f;
			dst2.m_right = 384.0f;
			dst2.m_bottom = 640.0f;
		}
		

		//描画
		Draw::Draw(4, &src2, &dst2, c2, 0.0f);
	}
}