//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjCloud.h"

//使用するネームスペース
using namespace GameL;

CObjCloud::CObjCloud(int stage)
{
	reset = stage;
}

//イニシャライズ
void CObjCloud::Init()
{
	m_px = 100.0f;
	m_py = 100.0f;
	m_vx = 5.0f;
	m_vy = 5.0f;
	m_hp = 1.0f;
	stay_flag = false;
	rain_flag = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_CLOUD, 1);
}

//アクション
void CObjCloud::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	CObjStage* pbb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		if (Input::GetVKey('A') == true)
			m_px -= m_vx;
		if (Input::GetVKey('D') == true)
			m_px += m_vx;
		if (Input::GetVKey('W') == true)
			m_py -= m_vy;
		if (Input::GetVKey('S') == true)
			m_py += m_vy;
	}

	if (Input::GetVKey('C') == true && rain_flag == true && m_hp > 0.0f)
	{
		CObjRain* objr = new CObjRain(m_px, m_py+64);
		Objs::InsertObj(objr, OBJ_RAIN, 10);
		rain_flag = false;
		m_hp -= 0.1f;	//hp減少
	}
	if (Input::GetVKey('C') == false && rain_flag == false)
	{
		rain_flag = true;
	}

	//HitBoxの位置の変更
	hit->SetPos(m_px, m_py);
}

//ドロー
void CObjCloud::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;


	//表示位置の設定
	dst.m_top = m_py;
	dst.m_left = m_px;
	dst.m_right = m_px + 64.0f;
	dst.m_bottom = m_py + 64.0f;

	//描画
	Draw::Draw(5, &src, &dst, c, 0.0f);
}