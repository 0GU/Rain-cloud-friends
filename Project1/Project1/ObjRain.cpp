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
	m_vy = 7.0f;
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, (m_px+16)+pb->GetScroll(), (m_py-32)+pb->GetScrollY(), 64, 64, ELEMENT_PLAYER, OBJ_RAIN, 1);
}

//アクション
void CObjRain::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//HitBoxの位置の変更
	hit->SetPos((m_px+16)+pb->GetScroll(), (m_py-32)+pb->GetScrollY());

	m_py += m_vy;

	if (m_py > 1500.0f)//一定ライン以下まで落下すると削除
	{
		this->SetStatus(false);//自身に削除命令を出す
		Hits::DeleteHitBox(this);//保有するHitBoxに削除する
	}
	if (hit->CheckObjNameHit(OBJ_FIRE) != nullptr || hit->CheckObjNameHit(OBJ_PLANT) != nullptr ||
		hit->CheckObjNameHit(OBJ_SWANP) != nullptr || hit->CheckElementHit(ELEMENT_ENEMY) != false ||
		hit->CheckObjNameHit(OBJ_STONE) != nullptr || hit->CheckObjNameHit(OBJ_SAND) != nullptr)//該当オブジェクトに当たると削除
	{
		this->SetStatus(false);//自身に削除命令を出す
		Hits::DeleteHitBox(this);//保有するHitBoxに削除する
	}
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
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	CObjStage* pbb = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//表示位置の設定
	dst.m_top = (m_py-32)+pbb->GetScrollY();
	dst.m_left = (m_px+16)+pbb->GetScroll();
	dst.m_right = (m_px+16) + 64.0f + pbb->GetScroll();
	dst.m_bottom = (m_py-32) + 64.0f+pbb->GetScrollY();

	//描画
	Draw::Draw(7, &src, &dst, c, 0.0f);


}