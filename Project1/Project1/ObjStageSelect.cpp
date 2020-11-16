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
	m_selectnum = 1;//セレクト番号判別
	m_key_f = false;//一回だけ　を判別するためのフラグ

	m_fade = 0.0f; // フェードの値を入れる

	move_flag = false;//２回目のフェード起動用
	m_fade_f = false;//１回目のフェード起動用

	title_flag = false;//タイトル画面に戻る用フラグ

	//セーブデータをセット（初期化）
	bool set_Stage[3] = { false, false ,false };
	bool set_Stage2[3] = { false, false ,false };
	bool set_Stage3[3] = { false, false ,false };
	Save::Open();
	//セーブデータをセット（セーブされているデータを参照して反映）
	for (int i = 0;i < 3;i++)
	{
		//perfrct
		if (((UserData*)Save::GetData())->Stage_1[i] == true)
		{
			set_Stage[i] = true;
		}
		if (((UserData*)Save::GetData())->Stage_2[i] == true)
		{
			set_Stage2[i] = true;
		}
		if (((UserData*)Save::GetData())->Stage_3[i] == true)
		{
			set_Stage3[i] = true;
		}
	}

	//セットされているデータを個々の配列にコピー
	//ぶっちゃけやる必要があるかは微妙
	memcpy(Clear_flag, set_Stage, sizeof(bool) * (3));
	memcpy(Clear_flag2, set_Stage2, sizeof(bool) * (3));
	memcpy(Clear_flag3, set_Stage3, sizeof(bool) * (3));
}

//アクション
void CObjStageSelect::Action()
{
	Save::Open();

	//フェードイン用操作起動時
	if (m_fade_f == false)
	{
		m_fade += 0.03f;//フェードを少しずつ明るくしていく
		if (m_fade >= 1.0f)//Maxまで来ると
		{
			m_fade = 1.0f;//値をMaxに固定し
			m_fade_f = true;//フェードインを止める
			m_key_f = true;//キー操作可能にする
		}

	}

	/*
	操作用の変数の流れとしては
	ボタンが押されており、フェードが停止しており、キー操作が可能な場合
	クリアデータを参照して内容を切り替えている
	*/
	//ここからステージコマンド------------------(コントローラー用）
	//右に動かす場合
	if (Input::GetConButtons(0, GAMEPAD_DPAD_RIGHT) && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//キー操作不能にする
		Audio::Start(1);
		if (m_selectnum == 3)//セレクトがStage3から超えるのを防ぐ
		{
			;//何もしない
		}
		//Stage1クリアフラグのみが反応している場合
		if (Clear_flag[2] == true && Clear_flag2[2] == false)
		{
			m_selectnum = 2;//Stage2に移行可能
		}
		//Stage1,2クリアフラグが反応している場合
		if (Clear_flag[2] == true && Clear_flag2[2] == true)
		{
			m_selectnum += 1;//1,2,3を選択できるようにする
			if (m_selectnum >= 3)
			{
				m_selectnum = 3;//セレクトがStage3から超えるのを防ぐ
			}
		}
	}
	//左に動かす場合
	if (Input::GetConButtons(0,GAMEPAD_DPAD_LEFT)&& m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//キー操作不能にする
		Audio::Start(1);//効果音作動
		if (m_selectnum == 1)//セレクト
		{
			;//何もしない
		}
		//Stage1クリアフラグが反応している場合
		if (Clear_flag[2] == true && Clear_flag2[2] == false)
		{
			m_selectnum = 1;
		}
		//Stage1,2クリアフラグが反応している場合
		if (Clear_flag[2] == true && Clear_flag2[2] == true)
		{
			m_selectnum -= 1;//1,2,3を選択できるようにする
			if (m_selectnum == 0)
			{
				m_selectnum = 1;//セレクトがStage1からマイナスになるのをのを防ぐ
			}
		}
	}
	//Bボタンが押されている場合
	if ( Input::GetConButtons(0, GAMEPAD_B) && m_key_f == true && m_fade_f == true)
	{

		m_key_f = false;//キー操作不能にする
		Audio::Start(2);//効果音作動
		title_flag = true;//タイトル以移行用フラグを起動し
		move_flag = true;//二回目のフェードを起動
	}
	if (Input::GetConButtons(0, GAMEPAD_A) && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//キー操作不能にする
		Audio::Stop(0);//メインBGM停止
		if (move_flag == false)//音が多重になるため黒幕が上がる前に一回だけ動かす
		{
			Audio::Start(2);
		}
		move_flag = true;//二回目のフェードを起動
	}

	//ここからキーボード用--------------------------------------------------------------
	if (Input::GetVKey(VK_RIGHT) && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//キー操作不能にする
		Audio::Start(1);
		if (m_selectnum == 3)//セレクトがStage3から超えるのを防ぐ
		{
			;//何もしない
		}
		//Stage1クリアフラグのみが反応している場合
		if (Clear_flag[2] == true && Clear_flag2[2] == false)
		{
			m_selectnum = 2;
		}
		//Stage1,2クリアフラグが反応している場合
		if (Clear_flag[2] == true && Clear_flag2[2] == true)
		{
			m_selectnum += 1;//1,2,3を選択できるようにする
			if (m_selectnum >= 3)
			{
				m_selectnum = 3;
			}
		}
	}
	if (Input::GetVKey(VK_LEFT) == true && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//キー操作不能にする
		Audio::Start(1);//効果音作動
		if (m_selectnum == 1)//セレクト
		{
			;//何もしない
		}
		//Stage1クリアフラグが反応している場合
		if (Clear_flag[2] == true && Clear_flag2[2] == false)
		{
			m_selectnum = 1;
		}
		//Stage1,2クリアフラグが反応している場合
		if (Clear_flag[2] == true && Clear_flag2[2] == true)
		{
			m_selectnum -= 1;//1,2,3を選択できるようにする
			if (m_selectnum == 0)
			{
				m_selectnum = 1;//セレクトがStage1からマイナスになるのをのを防ぐ
			}
		}
	}

	if (Input::GetVKey('X') == true && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//キー操作不能にする
		Audio::Start(2);//効果音作動
		title_flag=true;
		move_flag = true;//二回目のフェードを起動
	}

	if (Input::GetVKey('Z') == true  &&  m_key_f == true && m_fade_f == true)//Stage1
	{
		m_key_f = false;//キー操作不能にする
		Audio::Stop(0);
		if (move_flag == false)//音が多重になるため黒幕が上がる前に一回だけ動かす
		{
			Audio::Start(2);//効果音作動
		}
		move_flag = true;//二回目のフェードを起動
	}

	//ここまで------------------------
	//二回目のフェード処理
	if (move_flag == true)//起動していると
	{
		m_fade -= 0.03f;//フェードアウトしていく
	}

	if (m_fade <= 0.0f)//完全に真っ暗になったら
	{
		m_fade = 0.0f;//0に固定
		if (title_flag == true)//タイトル用フラグが起動していると
		{
			Scene::SetScene(new CSceneTitle);//titleシーンに移行
		}
		else//起動していない場合は
		{
			Scene::SetScene(new CSceneGameMain(m_selectnum));//そのステージに移行
		}
		
	}
	//全てのキーを離していると
	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false &&
		Input::GetVKey('X') == false && Input::GetVKey('Z') == false && Input::GetVKey('B') == false &&
		Input::GetConButtons(0, GAMEPAD_DPAD_RIGHT)==false && Input::GetConButtons(0, GAMEPAD_DPAD_LEFT) == false&&
		m_key_f == false
		)
	{

		m_key_f = true;//キー入力可能にする

	}
}

