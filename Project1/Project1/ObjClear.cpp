// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjClear.h"

void CObjClear::Init()
{
	key_flag = true;
	move_flag = false;
	scroll_flag = false;
	m_y1 = 0.0f;
}

//アクション
void CObjClear::Action()
{
	//黒画面スクロール
	if (scroll_flag == false)
	{
		m_y1 += 50.0f;
		if (m_y1 > 800.0f)//画面外を超えたら
		{
			m_y1 = 800.0f;//強制的に止める
			scroll_flag = true;
		}
	}

	if (Input::GetVKey('Z') == true && key_flag == true)//決定
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

	if (Input::GetVKey('Z') == false && key_flag == false)//何故かelseにするとバグるから
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
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 599.0f;
	src.m_bottom = 121.0f;

	dst.m_top = 400.0f;
	dst.m_left = 600.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 521.0f;

	Draw::Draw(1, &src, &dst, c, 30.0f);

	//雫（仮）
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 366.0f;
	src.m_bottom = 400.0f;

	dst.m_top = 400.0f;
	dst.m_left = 20.0f;
	dst.m_right = 270.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(2, &src, &dst, c, 0.0f);

	dst.m_top = 400.0f;
	dst.m_left = 200.0f;
	dst.m_right = 450.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(2, &src, &dst, c, 0.0f);

	dst.m_top = 400.0f;
	dst.m_left = 380.0f;
	dst.m_right = 630.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(2, &src, &dst, c, 0.0f);

	//黒画面
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 16.0f;
	src.m_bottom = 16.0f;

	dst.m_top = 800.0f + m_y1;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_y1;
	Draw::Draw(3, &src, &dst, c, 0.0f);
}