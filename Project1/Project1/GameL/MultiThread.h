#pragma once
//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0) 

#include <thread>
#include <vector>
#include <atomic>
#include <Windows.h>


using namespace std;

namespace GameL
{
	typedef class CMultiThread
	{
		public:
			static void Init(void(*game_sub)());
			static void Delete();
			static void End();
			static bool GetEnd();
		private:

			static unsigned __stdcall GameThread(void *p);	//ゲームスレッド用メソッド
			
			static thread*		 m_handoru_game;			//ゲームスレッド
	}GameLoop;
};