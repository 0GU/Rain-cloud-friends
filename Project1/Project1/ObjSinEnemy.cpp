#include"GameL\DrawTexture.h"
#include"GameL\HitBoxManager.h"
#include"GameHead.h"
#include"ObjSinEnemy.h"


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSinEnemy::CObjSinEnemy(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjSinEnemy::Init()
{
	m_r = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_ENEMY, OBJ_SINENEMY, 1);
}

//アクション
void CObjSinEnemy::Action()
{
	//角度加算
	m_r += 1.0f;

	//360°で初期値に戻す
	if (m_r > 360.0f)
		m_r = 0.0f;

	//移動方向
	m_vx = -1.0f;
	m_vy = sin(3.14 / 180 * m_r);//sinθを求めてm_vyに入れる

	

	//速度をつける
	m_vx *= 1.5f;
	m_vy *= 2.5f;

	//移動ベクトルを座標に加算する
	m_x += m_vx;
	m_y += m_vy;

	

	//ブロックタイプ検知用の変数がないためのダミー
	int d;
	//ブロックとの当たり判定実行
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	pb->BlockHit(&m_x, &m_y, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
		&m_vx, &m_vy, &d
	);

	

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + pb->GetScroll(), m_y + pb->GetScrollY());

	//落下したら消滅
	if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}

	
}
//ドロー
void CObjSinEnemy::Draw()
{
	//描画カラー情報　R=RED G=Green　B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//ブロック情報を持ってくる
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//表示位置の設定
	dst.m_top = 0.0f + m_y + block->GetScrollY();
	dst.m_left = 64.0f + m_x+block->GetScroll();
	dst.m_right = 0.0f + m_x + block->GetScroll();
	dst.m_bottom = 64.0f + m_y +block->GetScrollY();

	//0番目に登録したグラフィックをsrc・dst・cの情報を元に描画
	Draw::Draw(5, &src, &dst, c, 0.0f);
}