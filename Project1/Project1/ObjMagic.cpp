// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/Audio.h"
#include "GameL/HitBoxManager.h"

#include"GameHead.h"
#include"ObjMagic.h"

CObjMagic::CObjMagic(float x, float y,bool posture)
{
	m_px = x;
	m_py = y;
	m_posture = posture;
}

void CObjMagic::Init()
{
	m_check = true;

	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;

	m_ani_frame = 0;
	m_ani_time = 0;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_ENEMY, OBJ_MAGIC, 1);


}

//アクション
void CObjMagic::Action()
{
	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = hero->GetX()-(m_px+block->GetScroll());	//主人公機のｘ座標
	float y = hero->GetY()-(m_py+block->GetScrollY());	//主人公機のｙ座標

	m_r = atan2(-y, x) * 180.0f / 3.14f;
	if (m_r < 0)
	{
		m_r = 360 - abs(m_r);
	}


	//発射したときだけ主人公との座標の差を調べる
	if (m_check == true)
	{
		m_vx = cos(3.14/180*m_r);
		m_vy = sin(3.14 / 180 * m_r);

		m_check = false;
	}



	//速度
	m_px += m_vx * 2.0f;
	m_py -= m_vy * 2.0f;

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY(),32.0f,32.0f);

	//主人公と接触しているか調べる
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr )
	{
		this->SetStatus(false);	//自身に削除命令を出す
		Hits::DeleteHitBox(this);//保有するHitBoxに削除する
	}

	//ブロックタイプ検知用の変数がないためのダミー
	int d;
	//ブロックとの当たり判定実行
	block->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
		&m_vx, &m_vy, &d,false,32.0f,32.0f
	);
	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);	//自身に削除命令を出す
		Hits::DeleteHitBox(this);//保有するHitBoxに削除する
	}

	////領域外に出た弾丸を破棄する
	//bool check = CheckWindow(m_px, m_py, -32.0f, -32.0f, 800.0f, 600.0f);
	//if (check == false)
	//{
	//	this->SetStatus(false);     //自身に削除命令を出す。
	//	Hits::DeleteHitBox(this);   //弾丸が所有するHitBoxに削除する。

	//	return;
	//}

}

//ドロー
void CObjMagic::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//表示位置の設定
	dst.m_top = m_py + block->GetScrollY();
	dst.m_left = m_px + block->GetScroll();
	dst.m_right = m_px + 32.0f + block->GetScroll();
	dst.m_bottom = m_py + 32.0f + block->GetScrollY();

	//描画
	Draw::Draw(7, &src, &dst, c, 0.0f);
}