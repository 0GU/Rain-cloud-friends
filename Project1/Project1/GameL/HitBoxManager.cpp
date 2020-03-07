#include "DrawTexture.h"	//２Ｄ描画はDrawTextureに依存する
#include "HitBoxManager.h"
using namespace GameL;

#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p)=nullptr;}}

//当たり判定の複数同時判定量
#define MAX_HITS	(10)

//衝突判定当たっていない状態
#define	HIT_NULL	    (  -9999)	 
#define HIT_LONG_OUT	(9999.0f)

list<shared_ptr<CHitBox>>*	CHitBoxManager::m_ListHitBox;	//衝突判定リスト

//ヒットボックスメソッド-------------
CHitBox::CHitBox()
{
	//初期化
	m_my_obj		 = nullptr;
	m_hit_data		 = new HIT_DATA [MAX_HITS];
	m_hit_search_data= new HIT_DATA*[MAX_HITS];
	m_hit_count		 = 0;
	memset(&m_hit_status,0x00,sizeof(HIT_STATUS));
	
}
CHitBox::~CHitBox()
{
	SAFE_DELETE_ARRAY(m_hit_data);
	SAFE_DELETE_ARRAY(m_hit_search_data);
}
void CHitBox::SetObj(void* t)
{
	m_my_obj=t;
}
void CHitBox::SetPos(float x,float y,float h,float w)
{
	m_hit_box.x=x;
	m_hit_box.y=y;
	m_hit_box.h=h;
	m_hit_box.w=w;
}
void CHitBox::SetPos(float x,float y)
{
	m_hit_box.x=x;
	m_hit_box.y=y; 
}
void CHitBox::SetStatus(int e,int n,int p)
{
	m_hit_status.e=e;
	m_hit_status.n=n;
	m_hit_status.p=p;
}
void CHitBox::SetInvincibility(bool i)
{
	m_hit_status.i=i;
}

int CHitBox::GetCount()
{
	return m_hit_count;
}

bool CHitBox::GetInvincibility()
{
	return m_hit_status.i;
}

void* CHitBox::GetMyObj()
{
	return m_my_obj;
}

HIT_STATUS* CHitBox::GetStatus()
{
	return &m_hit_status;
}

HIT_BOX* CHitBox::GetHitBox()
{
	return &m_hit_box;
}

//HIT_BOX中のオブジェクトネームを探す
void* CHitBox::CheckObjNameHit(int obj_name)
{
	for(int i=0;i<m_hit_count;i++)
		if(m_hit_data[i].o!=nullptr)
			if(m_hit_data[i].n==obj_name)
				return m_hit_data[i].o;
	return nullptr;
}
//HIT_BOX中のオブジェクトネームとポイントで探す
void* CHitBox::CheckObjNameHit(int obj_name,int point)
{
	for(int i=0;i<m_hit_count;i++)
		if(m_hit_data[i].o!=nullptr)
			if(m_hit_data[i].n==obj_name)
				if(m_hit_data[i].p==point)
					return m_hit_data[i].o;
	return nullptr;
}
//HIT_BOX中にある属性情報を見る
bool CHitBox::CheckElementHit(int element)
{
	for(int i=0;i<m_hit_count;i++)
		if(m_hit_data[i].o!=nullptr)
			if(m_hit_data[i].e==element)
				return true;
	return false;
}
//HIT_BOX中にある属性情報とポイントを見る
bool CHitBox::CheckElementHit(int element,int point)
{
	for(int i=0;i<m_hit_count;i++)
		if(m_hit_data[i].o!=nullptr)
			if(m_hit_data[i].e==element)
				if(m_hit_data[i].p==point)
					return true;
	return false;
}

//HIT_BOX中のネームで探した結果を配列にして出力
HIT_DATA** CHitBox::SearchObjNameHit(int obj_name)
{
	SortHitBox();
	memset(&(*m_hit_search_data),0x00,sizeof(HIT_DATA*)*MAX_HITS);
	for(int i=0;i<m_hit_count;i++)
		if(m_hit_data[i].o!=nullptr)
			if(m_hit_data[i].n==obj_name)
					 m_hit_search_data[i]=&m_hit_data[i];

	if(m_hit_count==0)
	{
		return nullptr;
	}
	else
	{
		return m_hit_search_data;
	}
}

//HIT_BOX中のネーム・ポイントで探した結果を配列にして出力
HIT_DATA** CHitBox::SearchObjNameHit(int name,int point)
{
	SortHitBox();
	memset(&(*m_hit_search_data),0x00,sizeof(HIT_DATA*)*MAX_HITS);
	for(int i=0;i<m_hit_count;i++)
		if(m_hit_data[i].o!=NULL)
			if(m_hit_data[i].n==name)
				if(m_hit_data[i].p==point)
					 m_hit_search_data[i]=&m_hit_data[i];
	if(m_hit_count==0)
	{
		return nullptr;
	}
	else
	{
		return m_hit_search_data;
	}
}	
	
