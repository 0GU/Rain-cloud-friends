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

}

//アクション
void CObjTitle::Action()
{
	if (Input::GetVKey('Z') == true)
	{
		Scene::SetScene(new CSceneStageSelect());
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

}