//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL/DrawFont.h"
#include"GameL/Audio.h"

#include "GameHead.h"
#include "ObjKey.h"

//使用するネームスペース
using namespace GameL;



CObjKey::CObjKey(float x, float y, int k_num)
{
	m_x = x;
	m_y = y;
	Key_num = k_num;
}

void CObjKey::Init()
{

	delete_flag = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_RED, OBJ_KEY, 1);
}

void CObjKey::Action()
{
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + block->GetScroll(), m_y + block->GetScrollY());

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hero->SetKey(Key_num);

		this->SetStatus(false);//自身に削除命令を出す
		Hits::DeleteHitBox(this);//保有するHitBoxに削除する
	}
		
	


}

void CObjKey::Draw()
{

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = src.m_top + 512.0f;


	//表示位置の設定
	dst.m_top = 0.0f + m_y + block->GetScrollY();						//↓描画に対してスクロールの影響を与える
	dst.m_left = 0.0f + m_x + block->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = 64.0f + m_y + block->GetScrollY();

	//描画
	Draw::Draw(13, &src, &dst, c, 0.0f);
}