//HIT_BOX中の属性で探した結果を配列にして出力
HIT_DATA** CHitBox::SearchElementHit(int element)
{
	SortHitBox();
	memset(&(*m_hit_search_data),0x00,sizeof(HIT_DATA*)*MAX_HITS);
	for(int i=0;i<m_hit_count;i++)
		if(m_hit_data[i].o!=NULL)
			if(m_hit_data[i].e==element)
					 m_hit_search_data[i]=&m_hit_data[i];
	if(m_hit_count==0)
	{
		return nullptr;
	}
	else
	{
		return m_hit_search_data;
	}
}

//HIT_BOX中の属性・ポイントで探した結果を配列にして出力
HIT_DATA** CHitBox::SearchElementHit(int element,int point)
{
	SortHitBox();
	memset(&(*m_hit_search_data),0x00,sizeof(HIT_DATA*)*MAX_HITS);
	for(int i=0;i<m_hit_count;i++)
		if(m_hit_data[i].o!=NULL)
			if(m_hit_data[i].e==element)
				if(m_hit_data[i].p==point)
					 m_hit_search_data[i]=&m_hit_data[i];
	if(m_hit_count==0)
	{
		return nullptr;
	}
	else
	{
		return m_hit_search_data;
	}
}

//当たっている情報の距離ソート
void CHitBox::SortHitBox()
{
	for(int i=0;i<m_hit_count;i++)
	{
		for(int j=i;j<m_hit_count;j++)
		{
			float si= ( m_hit_data[i].o == nullptr ) ? HIT_LONG_OUT :  m_hit_data[i].s ;
			float sj= ( m_hit_data[j].o == nullptr ) ? HIT_LONG_OUT :  m_hit_data[j].s ;
			if(si > sj)
			{
				HIT_DATA w;
				w = m_hit_data[i];
				m_hit_data[i] = m_hit_data[j];
				m_hit_data[j] = w;
			}
		}
	}
}

//-----------------------------------
//コンストラクタ
void CHitBoxManager::Init()
{
	m_ListHitBox=new list<shared_ptr<CHitBox>>;
}
//デストラクタ
void CHitBoxManager::Delete()
{
	DeleteAllListData();
	delete m_ListHitBox;
}

//自分のアドレスを持つヒットボックスを返すメソッド
CHitBox* CHitBoxManager::GetHitBox(void* t)
{
	  for(auto itr = m_ListHitBox->begin() ; itr !=m_ListHitBox->end() ; itr++ )
	{
		if( (*itr).get()->GetMyObj() == t )
		{
			return (*itr).get();
		}
	} 
	return nullptr;
	
}

//ヒットボックスの登録メソッド
void CHitBoxManager::SetHitBox(void* t,float x,float y,float w,float h,int e,int n,int p)
{
	shared_ptr<CHitBox> ptr_box(new CHitBox());
	ptr_box->SetPos(x,y,h,w);
	ptr_box->SetStatus(e,n,p);
	ptr_box->SetObj(t);
	ptr_box->SetInvincibility(false);
	m_ListHitBox->push_front(ptr_box);		//データ登録
	return ;
}

//ヒットボックスの削除メソッド
void  CHitBoxManager::DeleteHitBox(void* t)
{
    for(auto itr = m_ListHitBox->begin() ; itr !=m_ListHitBox->end() ; itr++ )
	{
		if( (*itr).get()->GetMyObj() == t )
		{
			m_ListHitBox->erase(itr);	//データ削除
			return ;
		}
	} 

}

//リスト情報破棄
void CHitBoxManager::DeleteAllListData()
{
	m_ListHitBox->clear(); 
}

