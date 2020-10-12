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

	select_flag = true;
	description_flag = true;
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
	//コントローラー用------------------------------------------------------------------
	//ステージに進む
	if (Input::GetConButtons(0,GAMEPAD_A) && scroll_flag == true && select_flag == true && key_flag == true)//Aボタンを押すと
	{
		Audio::Start(2);
		key_flag = false;//Keyのフラグを止めて

		move_flag = true;//下から上に動かすフラグ起動
	}
	//操作説明に移行
	//カーソル移動
	if (Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) && select_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		select_flag = false;
	}

	if (Input::GetConButtons(0, GAMEPAD_DPAD_UP) && select_flag == false && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		select_flag = true;
	}
	//操作説明起動
	if (Input::GetConButtons(0, GAMEPAD_A) && select_flag == false && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		description_flag = false;
	}
	//操作説明終了
	if (Input::GetConButtons(0, GAMEPAD_A)  && select_flag == false && description_flag == false && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		description_flag = true;
	}
	//キーボード用-----------------------------------------------------------------------------
	//ステージに進む
	if (Input::GetVKey('Z') == true  && scroll_flag == true && select_flag ==true && key_flag == true)//Zキーを押すと
	{
		Audio::Start(2);
		key_flag = false;//Keyのフラグを止めて

		move_flag = true;//下から上に動かすフラグ起動
	}
	//操作説明に移行
	//カーソル移動
	if (Input::GetVKey(VK_DOWN) == true && select_flag == true && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		select_flag = false;
	}

	if (Input::GetVKey(VK_UP) == true && select_flag == false && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		select_flag = true;
	}
	//操作説明起動
	if (Input::GetVKey('Z') == true && select_flag == false && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		description_flag = false;
	}
	//操作説明終了
	if (Input::GetVKey('Z') == true && select_flag == false && description_flag == false && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		description_flag = true;
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

	if (Input::GetVKey('Z') == false && Input::GetConButtons(0, GAMEPAD_A)==false && key_flag == false)
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

	if (description_flag == true)
	{
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
		dst.m_right = 1100.0f;
		dst.m_bottom = 400.0f;

		Draw::Draw(1, &src, &dst, c, 0.0f);

		

		//操作説明
		src.m_top = 1.0f;
		src.m_left = 1.0f;
		src.m_right = 275.0f;
		src.m_bottom = 70.0f;

		dst.m_top = 500.0f;
		dst.m_left = 490.0f;
		dst.m_right = 765.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);

		//Game Start
		src.m_top = 72.0f;
		src.m_left = 1.0f;
		src.m_right = 340.0f;
		src.m_bottom = 125.0f;

		dst.m_top = 401.0f;
		dst.m_left = 490.0f;
		dst.m_right = 830.0f;
		dst.m_bottom = 455.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);

		//選択カーソル------------------------------------------
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

	}
	
	//上判定
	if (select_flag == true)
	{
		dst.m_top = 400.0f;
		dst.m_left = 420.0f;
		dst.m_right = 484.0f;
		dst.m_bottom = 464.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//下判定
	if(select_flag==false)
	{
		dst.m_top = 500.0f;
		dst.m_left = 420.0f;
		dst.m_right = 485.0f;
		dst.m_bottom = 564.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//操作説明
	if (description_flag == false)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1280.0f;
		src.m_bottom = 720.0f;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 1280.0f;
		dst.m_bottom = 720.0f;
		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
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