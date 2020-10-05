// 使用するヘッダーファイル
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/Audio.h"

#include"GameHead.h"
#include"ObjHp.h"


void CObjHp::Init()
{
	caution_flag = true;//瀕死
	danger_flag = true;//重症
	CObjCloud* cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
	cl_MAX_HP = cloud->GetHP();
}

//アクション
void CObjHp::Action()
{
	//主人公から体力の情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	he_hp = hero->GetHP();

	//雲から体力の情報を持ってくる
	CObjCloud* cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
	cl_hp = cloud->GetHP();
	//hpが一定以下の場合効果音を鳴らす
	if (he_hp < 0.5f &&caution_flag==true)
	{
		Audio::Start(9);
		caution_flag = false;
	}
	if (he_hp < 0.2f && danger_flag == true)
	{
		Audio::Start(10);
		danger_flag = false;
	}
	//hpが0以下なら0にする
	if (he_hp <= 0.0f)
		he_hp = 0.0f;
	if (cl_hp <= 0.0f)
		cl_hp = 0.0f;
}

//ドロー
void CObjHp::Draw()
{
	//描画カラー情報
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //描画元切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//主人公：HPゲージ
	//切り取り位置の設定
	src.m_top = 17.0f;
	src.m_bottom = 27.0f;

	if (he_hp > 0.5)
	{
		src.m_left = 0.0f;
		src.m_right = src.m_left + 10.0f;


	}
	else if (he_hp > 0.2)
	{
		src.m_left = 11.0f;
		src.m_right = src.m_left + 10.0f;
	}
	else
	{
		src.m_left = 22.0f;
		src.m_right = src.m_left + 10.0f;
	}

	//表示位置の設定
	dst.m_top = 53.0f;
	dst.m_left = 53.0f;
	dst.m_right = ((174.0f - dst.m_left) * he_hp) + dst.m_left;
	dst.m_bottom = dst.m_top+10.0f;

	//描画
	Draw::Draw(6, &src, &dst, c, 0.0f);

	//雲：HPゲージ
	//切り取り位置の設定
	src.m_top = 17.0f;
	src.m_bottom = 27.0f;

	if ((cl_hp/cl_MAX_HP) > 0.5)
	{
		src.m_left = 33.0f;
		src.m_right = src.m_left + 10.0f;
	}
	else if ((cl_hp / cl_MAX_HP) > 0.2)
	{
		src.m_left = 11.0f;
		src.m_right = src.m_left + 10.0f;
	}
	else
	{
		src.m_left = 22.0f;
		src.m_right = src.m_left + 10.0f;
	}

	//表示位置の設定
	dst.m_top = 73.0f;
	dst.m_left = 53.0f;
	dst.m_right = ((174.0f - dst.m_left) * (cl_hp/cl_MAX_HP)) + dst.m_left;
	dst.m_bottom = dst.m_top + 10.0f;

	//描画
	Draw::Draw(6, &src, &dst, c, 0.0f);


	//HPバー外枠
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 127.0f;
	src.m_bottom = 16.0f;

	//表示位置：主人公
	dst.m_top = 50.0f;
	dst.m_left = 50.0f;
	dst.m_right = 177.0f;
	dst.m_bottom = 66.0f;
	//描画
	Draw::Draw(6, &src, &dst, c, 0.0f);

	//表示位置：雲
	dst.m_top = 70.0f;
	dst.m_bottom = 86.0f;
	//描画
	Draw::Draw(6, &src, &dst, c, 0.0f);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 218.5f;
	src.m_bottom = 133.5f;


	//表示位置の設定
	dst.m_top = 64.0f;;
	dst.m_left = 16.0f;
	dst.m_right = 48.0f;
	dst.m_bottom = 96.0f;

	//描画
	Draw::Draw(8, &src, &dst, c, 0.0f);

}