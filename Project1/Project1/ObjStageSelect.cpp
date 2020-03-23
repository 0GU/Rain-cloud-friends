//使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjStageSelect.h"

void CObjStageSelect::Init()
{
	stage = 1;
}

//アクション
void CObjStageSelect::Action()
{
	if (Input::GetVKey(VK_RIGHT)==true)
	{
		if (stage == 3)
		{
			;//何もしない
		}
		else
		{
			stage++;
		}
	}
	if (Input::GetVKey(VK_LEFT)==true)
	{
		if (stage == 1)
		{
			;//何もしない
		}
		else
		{
			stage--;
		}
		
		if (Input::GetVKey('Z') == true)
		{
			for (int i = 1 ;i < stage;i++)
			{
				if (stage == i)
				{
					;//そのステージに移行
				}
			}
			
		}
	}
	if (Input::GetVKey('X') == true)
	{
		;//titleシーンに移行
	}
}

//ドロー
void CObjStageSelect::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//hoge1
	src.m_top = ZERO_G;
	src.m_left = ZERO_G;
	src.m_right = HD_RIGIT;
	src.m_bottom = HD_BUTTOM;

	dst.m_top = ZERO_G;
	dst.m_left = ZERO_G;
	dst.m_right = HD_RIGIT;
	dst.m_bottom = HD_BUTTOM;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 0.0f;
	src.m_bottom = 0.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 0.0f;
	dst.m_bottom = 0.0f;

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 0.0f;
	src.m_bottom = 0.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 0.0f;
	dst.m_bottom = 0.0f;

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 0.0f;
	src.m_bottom = 0.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 0.0f;
	dst.m_bottom = 0.0f;

}