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
	key_flag = true;
	move_flag = false;//２回目のフェード起動用
	m_fade_f = false;//1回目のフェード起動用
	key_flag = false;//一回だけ　を判別するためのフラグ

	m_fade = 0.0f;//フェードの値を入れる
	move_flag2 = false;
	move_flag = false;

	check_flag = false;
}

//アクション
void CObjOver::Action()
{
	//コントローラー操作仮
	//m_con_num = Input::UpdateXControlerConnected();

	//フェードイン用操作起動時
	if (m_fade_f == false)
	{
		m_fade += 0.03f;//フェードを少しずつ明るくしていく
		if (m_fade >= 1.0f)//Maxまで来ると
		{
			m_fade = 1.0f;//値をMaxに固定し
			m_fade_f = true;//フェードインを止める
			if (Input::GetConButtons(0, GAMEPAD_A) ||Input::GetVKey('Z')==true)//フェードイン中にキーを押していると
			{
				;//何もしない
			}
			else
			{
				key_flag = true;//キー操作可能にする
			}

		}

	}

	//ここからステージコマンド------------------
	

	//キーボード用------------------------------
	if (Input::GetVKey(VK_DOWN) == true && key_flag == true && move_flag == false)
	{
		key_flag = false;
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
	else if (Input::GetVKey(VK_UP) == true && key_flag == true && move_flag == false)
	{
		key_flag = false;
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
	if (Input::GetVKey('Z') == true && key_flag == true && move_flag == false)
	{
		key_flag = false;
		Audio::Start(2);
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
				//Audio::Start(2);
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
	//コントローラー用------------------------
	if (Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) == true && key_flag == true && move_flag == false)
	{
		key_flag = false;
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
	if (Input::GetConButtons(0, GAMEPAD_DPAD_UP) && key_flag == true && move_flag == false)
	{
		key_flag = false;
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
	if (Input::GetConButtons(0, GAMEPAD_A) && key_flag == true && move_flag == false)
	{
		key_flag = false;
		Audio::Start(2);
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
				//Audio::Start(2);
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

	//二回目のフェード処理
	if (move_flag == true)//起動していると
	{
		m_fade -= 0.03f;//フェードアウトしていく
	}

	if (m_fade <= -0.01f)//完全に真っ暗になったら
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
		Input::GetVKey('Z') == false && key_flag == false && Input::GetConButtons(0, GAMEPAD_A) == false&&
		Input::GetConButtons(0, GAMEPAD_DPAD_DOWN)==false && Input::GetConButtons(0, GAMEPAD_DPAD_UP)==false)
	{
		key_flag = true;
	}

}

//ドロー
void CObjOver::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//背景
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1280.0f;
	src.m_bottom = 720.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;
	Draw::Draw(4, &src, &dst, c, 0.0f);

	//画像貼り進捗
	//画面サイズは 1280*720 っつってんだろくそが！！！！(自分)
	if (check_flag == false)
	{
		//GAMEOVER
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1007.0f;
		src.m_bottom = 128.0f;

		dst.m_top = 100.0f;
		dst.m_left = 136.0f;
		dst.m_right = 1043.0f;
		dst.m_bottom = 228.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//コンティニュー
		src.m_top = 132.0f;
		src.m_left = 0.0f;
		src.m_right = 848.0f;
		src.m_bottom = 259.0f;

		dst.m_top = 350.0f;
		dst.m_left = 428.0f;
		dst.m_right = 852.0f;
		dst.m_bottom = 414.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//セレクト戻る
		//src.m_top = 261.0f;
		//src.m_left = 0.0f;
		//src.m_right = 546.0f;
		//src.m_bottom = 390.0f;

		//dst.m_top = 450.0f;
		//dst.m_left = .0f;
		//dst.m_right = .0f;
		//dst.m_bottom = 579.0f;
		//Draw::Draw(1, &src, &dst, c, 0.0f);

		src.m_top = 392.0f;
		src.m_left = 0.0f;
		src.m_right = 631.0f;
		src.m_bottom = 521.0f;

		dst.m_top = 444.0f;
		dst.m_left = 482.0f;
		dst.m_right = 797.0f;
		dst.m_bottom = 509.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);


		//タイトル戻る
		src.m_top = 523.0f;
		src.m_left = 0.0f;
		src.m_right = 1002.0f;
		src.m_bottom = 657.0f;

		dst.m_top = 539.0f;
		dst.m_left = 389.0f;
		dst.m_right = 890.0f;
		dst.m_bottom = 606.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//カーソル
		src.m_top = 64.0f;
		src.m_left = 512.0f;
		src.m_right = 575.0f;
		src.m_bottom = 128.0f;

		dst.m_top = 350.0f + (selectnum - 1) * 90.0f;
		dst.m_left = 306.0f;
		dst.m_right = 370.0f;
		dst.m_bottom = 414.0f + (selectnum - 1) * 90.0f;
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	else if (check_flag == true)
	{
		//確認
		src.m_top = 659.0f;
		src.m_left = 0.0f;
		src.m_right = 997.0f;
		src.m_bottom = 766.0f;

		dst.m_top = 150.0f;
		dst.m_left = 391.0f;
		dst.m_right = 889.0f;
		dst.m_bottom = 203.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//はい
		src.m_top = 768.0f;
		src.m_left = 0.0f;
		src.m_right = 273.0f;
		src.m_bottom = 898.0f;

		dst.m_top = 300.0f;
		dst.m_left = 572.0f;
		dst.m_right = 708.0f;
		dst.m_bottom = 365.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//いいえ
		//src.m_top = 0.0f;
		src.m_left = 275.0f;
		src.m_right = 691.0f;
		//src.m_bottom = 0.0f;

		dst.m_top = 400.0f;
		dst.m_left = 534.0f;
		dst.m_right = 746.0f;
		dst.m_bottom = 465.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//カーソル
		src.m_top = 64.0f;
		src.m_left = 512.0f;
		src.m_right = 575.0f;
		src.m_bottom = 128.0f;

		dst.m_top = 300.0f + (selectnum_c - 1) * 100.0f;
		dst.m_left = 448.0f;
		dst.m_right = 512.0f;
		dst.m_bottom = 364.0f + (selectnum_c - 1) * 100.0f;
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}


}