//ドロー
void CObjStageSelect::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade };//

	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//hoge背景1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = HD_RIGIT;
	src.m_bottom = HD_BUTTOM;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = HD_RIGIT;
	dst.m_bottom = HD_BUTTOM;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//Stage1赤色選択
	if (m_selectnum == 1)
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
		if (Clear_flag[2] == true)
		{
			src.m_left = 301.0f;
			src.m_right = 601.0f;

			dst.m_left = 500.0f;
			dst.m_right = 800.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);
		}
		if (Clear_flag2[2] == true)
		{
			//stage3
			dst.m_left = 900.0f;
			dst.m_right = 1200.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);
		}
	}
	//Stage2赤色選択
	if (Clear_flag[2] == true)
	{
		if (m_selectnum == 2)
		{
			//stage1
			src.m_top = 0.0f;
			src.m_left = 301.0f;
			src.m_right = 601.0f;
			src.m_bottom = 200.0f;

			dst.m_top = 350.0f;
			dst.m_left = 100.0f;
			dst.m_right = 400.0f;
			dst.m_bottom = 550.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);

			// stage2
			src.m_left = 0.0f;
			src.m_right = 300.0f;

			dst.m_top = 350.0f;
			dst.m_left = 500.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 550.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);

			if (Clear_flag2[2] == true)
			{
				//stage3
				src.m_left = 301.0f;
				src.m_right = 601.0f;

				dst.m_left = 900.0f;
				dst.m_right = 1200.0f;
				Draw::Draw(1, &src, &dst, c, 0.0f);
			}
		}
	}
	
	//Stage3赤色選択
	if (Clear_flag2[2] == true)
	{
		if (m_selectnum == 3)
		{
			//stage1
			src.m_top = 0.0f;
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
			src.m_left = 0.0f;
			src.m_right = 300.0f;


			dst.m_left = 900.0f;
			dst.m_right = 1200.0f;

			Draw::Draw(1, &src, &dst, c, 0.0f);
		}
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
	if (Clear_flag[2] == true)
	{
		src.m_top = 321.0f;
		src.m_left = 302.0f;
		src.m_right = 602.0f;
		src.m_bottom = 421.0f;

		dst.m_top = 201.0f;
		dst.m_left = 500.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 321.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	
	//Stage3
	if (Clear_flag2[2] == true)
	{
		src.m_top = 321.0f;
		src.m_left = 603.0f;
		src.m_right = 903.0f;
		src.m_bottom = 421.0f;

		dst.m_top = 201.0f;
		dst.m_left = 900.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 321.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	

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
	if (Clear_flag[2] == true)
	{
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
	}
	
	//stage3
	if (Clear_flag2[2] == true)
	{
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

	}
	//-------------------ここまで
}