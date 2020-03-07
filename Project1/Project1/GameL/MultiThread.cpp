#include <process.h>
#include "MultiThread.h"


using namespace GameL;
atomic<bool>  execution;							//スレッド実行フラグ
thread*		  CMultiThread::m_handoru_game;			//ゲームスレッド


bool CMultiThread::GetEnd()
{
	return  execution.load(std::memory_order_acquire);
}

//初期化
void CMultiThread::Init( void(*game_sub)() )
{
	m_handoru_game = new thread(GameThread, (void *)game_sub);
	execution.store(true);
}

//削除
void CMultiThread::Delete()
{
	//スレッド終了フラグを立てる
	End();
	//スレッド終了確認
	m_handoru_game->join();
	delete m_handoru_game;

}

//ゲームスレッド停止メソッド
void CMultiThread::End()
{	
	execution.store(false);	
}

//ゲームスレッド用メソッド
unsigned __stdcall CMultiThread::GameThread(void *p)
{
	execution.store(true);
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	

	void (*sub)() = (void(*)()) p;
	

	//ゲームループ
	while(execution.load(std::memory_order_acquire))
	{
		sub();
	}

	CoUninitialize();//ＣＯＭ解除
    return 0;
}