//衝突判定
void CHitBoxManager::AllHitCheck()
{

	for(auto itr_my =  m_ListHitBox->begin() ; itr_my != m_ListHitBox->end() ; itr_my++ )
	{	
		bool hit;

		//前回の内容を破棄
		(*itr_my)->m_hit_count=0;
		memset( &(*(*itr_my)->m_hit_data),0x00,sizeof(HIT_DATA)*MAX_HITS);

		if((*itr_my)->GetStatus()->i==true)
		{
			continue;
		}

		for(auto itr =  m_ListHitBox->begin() ; itr != m_ListHitBox->end() ; itr++ )
		{	

			if( (*itr)->GetStatus()->e != (*itr_my)->m_hit_status.e || (*itr_my)->GetStatus()->e == 0 )
			{
				if((*itr)->GetStatus()->i==true)
				{
					;
				}
				else if( itr != itr_my )
				{
					if( (*itr_my)->m_hit_count > MAX_HITS-1 )
					{
						continue;
					}

					hit = Hit(&(*itr_my)->m_hit_box , &(*itr)->m_hit_box , &(*itr_my)->m_hit_data[(*itr_my)->m_hit_count]);
					if(hit == true)
					{
						
						(*itr_my)->m_hit_data[(*itr_my)->m_hit_count].e  = (*itr)->GetStatus()->e;
						(*itr_my)->m_hit_data[(*itr_my)->m_hit_count].p  = (*itr)->GetStatus()->p;
						(*itr_my)->m_hit_data[(*itr_my)->m_hit_count].n  = (*itr)->GetStatus()->n;
						(*itr_my)->m_hit_data[(*itr_my)->m_hit_count].o  = (*itr)->GetMyObj();		
						(*itr_my)->m_hit_count++;
						
					}
				}
			}
		}
	}
}


//衝突判定メソッド
//aがｂのどこに当たっているか
bool CHitBoxManager:: Hit(HIT_BOX* a, HIT_BOX* b, HIT_DATA* hit)
{
	//衝突判定
	if( 
		( a->x + a->w > b->x ) && ( a->x < b->x + b->w ) &&
		( a->y + a->h > b->y ) && ( a->y < b->y + b->h ) 
	)
	{
		//どこに当たっているかチェックを行い角度を返す
		float pa_x,pa_y,pb_x,pb_y;
		float r;
		pa_x = a->x + ( a->w / 2.0f );	pa_y = a->y + ( a->h / 2.0f );
		pb_x = b->x + ( b->w / 2.0f );	pb_y = b->y + ( b->h / 2.0f ); 
	
		r =atan2(pb_y-pa_y , pb_x-pa_x );
		hit->r = r * 180.0f / 3.14f; 

		if(hit->r <= 0.0f)
			hit->r = abs(r * 180.0f / 3.14f); 
		else
			hit->r = 360.0f-abs(r * 180.0f / 3.14f); 
		
		//三平方の定理から距離を図る
		hit->s =sqrt((float)( pb_x - pa_x )*( pb_x - pa_x ) + ( pb_y - pa_y )*( pb_y - pa_y ) );  
		return true; 
	}

	return false ; 
}

//当たり判定描画メソッド
void  CHitBoxManager::DrawHitBox()
{
	float col[4]={0.5f,0.0f,0.0f,0.2f};
	
	// イタレーター
    for(auto itr =m_ListHitBox->begin() ; itr != m_ListHitBox->end() ; itr++ )
	{
		if(		(*itr)->GetStatus()->e==0)	{ col[0]=0.5f;col[1]=0.5f;col[2]=1.0f; }
		else if((*itr)->GetStatus()->e==1)	{ col[0]=0.5f;col[1]=1.0f;col[2]=0.3f; }
		else if((*itr)->GetStatus()->e==2)  { col[0]=1.0f;col[1]=0.5f;col[2]=0.3f; }
		else if((*itr)->GetStatus()->e==3)	{ col[0]=0.3f;col[1]=1.0f;col[2]=0.5f; }
		else if((*itr)->GetStatus()->e==4)  { col[0]=0.3f;col[1]=1.0f;col[2]=0.5f; }
		else if((*itr)->GetStatus()->e==5)	{ col[0]=1.0f;col[1]=1.0f;col[2]=1.0f; }
		else if((*itr)->GetStatus()->e==6)	{ col[0]=1.0f;col[1]=0.0f;col[2]=0.0f; }
		else if((*itr)->GetStatus()->e==7)  { col[0]=0.0f;col[1]=1.0f;col[2]=0.0f; }
		else if((*itr)->GetStatus()->e==8)	{ col[0]=0.0f;col[1]=0.0f;col[2]=1.0f; }
		else if((*itr)->GetStatus()->e==9)	{ col[0]=0.0f;col[1]=0.0f;col[2]=0.0f; }
		else if((*itr)->GetStatus()->e==10)	{ col[0]=1.0f;col[1]=1.0f;col[2]=1.0f; }
		else								{ col[0]=0.5f;col[1]=0.5f;col[2]=0.5f; }
		
		//当たり判定描画
		CDrawTexture::DrawHitBox(
			(*itr)->GetHitBox()->x,
			(*itr)->GetHitBox()->y,
			(*itr)->GetHitBox()->h,
			(*itr)->GetHitBox()->w,
			col
		);

	}
}
