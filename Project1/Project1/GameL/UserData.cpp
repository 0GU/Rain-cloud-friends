#include <stdio.h>
#include <locale.h>
#include "UserData.h"
using namespace GameL;

#define SEVE_NAME (L"user_data")
void* CUserData::m_data;		//ユーザー情報
int   CUserData::m_data_size;	//ユーザー情報サイズ


void* CUserData::GetData()
{
	return m_data;
}

void CUserData::Init(void *data,int size)
{
	setlocale( LC_CTYPE, "jpn" );
	m_data=data;
	m_data_size=size;
}

void CUserData::Delete()
{
	m_data=nullptr;
	m_data_size=0;
}

void CUserData::Open()
{
	FILE* fp;
	_wfopen_s(&fp,SEVE_NAME,L"r");
	if(fp==nullptr)
	{
		memset(m_data,0x00,m_data_size);
		return ;
	}
	fread(m_data,m_data_size,1,fp);
	fclose(fp);
}

void CUserData::Seve()
{
	FILE* fp;
	_wfopen_s(&fp,SEVE_NAME,L"w");
	if(fp==nullptr) return ;
	fwrite(m_data,m_data_size,1,fp);
	fclose(fp);

}

unique_ptr<wchar_t> CUserData::ExternalDataOpen(const wchar_t* file_name,int* size)
{
	
	int  s=0;
	wint_t c;
	unique_ptr<wchar_t> str;
	FILE* fp;
	_wfopen_s(&fp,file_name,L"rt,ccs=Unicode");//文字コードをUnicode指定
	if(fp==nullptr) return nullptr;

	//ファイルのサイズ取得
	do
	{
		c=fgetwc(fp);
		if( c == WEOF )
		{
			break;
		}
		else
		{
			s++;
		}
		
	}while(1);

	if(s==0)
	{
		fclose(fp);
		return nullptr;
	}

	fseek(fp,0, SEEK_SET);
	//ファイル情報の大きさ
	str.reset(new wchar_t[s+1]);
	fread(str.get(),sizeof(wchar_t)*s,1,fp);
	str.get()[s]=L'\0';
	fclose(fp);

	*size=s+1;
	return move(str);
}