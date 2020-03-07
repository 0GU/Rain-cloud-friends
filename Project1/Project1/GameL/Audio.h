#pragma once
//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

#include <XAudio2.h>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


namespace GameL
{
	enum SOUND_TYPE
	{
		EFFECT,			//効果音			（単発音）
		BACK_MUSIC,		//バックミュージック (ループ)
	};


	//サウンドデータ
	struct AudioData
	{
		//サウンド情報(RIFFファイルフォーマットを読み取り用)
		unsigned int   Size;					//サウンドサイズ
		unsigned char* pWave;					//wave先頭アドレスポインタ
		unsigned char* pData;					//波状情報アドレスポインタ
		//Audioデータ
		IXAudio2SourceVoice**	m_pSourceVoice;     //サウンドボイスインターフェース
		IXAudio2SubmixVoice*	m_pSFXSubmixVoice;  //サブミクスインターフェース
		SOUND_TYPE				m_type;				//サウンドタイプ
		XAUDIO2_BUFFER			m_sound_buffer;		//サウンドバッファ
		float					m_volume;			//ボリューム情報
	};

	//オーディオクラス
	//Wave形式の読み込みとサウンド再生・管理を行う
	typedef class CAudio
	{
		public:
			static void Init(int max_audio);			//初期化
			static void Delete();						//クラス破棄
			static void LoadAudio(int id,const wchar_t* name,SOUND_TYPE type);	//サウンドボイスデータ登録
			static void DeleteAudio();					//サウンド情報破棄
			static void Start(int id);					//スタート	
			static void Stop(int id);					//ストップ
			static float Volume(float t,int id);		//個々のサウンドボリューム変更
			static float VolumeMaster(float t);			//全体のサウンドボリューム変更

		private:
			static IXAudio2*						m_pXAudio2;				//XAudio2オブジェクト
			static IXAudio2MasteringVoice*			m_pMasteringVoice;		//マスターボリューム
			static vector<shared_ptr<AudioData>>	m_AudioData;			//サウンドデータ
			static int		m_aud_max;					//オーディオ最大数
			static float	m_volume;					//マスターボリューム値
			//waveファイル読み込み
			static WORD GetWord(const unsigned char* pData);
			static DWORD GetDword(const unsigned char* pData);
			static void FindChunk(const unsigned char* pData,const char* pChunckName,unsigned* Size,unsigned char** ppData);
	}Audio;
};
