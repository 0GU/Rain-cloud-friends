#pragma once
//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

#include <memory>
using namespace std;

namespace GameL
{
	//ユーザー・セーブ・シーン間受け渡しデータクラス
	typedef class CUserData
	{
		public :
			static void Init(void* data,int size);
			static void Delete();
			static void Open();
			static void Seve();
			static void* GetData();

			//ユーザーデータ以外の外部データ読み込み
			//全データ(文字列情報)を取得したメモリが返される
			//テキストエディタでUnicode指定　BOMチェック有りにしてください。
			static unique_ptr<wchar_t> ExternalDataOpen(const wchar_t* file_name,int* size);
		private:
			static void* m_data;		//ユーザー情報
			static int   m_data_size;	//ユーザー情報サイズ
	}Save;
};