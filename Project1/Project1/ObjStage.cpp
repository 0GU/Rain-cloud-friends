//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjStage.h"

//使用するネームスペース
using namespace GameL;

CObjStage::CObjStage(int map[15][100])
{
	

	//マップデータをコピー
	memcpy(m_map, map, sizeof(int) * (15 * 100));
}
//イニシャライズ
void CObjStage::Init()
{
	mx_scroll = 0.0f;
	my_scroll = 0.0f;
	m_y1 = 0.0f;
	black_scroll = false;
}

//アクション
void CObjStage::Action()
{
	//黒画面スクロール
	if (black_scroll == false)
	{
		m_y1 += 50.0f;
		if (m_y1 > 800.0f)
		{
			m_y1 = 800.0f;
		}
	}
	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//後方スクロールライン
	if (hx < 80)
	{
		hero->SetX(80);				//主人公はラインを超えないようにする
		mx_scroll -= hero->GetVX();	//主人公が本来動くべき分の値をm_scrollに加える
	}

	//前方スクロールライン
	if (hx > 300)
	{
		hero->SetX(300);			//主人公はラインを超えないようにする
		mx_scroll -= hero->GetVX();	//主人公が本来動くべき分の値をm_scrollに加える
	}

	//上方スクロールライン
	if (hy < 10)
	{
		hero->SetY(10);				//主人公はラインを超えないようにする
		my_scroll -= hero->GetVY();	//主人公が本来動くべき分の値をm_scrollに加える
	}

	//下方スクロールライン
	if (hy > 500)
	{
		hero->SetY(500);			//主人公はラインを超えないようにする
		my_scroll -= hero->GetVY();	//主人公が本来動くべき分の値をm_scrollに加える
	}

	//敵出現ライン
	//主人公の位置+500を敵出現ラインにする
	float line = hx + (-mx_scroll) + 500;

	//敵出現ラインを要素番号化
	int ex = ((int)line) / 64;

	//敵出現ラインの列を検索
	for (int i = 0; i < 15; i++)
	{
		//列の中から4を探す
		if (m_map[i][ex] == 4)
		{
			//4があれば　敵を出現
			CObjEnemy* obje = new CObjEnemy(ex * 64.0f, i * 64.0f);
			Objs::InsertObj(obje, OBJ_ENEMY, 10);

			//敵出現場所の値を0にする
			m_map[i][ex] = 0;
		}
	}
	
}

//ドロー
void CObjStage::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//背景表示
	src.m_top = 256.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	dst.m_top = ZERO_G;
	dst.m_left = ZERO_G;
	dst.m_right = HD_RIGIT;
	dst.m_bottom = HD_BUTTOM;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//マップチップによるblock設置
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
				//表示位置の設定
				dst.m_top = i * 64.0f+my_scroll;
				dst.m_left = j * 64.0f + mx_scroll;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;
				if (m_map[i][j] == 2)
				{
					//スタートブロック
					BlockDraw(320.0f + 64.0f, 0.0f, &dst, c);
				}
				else if (m_map[i][j] == 3)
				{
					//ゴールブロック
					BlockDraw(320.0f + 64.0f, 64.0f, &dst, c);
				}
				else if (m_map[i][j] == 4)
				{
					;//敵配置用の番号のため何もしない
				}
				else if (m_map[i][j] == 5)
				{
					CObjFire* objf = new CObjFire(j * 64.0f, i * 64.0f);
					Objs::InsertObj(objf, OBJ_FIRE, 10);
					m_map[i][j] = 0;
				}
				else
				{
					BlockDraw(320.0f + 0.0f, 0.0f, &dst, c);
				}
			}
		}
	}


	//黒画面
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 16.0f;
	src.m_bottom = 16.0f;

	dst.m_top = 800.0f + m_y1;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_y1;
	Draw::Draw(2, &src, &dst, c, 0.0f);
}

//BlockDrawMethod関数
//引数1 float	x	:リソース切り取り位置X
//引数2 float	y	:リソース切り取り位置Y
//引数3 RECT_F* dst :描画位置
//引数4 float	c[] :カラー情報
//ブロックを64×64限定描画用。リソース切り取り位置のみx・yで
//設定できる
void CObjStage::BlockDraw(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//描画
	Draw::Draw(0, &src, dst, c, 0.0f);
}


//BlockHit関数
//引数1  float* x			:判定を行うobjectのX位置
//引数2  float* y			:判定を行うobjectのY位置
//引数3  bool*	scroll_on	:判定を行うobjectはスクロールの影響を与えるかどうか(true=与える false=与えない)
//引数4  bool*	up			:上下左右判定の上部分に当たっているかどうかを返す
//引数5  bool*	down		:上下左右判定の下部分に当たっているかどうかを返す
//引数6  bool*	left		:上下左右判定の左部分に当たっているかどうかを返す
//引数7  bool*	right		:上下左右判定の右部分に当たっているかどうかを返す
//引数8  float* vx			:左右判定時の反発による移動速度・力の値を変えて返す
//引数9  float* vy			:上下判定時による自由落下速度の移動方向・力の値を変えて返す
//引数10 int*	bt			:下部分判定時、特殊なブロックのタイプを返す
//判定を行うobjectとブロック64×64限定で当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
void CObjStage::BlockHit(
	float* x, float* y, bool scroll_on,
	bool* up, bool* down, bool* left, bool* right,
	float* vx, float* vy, int* bt
)
{
	//衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるのblockの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//スクロールの影響
				float scroll = scroll_on ? mx_scroll : 0;
				float scroll_y = scroll_on ? my_scroll : 0;
				//オブジェクトとブロックの当たり判定
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + 64.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = (*y + (-scroll_y)) - by;

					//長さを求める
					float len = sqrt(rvx * rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//lenがある一定の長さより短い場合判定に入る
					if (len < 88.0f)
					{
						//角度で上下左右を判定
						if ((r < 45 && r > 0) || r > 315)
						{
							//右
							*right = true;//オブジェクトの左の部分が衝突している
							*x = bx + 64.0f + (scroll);//ブロックの位置+オブジェクトの幅
							*vx = -(*vx) * 0.1f;//-VX*反発係数

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//オブジェクトの下の部分が衝突している
							*y = by - 64.0f + (scroll_y);//ブロックの位置-オブジェクトの幅
							//種類を渡すのスタートとゴールのみ変更する
							if (m_map[i][j] >= 2)
								* bt = m_map[i][j];//ブロックの要素（type）をオブジェクトに渡す
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//オブジェクトの右の部分が衝突している
							*x = bx - 64.0f + (scroll);//ブロックの位置-オブジェクトの幅
							*vx = -(*vx) * 0.1f;//-VX*反発係数

						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//オブジェクトの上の部分が衝突している
							*y = by + 64.0f + (scroll_y);//ブロックの位置+オブジェクトの幅
							if (*vy < 0)
							{
								*vy = 0.0f;
							}

						}
					}
				}
			}
		}
	}
}

