#include "SceneObjManager.h"
using namespace GameL;

//ソート用クラス
class Pr
{
	public:
	bool operator()(const shared_ptr<CObj> x, const shared_ptr<CObj> y) const 
	{
		return x.get()->GetPrio()  <  y.get()->GetPrio();
	}
};

list<shared_ptr<CObj>>*		CSceneObjManager::m_ListData;	//ゲーム実行リスト
		
//---CObj-----------------------------------------------------
//コンストラクタ
CObj::CObj()
{
	m_prio=     0;
	m_name=    -1;
	m_status=true;
}

//優先順位変更
void CObj::SetPrio(unsigned int prio)
{
	m_prio=prio;
	CSceneObjManager::ResetPrio();
}

unsigned int CObj::GetPrio()
{
	return m_prio;
}

//オブジェクト名前ID変更
void CObj::SetName(int name)
{
	m_name=name;
}

int CObj::GetName()
{
	return m_name;
}

//オブジェクトの状態変更
void CObj::SetStatus(bool exe)
{
	m_status=exe;
}
bool CObj::GetStatus()
{
	return m_status; 
}
//------------------------------------------------------------


//初期化
void CSceneObjManager::Init()
{
	m_ListData= new list<shared_ptr<CObj>>;
}

//削除
void CSceneObjManager::Delete()
{
	m_ListData->clear(); 
	delete m_ListData;
}

//タスクデータ挿入（末端）メソッド
void CSceneObjManager:: InsertObj(CObj* obj,int name,unsigned int prio)
{
	if(obj == nullptr ) 
		return ;
	
	//オブジェクトの初期化メソッド起動
	obj->Init();

	//オブジェクトステータス登録
	obj->SetName(name);
	

	//データ登録
	unique_ptr<CObj> ptr_obj(obj);
	m_ListData->push_front(move(ptr_obj));

	obj->SetPrio(prio);

	return;
}

//オブジェクトリスト削除命令メソッド
void CSceneObjManager::ListDeleteSceneObj()
{
	for(auto itr = m_ListData->begin() ; itr != m_ListData->end() ; itr++ )
	{
		(*itr)->SetStatus(false);
	}
}

//アクション実行
void CSceneObjManager::ObjAction()
{
	//削除実行
	auto i = m_ListData->begin();
	while (i !=  m_ListData->end())
	{
		if (i->get()->GetStatus() == false)
		{
			i=m_ListData->erase(i);
		} 
		else
		{
			i++;
		}
	}

	//アクション実行
    for(auto itr =m_ListData->begin() ; itr !=m_ListData->end() ; itr++ )
	{
		if( (*itr)->GetStatus() == true )
		{
			(*itr)->Action();
		}
	}
}

//描画優先順位の再セット
void CSceneObjManager::ResetPrio()
{
	//描画優先順位リストソート//
	Pr pr;
	if(m_ListData->size()>=2)
	{
		m_ListData->sort(pr);
	}
}

//ドロー実行
void CSceneObjManager::ObjDraw()
{
	//描画実行
    for(auto itr = m_ListData->begin() ; itr != m_ListData->end() ; itr++ )
	{
		if( (*itr)->GetStatus() == true )
		{
			(*itr)->Draw(); 
		}
	}
}

//OBJ_NEMEからオブジェクト情報取得
CObj* CSceneObjManager::GetObj(int name)
{
    for(auto itr =m_ListData->begin() ; itr != m_ListData->end() ; itr++ )
	{
		if( (*itr)->GetName()== name )
			return (*itr).get(); 
	}

	return NULL;
}
