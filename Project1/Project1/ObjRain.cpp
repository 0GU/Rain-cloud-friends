//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRain.h"

//使用するネームスペース
using namespace GameL;

CObjRain::CObjRain(float x,float y)
{
	m_px = x;
	m_py = y;

}

//イニシャライズ
void CObjRain::Init()
{
	m_vy = 5.0f;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_RAIN, 1);
}

//アクション
void CObjRain::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	m_py += m_vy;

	if (m_py > 1000.0f)
	{
		this->SetStatus(false);//自身に削除命令を出す
		Hits::DeleteHitBox(this);//保有するHitBoxに削除する
	}
	if (hit->CheckObjNameHit(OBJ_FIRE)!=nullptr|| hit->CheckObjNameHit(OBJ_PLANT) != nullptr)
	{
		this->SetStatus(false);//自身に削除命令を出す
		Hits::DeleteHitBox(this);//保有するHitBoxに削除する
	}
	//HitBoxの位置の変更
	hit->SetPos(m_px, m_py);
}

//ドロー
void CObjRain::Draw()
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
	Draw::Draw(7, &src, &dst, c, 0.0f);
}