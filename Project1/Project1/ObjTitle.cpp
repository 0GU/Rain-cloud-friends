// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjTitle.h"

void CObjTitle::Init()
{
	m_y1 = 0.0f;


	m_scroll = 0.0f;
	move_flag = false;
	scroll_flag = false;

}

//アクション
void CObjTitle::Action()
{
	//黒画面スクロール
	if (scroll_flag == false)
	{
		m_y1 += 50.0f;
		if (m_y1 > 800.0f)
		{
			m_y1 = 800.0f;
			scroll_flag = true;
		}
	}
	if (Input::GetVKey('Z') == true)
	{
		move_flag = true;
	}
	if (move_flag == true)
	{
		m_y1 -= 50.0f;
	}
	if (m_y1 == 0.0f)
	{
		Scene::SetScene(new CSceneStageSelect());//そのステージに移行
	}
}

//ドロー
void CObjTitle::Draw()
{

	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//タイトル背景
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

	//タイトル背景
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 256.0f;

	dst.m_top = 100.0f;
	dst.m_left = 180.0f;
	dst.m_right =1100.0f;
	dst.m_bottom = 400.0f;

	Draw::Draw(1, &src, &dst, c, 0.0f);

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