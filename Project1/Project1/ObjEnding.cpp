// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"
#include"GameHead.h"


void CObjEnding::Init()
{
	key_flag = false;
	move_flag = false;//２回目のフェード起動用
	m_fade_f = false;//1回目のフェード起動用

	m_fade = 0.0f;
}

//アクション
void CObjEnding::Action()
{
	//フェードイン用操作起動時
	if (m_fade_f == false)
	{
		m_fade += 0.01f;//フェードを少しずつ明るくしていく
		if (Input::GetConButtons(0, GAMEPAD_A) == true || Input::GetVKey('Z') == true)//フェードイン中にキーを押していると
		{
			;//何もしない
		}
		if (m_fade >= 1.0f)//Maxまで来ると
		{
			m_fade = 1.0f;//値をMaxに固定し
			m_fade_f = true;//フェードインを止める
			key_flag = true;//キー操作可能にする
			
		}
	}

	if (Input::GetVKey('Z') == true &&key_flag==true && move_flag == false)
	{
		key_flag = false;
		move_flag = true;
	}
	//二回目のフェード処理
	if (move_flag == true)//起動していると
	{
		m_fade -= 0.03f;//フェードアウトしていく
	}

	if (m_fade <= -0.01f)//完全に真っ暗になったら
	{
		Scene::SetScene(new CSceneStageSelect);//ステージセレクト画面に転移する

	}
}

//ドロー
void CObjEnding::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1280.0f;
	src.m_bottom = 720.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;

	Draw::Draw(1, &src, &dst, c, 0.0f);
	Draw::Draw(0, &src, &dst, c, 0.0f);
	
}
