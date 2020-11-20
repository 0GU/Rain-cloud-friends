// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjTitle.h"

//変数の初期化
void CObjTitle::Init()
{
	move_flag = false;//２回目のフェード起動用
	m_fade_f = false;//1回目のフェード起動用
	key_flag = false;//一回だけ　を判別するためのフラグ
	
	m_fade = 0.0f;//フェードの値を入れる

	select_flag = true;//カーソルが上か下かを判別するためのフラグ
	description_flag = false;//操作説明画面を出すためのフラグ

	m_ani_time = 0.0f;//アニメーション時間
	m_ani_max = 8.0f;//アニメーション最大値

	m_con_num = 5;//念のためコントローラー番号をコントローラが接続されていない番号に初期化
}

//アクション
void CObjTitle::Action()
{
	//コントローラ番号割り当て
	m_con_num = Input::UpdateXControlerConnected();
	
	//フェードイン用操作起動時
	if (m_fade_f == false)
	{
		m_fade += 0.03f;//フェードを少しずつ明るくしていく
		if (m_fade >= 1.0f)//Maxまで来ると
		{
			m_fade = 1.0f;//値をMaxに固定し
			m_fade_f = true;//フェードインを止める
			key_flag = true;//キー操作可能にする
		}
		
	}

	/*
	操作用の変数の流れとしては
	ボタンが押されており、フェードが停止しており、キー操作が可能な場合
	*/
	//コントローラー用------------------------------------------------------------------
	//ステージに進む
	if (Input::GetConButtons(0,GAMEPAD_A) && m_fade_f == true && select_flag == true && key_flag == true)//
	{
		Audio::Start(2);//効果音作動
		key_flag = false;//キー操作不能にする

		move_flag = true;//二回目のフェードを起動
	}

	//カーソル移動
	//カーソルを下に動かす場合
	if (Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) && select_flag == true && key_flag == true && m_fade_f == true)
	{
		Audio::Start(2);//効果音作動
		key_flag = false;//キー操作不能にする
		select_flag = false;//カーソルが下に
	}
	//カーソルを上に動かす場合
	if (Input::GetConButtons(0, GAMEPAD_DPAD_UP) && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
	{
		Audio::Start(2);//効果音作動
		key_flag = false;//キー操作不能にする
		select_flag = true;//カーソルが上に
	}

	//操作説明起動
	if (Input::GetConButtons(0, GAMEPAD_A) && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
	{
		Audio::Start(2);//効果音作動
		key_flag = false;//キー操作不能にする
		description_flag = true;//操作説明画面を表示する
	}
	//操作説明終了
	if (Input::GetConButtons(0, GAMEPAD_A)  && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
	{
		Audio::Start(2);//効果音作動
		key_flag = false;//キー操作不能にする
		description_flag = false;//操作説明画面を非表示にする
	}
	//-----------------------------------------------------------------------------------------

	//キーボード用-----------------------------------------------------------------------------
	if (m_con_num !=0 && m_con_num !=1)
	{
		if (Input::GetVKey('Z') == true && m_fade_f == true && select_flag == true && key_flag == true)//Zキーを押すと
		{
			Audio::Start(2);//効果音作動
			key_flag = false;//Keyのフラグを止めて

			move_flag = true;//二回目のフェードを起動
		}
		//カーソルを下に動かす場合
		if (Input::GetVKey(VK_DOWN) == true && select_flag == true && description_flag == false && key_flag == true && m_fade_f == true)
		{
			Audio::Start(2);//効果音作動
			key_flag = false;//キー操作不能にする
			select_flag = false;//カーソルが下に
		}
		//カーソルを上に動かす場合
		if (Input::GetVKey(VK_UP) == true && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
		{
			Audio::Start(2);//効果音作動
			key_flag = false;//キー操作不能にする
			select_flag = true;//カーソルが上に
		}

		//操作説明起動
		if (Input::GetVKey('Z') == true && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
		{
			Audio::Start(2);//効果音作動
			key_flag = false;//キー操作不能にする
			description_flag = true;//操作説明画面を表示する
		}
		//操作説明終了
		if (Input::GetVKey('Z') == true && select_flag == false && description_flag == true && key_flag == true && m_fade_f == true)
		{
			Audio::Start(2);//効果音作動
			key_flag = false;//キー操作不能にする
			description_flag = false;//操作説明画面を非表示する
		}
	}
	
	//二回目のフェード処理
	if (move_flag == true)//起動していると
	{
		m_fade -=0.03f;//フェードアウトしていく
	}

	if (m_fade <= 0.0f)//完全に真っ暗になったら
	{
		m_fade = 0.0f;//0に固定
		m_fade_f = false;//念のため
		Scene::SetScene(new CSceneStageSelect);//ステージセレクト画面に転移する
	}

	//全てのキーを離していると
	if (Input::GetVKey('Z') == false && Input::GetConButtons(0, GAMEPAD_A)==false && key_flag == false)
	{
		key_flag = true;//キー入力可能にする
	}

	//カーソルのアニメーション
	m_ani_time += 0.2f;
	if (m_ani_time >=8.0f)
	{
		m_ani_time = 0.0f;
	}
}

//ドロー
void CObjTitle::Draw()
{

	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade };//m_fadeの場所は透明度を表す


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//
	if (description_flag == false)
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

		//タイトル文字
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 100.0f;
		dst.m_left = 180.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 400.0f;

		Draw::Draw(1, &src, &dst, c, 0.0f);

		

		//操作説明文字
		src.m_top = 1.0f;
		src.m_left = 1.0f;
		src.m_right = 275.0f;
		src.m_bottom = 70.0f;

		dst.m_top = 500.0f;
		dst.m_left = 490.0f;
		dst.m_right = 765.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);

		//Game Start文字
		src.m_top = 72.0f;
		src.m_left = 1.0f;
		src.m_right = 340.0f;
		src.m_bottom = 125.0f;

		dst.m_top = 401.0f;
		dst.m_left = 490.0f;
		dst.m_right = 830.0f;
		dst.m_bottom = 455.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);



	}
	
	//選択カーソル------------------------------------------
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;
	//上判定
	if (select_flag == true)
	{
		dst.m_top = 400.0f;
		dst.m_left = 420.0f + m_ani_time;
		dst.m_right = 484.0f + m_ani_time;
		dst.m_bottom = 464.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//下判定
	if(select_flag==false)
	{
		dst.m_top = 500.0f;
		dst.m_left = 420.0f + m_ani_time;
		dst.m_right = 485.0f + m_ani_time;
		dst.m_bottom = 564.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//---------------------------------------------------------
	//操作説明画面
	if (description_flag == true)
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
/*	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 800.0f + m_fade;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_fade;
	Draw::Draw(2, &src, &dst, c, 0.0f);*/
}