// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjOver.h"

CObjOver::CObjOver(int stagenum)
{
	restart = stagenum;
}

//イニシャライズ
void CObjOver::Init()
{
	//初期化
	selectnum = 1;
	selectnum_c = 1;
	keyflag = true;

	m_y1 = 0.0f;

	move_flag = false;
	scroll_flag = false;
	check_flag = false;
}

//アクション
void CObjOver::Action()
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

	//ここからステージコマンド------------------
	if (Input::GetVKey(VK_DOWN) == true && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);

		//通常時
		if (check_flag == false)
		{
			if (selectnum == 3)
			{
				;//何もしない
			}
			else
			{
				selectnum += 1;
			}
		}
		//確認画面
		else
		{
			if (selectnum_c == 1)
			{
				selectnum_c++;
			}
		}
	}
	else if (Input::GetVKey(VK_UP) == true && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);

		//通常時
		if (check_flag == false)
		{
			if (selectnum == 1)
			{
				;//何もしない
			}
			else
			{
				selectnum -= 1;
			}
		}
		//確認画面
		else
		{
			if (selectnum_c == 2)
			{
				selectnum_c--;
			}
		}

	}

	//画面移行
	if (Input::GetVKey('Z') == true && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		
		//通常時
		if (check_flag == false)
		{
			//コンティニュー以外は確認を挟む
			if (selectnum == 1)
			{
				move_flag = true;
			}
			else
			{
				check_flag = true;
			}
		}
		//確認画面
		else
		{
			if (selectnum_c == 1)
				move_flag = true;
			else
				check_flag = false;
		}
	}

	//画面移行部分　スクロール終了したら移行
	if (move_flag == true)
	{
		m_y1 -= 50.0f;
	}
	if (m_y1 == 0.0f)
	{
		switch (selectnum)
		{
			case 1:
				Scene::SetScene(new CSceneGameMain(restart));
				break;
			case 2:
				Scene::SetScene(new CSceneStageSelect);
				break;
			case 3:
				Scene::SetScene(new CSceneTitle);
				break;
		}
	}

	//キー解放
	if (Input::GetVKey(VK_DOWN) == false && Input::GetVKey(VK_UP) == false &&
		Input::GetVKey('Z') == false && keyflag == false)
	{
		keyflag = true;
	}

}

//ドロー
void CObjOver::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//背景
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1023.0f;
	src.m_bottom = 63.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//GAMEOVER
	src.m_top = 64.0f;
	src.m_left = 704.0f;
	src.m_right = 831.0f;
	src.m_bottom = 127.0f;

	dst.m_top = 200.0f;
	dst.m_left = 550.0f;
	dst.m_right = 650.0f;
	dst.m_bottom = 264.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//コンティニュー
	//src.m_top = 0.0f;
	src.m_left = 256.0f;
	src.m_right = 383.0f;
	//src.m_bottom = 0.0f;

	dst.m_top = 300.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 0.0f;
	dst.m_bottom = 364.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//セレクト戻る
	//src.m_top = 0.0f;
	src.m_left = 128.0f;
	src.m_right = 255.0f;
	//src.m_bottom = 0.0f;

	dst.m_top = 400.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 0.0f;
	dst.m_bottom = 464.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//タイトル戻る
	//src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 127.0f;
	//src.m_bottom = 0.0f;

	dst.m_top = 500.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 0.0f;
	dst.m_bottom = 564.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	if (check_flag == true)
	{
		//確認
		//src.m_top = 0.0f;
		src.m_left = 384.0f;
		src.m_right = 511.0f;
		//src.m_bottom = 0.0f;

		dst.m_top = 250.0f;
		//dst.m_left = 0.0f;
		//dst.m_right = 0.0f;
		dst.m_bottom = 314.0f;
		Draw::Draw(0, &src, &dst, c, 0.0f);

		//はい
		//src.m_top = 0.0f;
		src.m_left = 576.0f;
		src.m_right = 639.0f;
		//src.m_bottom = 0.0f;

		dst.m_top = 350.0f;
		dst.m_left = 568.0f;
		dst.m_right = 632.0f;
		dst.m_bottom = 414.0f;
		Draw::Draw(0, &src, &dst, c, 0.0f);

		//いいえ
		//src.m_top = 0.0f;
		src.m_left = 640.0f;
		src.m_right = 703.0f;
		//src.m_bottom = 0.0f;

		dst.m_top = 450.0f;
		//dst.m_left = 0.0f;
		//dst.m_right = 0.0f;
		dst.m_bottom = 514.0f;
		Draw::Draw(0, &src, &dst, c, 0.0f);
		
		//カーソル
		//src.m_top = 0.0f;
		src.m_left = 512.0f;
		src.m_right = 575.0f;
		//src.m_bottom = 0.0f;

		dst.m_top = 350.0f+(selectnum_c-1)*100.0f;
		dst.m_left = 468.0f;
		dst.m_right = 532.0f;
		dst.m_bottom = 414.0f + (selectnum_c - 1) * 100.0f;
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}

	//カーソル
	//src.m_top = 0.0f;
	src.m_left = 512.0f;
	src.m_right = 575.0f;
	//src.m_bottom = 0.0f;

	dst.m_top = 300.0f + (selectnum - 1) * 100.0f;
	dst.m_left = 468.0f;
	dst.m_right = 532.0f;
	dst.m_bottom = 364.0f + (selectnum - 1) * 100.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//黒画面
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 800.0f + m_y1;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_y1;
	Draw::Draw(3, &src, &dst, c, 0.0f);

}