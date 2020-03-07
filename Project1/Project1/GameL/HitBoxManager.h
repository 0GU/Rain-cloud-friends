#pragma once
//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

#include <memory>
#include <list>
using namespace std;

namespace GameL
{
	//---	衝突状態構造体		---//
	struct HIT_BOX
	{
		float x;	//位置x
		float y;	//位置y
		float h;	//高さ
		float w;	//幅
	};
	struct HIT_STATUS
	{
		 int  e;	//当たり判定属性
		 int  n;	//オブジェクトネーム
		 bool i;	//無敵スイッチ
		 int  p;	//個別ポイント情報
	};
	struct HIT_DATA
	{
		int	  e;	//当たった相手の属性情報
		int   n;	//当たった相手のオブジェクトネーム
		int	  p;	//当たった相手のポイント情報
		float s;	//距離
		float r;	//当たっている角度
		void* o;	//当たっているオブジェクトアドレス
	};
	//-----------------------------//
	//---	衝突判定用クラス	---//
	typedef class CHitBox
	{
		friend class CHitBoxManager;
		public:
			CHitBox();
			~CHitBox();
			void SetObj(void* t);									//このHitBoxが持つオブジェクトアドレスの設定
			void SetPos(float x,float y,float h,float w);			//座標・大きさ設定
			void SetPos(float x,float y);							//座標設定
			void SetStatus(int e,int n,int p);						//属性・オブジェクトネーム・ポイント設定
			void SetInvincibility(bool i);							//無敵の有無

			void* CheckObjNameHit(int obj_name);					//HIT_BOX中のオブジェクトネームを探す
			void* CheckObjNameHit(int obj_name,int point);			//HIT_BOX中のオブジェクトネームとポイントで探す
			bool  CheckElementHit(int element);						//HIT_BOX中にある属性情報を見る
			bool  CheckElementHit(int element,int point);			//HIT_BOX中にある属性情報とポイントを見る

			HIT_DATA** SearchObjNameHit(int name);					//HIT_BOX中のネームで探した結果を配列にして出力
			HIT_DATA** SearchObjNameHit(int name,int point);		//HIT_BOX中のネーム・ポイントで探した結果を配列にして出力
			HIT_DATA** SearchElementHit(int element);				//HIT_BOX中の属性で探した結果を配列にして出力
			HIT_DATA** SearchElementHit(int element,int point);		//HIT_BOX中の属性・ポイントで探した結果を配列にして出力
			
			int		    GetCount();									//当たっているヒット相手の数を返す
			bool	    GetInvincibility();							//無敵状態確認
			void*	    GetMyObj();									//このHITBOXを持つオブジェクトアドレスを返す
			HIT_STATUS* GetStatus();								//ステータスの状態
			HIT_BOX*	GetHitBox();								//位置・高さ・幅
		private:
			void SortHitBox();					//当たっている情報の距離ソート
			HIT_STATUS	  m_hit_status;			//当たり判定の状態
			HIT_BOX		  m_hit_box;			//当たり判定の座標幅
			HIT_DATA*	  m_hit_data;			//当たっている相手の情報[10]
			HIT_DATA**	  m_hit_search_data;	//当たっている相手の中で属性・ネーム検索後の情報[10]
			void*		  m_my_obj;				//このHitBoxが持つオブジェクトアドレス
			int			  m_hit_count;			//ヒットしているカウント数
	}HitBox;
	//-----------------------------//

	//衝突判定マネージャー
	typedef class CHitBoxManager
	{
		public:
			static void		Init();
			static void		Delete();
			static void		SetHitBox(void* t,float x,float y,float w,float h,int e,int n,int p);	//ヒットボックスの作成と登録
			static CHitBox*	GetHitBox(void* t);												//自分のアドレスを持つヒットボックスを返す
			static void		DeleteHitBox(void* t);											//自分のアドレスを持つヒットボックスの削除
			static void		AllHitCheck();													//衝突判定
			static void		DeleteAllListData();											//リスト情報破棄
			static void		DrawHitBox();													//デバック用の当たり判定描画
		private:
			static bool Hit(HIT_BOX* a, HIT_BOX* b, HIT_DATA* hit);							//aがｂのどこに当たっているか
			static list<shared_ptr<CHitBox>>*	m_ListHitBox;								//衝突判定リスト

	}Hits;
};