//内積関数
//引数1,2 float  ax , ay :Aベクトル
//引数3,4 float  bx , by :Bベクトル
//戻り値  float :投影
//内容  AベクトルとBベクトルで内積を行い射影を求める
float CObjStage::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * by;

	return t;
}
//外積関数
//引数1,2 float  ax , ay :Aベクトル
//引数3,4 float  bx , by :Bベクトル
//戻り値  float :投影
//内容　AベクトルとBベクトルで外積を行い射影を求める
float CObjStage::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//符号を求めるマクロ
#define SGN(x) 1 - (x <= 0) - (x < 0)

//線と線と交差判定関数
//引数 float 1, 2  a1x , a1y		:軸ベクトルAの始点
//引数 float 3, 4  a2x , a2y		:軸ベクトルAの終点
//引数 float 5 ,6  b1x , b1y		:ベクトルBの始点
//引数 float 7, 8  b2x , b2y		:ベクトルBの終点
//引数 float 9,10  out_px,out_py	:交差するベクトルの交点位置
//戻り値 bool	:true=交点有り false=交点無し
//内容：引数のA・Bベクトルの交点を見つけ、out_pxとout_pyに返す
bool CObjStage::LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float* out_px, float* out_py
)
{
	//エラーコード
	*out_px = -99999.0f;	*out_py = -99999.0f;

	//Aベクトル作成(a2←a1)
	float ax = a2x - a1x;	float ay = a2y - a1y;

	//Bベクトル作成(b2←b1)
	float bx = b2x - b1x;	float by = b2y - b1y;

	//Cベクトル作成(b1←a1)
	float cx = b1x - a1x;	float cy = b1y - a1y;

	//Dベクトル作成(b2←a1)
	float dx = b2x - a1x;	float dy = b2y - a1y;

	//A×Cの射影とA×Bの射影を求める
	float t1 = Cross(ax, ay, cx, cy);
	float t2 = Cross(ax, ay, bx, by);

	//符号が同じ方向になっているかどうかをチェック
	if (SGN(t1) == SGN(t2))
		return false;	//交点無し

	//射影を絶対値化
	t1 = abs(t1);	t2 = abs(t2);

	//交点を求める
	float px = bx * (t1 / (t1 + t2)) + b1x;
	float py = by * (t1 / (t1 + t2)) + b1y;

	//APベクトル(p←a1)
	float apx = px - a1x;		float apy = py - a1y;

	//BPベクトル(p←a2)
	float bpx = px - a2x;		float bpy = py - a2y;

	//A・APの射影とA・BPの射影を求める
	float w1 = Dot(ax, ay, apx, apy);
	float w2 = Dot(ax, ay, bpx, bpy);

	//符号チェック
	if (SGN(w1) == SGN(w2))
		return false;	//交点が外

	//交点を返す
	*out_px = px;	*out_py = py;
	return true;
}

//主人公と壁の交差判定関数
//引数1,2 float  x , y			:主人公の位置
//引数3,4 float  vx,vy			:主人公の移動ベクトル
//引数5,6 float* out_px,out_py	:Blockとの交点
//引数7,8 float* out			:位置から交点までの距離
//主人公の位置+移動ベクトルと各ブロックの辺で交差判定を行い
//最も近い交点の位置と距離を返す
bool CObjStage::HeroBlockCrossPoint(
	float x, float y, float vx, float vy,
	float* out_px, float* out_py, float* out_len
)
{
	bool pb = false;		  //交点確認用
	float len = 99999.0f; //交点との距離
	//ブロックの辺ベクトル
	float edge[4][4] =
	{
		{ 0, 0,64, 0},//→
		{64, 0,64,64},//↓
		{64,64, 0,64},//←
		{ 0,64, 0, 0},//↑
	};

	//m_mapの全要素にアクセス
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//ブロックの４辺から交点を探す
				for (int k = 0; k < 4; k++)
				{
					//交点を探す
					float px, py;
					bool b;
					float l = 0.0f;
					b = LineCrossPoint(x, y, x + vx, y + vy,
						j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
						&px, &py);

					//交点チェック
					if (b == true)
					{
						//交点との距離を求める
						l = sqrt((px - x) * (px - x) + (py - y) * (py - y));

						//見つけた交点の中で最も距離が短いモノを探す
						if (len > l)
						{
							len = l;
							*out_px = px;
							*out_py = py;
							pb = true;
						}
					}
				}
			}
		}
	}

	*out_len = len;
	return pb;
}
