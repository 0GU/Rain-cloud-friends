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
	m_scroll = 0.0f;
	move_flag = false;
	scroll_flag = false;
	key_flag = false;
	m_y1 = 0.0f;
}

//アクション
void CObjTitle::Action()
{

	///黒画面スクロール
	if (scroll_flag == false)
	{
		
		m_y1 += 50.0f;//上から下に降ろす
		if (m_y1 > 800.0f)//800を超えたら
		{
			m_y1 = 800.0f;//800に固定
			scroll_flag = true;//スクロールを止める
			key_flag = true;
		}
	}

	if (Input::GetConButtons(0,GAMEPAD_A)&& key_flag == true && scroll_flag==true)//Zキーを押すと
	{
		key_flag = false;//Keyのフラグを止めて

		move_flag = true;//下から上に動かすフラグ起動
	}
	if (Input::GetVKey('Z') == true  && scroll_flag == true)//Zキーを押すと
	{
		key_flag = false;//Keyのフラグを止めて

		move_flag = true;//下から上に動かすフラグ起動
	}
	if (move_flag == true)//起動していると
	{
		m_y1 -= 40.0f;//下から上に動かす
	}

	if (m_y1 == 0.0f)//下から上に
	{
		m_y1 = 0.0f;//0に固定
		scroll_flag = false;
		Scene::SetScene(new CSceneStageSelect);
	}

	if (Input::GetVKey('Z') == false && key_flag == false)
	{

		key_flag = true;
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