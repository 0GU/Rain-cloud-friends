// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjSign.h"

CObjSign::CObjSign(float x, float y)
{
	m_px = x;			//位置
	m_py = y;
}
void CObjSign::Init()
{

}

//アクション
void CObjSign::Action()
{

}

//ドロー
void CObjSign::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	dst.m_top = m_py + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();
	//描画
	Draw::Draw(34, &src, &dst, c, 0.0f);

}