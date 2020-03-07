#include "Audio.h"

#define SCENE_AUDIO_EFFCT_MAX	(16)					//効果音の同時出力最大数
#define HRESULT_CHECK(hr) if(FAILED(hr)){ _asm{int 3} }	//簡単なエラーチェックマクロ
#define SAFE_RESET(p){ if (p) { (p).reset(nullptr);}  }


using namespace GameL;

IXAudio2*						CAudio::m_pXAudio2;			//XAudio2オブジェクト
IXAudio2MasteringVoice*			CAudio::m_pMasteringVoice;	//マスターボリューム
vector<shared_ptr<AudioData>>	CAudio::m_AudioData;		//サウンドデータ	
int								CAudio::m_aud_max;			//オーディオ最大数
float							CAudio::m_volume;			//マスターボリューム値

//エラーサウンド変数
bool g_is_error_sound;

//初期化
void CAudio::Init(int max_audio)
{
	m_aud_max=max_audio;
	m_volume=1.0f;
	unsigned XAudio2CreateFlags = 0;
	

	XAudio2Create(&m_pXAudio2, XAudio2CreateFlags);

	//マスターボイス作成
	m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);

	//マスターボイスエラーチェック
	g_is_error_sound = false;
	if (m_pMasteringVoice == nullptr)
	{
		MessageBox(0, L"ｻｳﾝﾄﾞﾊｰﾄﾞ系のｻﾎﾟｰﾄに問題があるため、音がなりません", NULL, MB_OK);
		g_is_error_sound = true;
		return;
	}

	//メモリ作成
	m_AudioData.reserve(m_aud_max); //配列の許容量設定
	m_AudioData.resize( m_aud_max);	//配列の要素数設定
	
	//オーディオデータ作成
	for(int i=0;i<m_aud_max;i++)
	{
		//各オーディオメモリ作成	
		m_AudioData[i].reset(new AudioData);
		
		m_AudioData[i]->pData=nullptr;
		m_AudioData[i]->pWave=nullptr;
		m_AudioData[i]->Size=0;
		m_AudioData[i]->m_volume=1.0f;

		//サウンドインターフェースメモリ作成
		m_AudioData[i]->m_pSourceVoice = new IXAudio2SourceVoice*[SCENE_AUDIO_EFFCT_MAX];
		for(int j=0 ; j < SCENE_AUDIO_EFFCT_MAX ; j++ )
		{
			m_AudioData[i]->m_pSourceVoice[j]=nullptr;
		}

		//ミックスボイス作成
		m_pXAudio2->CreateSubmixVoice(&m_AudioData[i]->m_pSFXSubmixVoice,1,44100,0,0,0,0);
	}

	//マスターボリューム
	m_pMasteringVoice->SetVolume(1.0f,0);
}

//クラス破棄
void CAudio::Delete()
{
	//マスターボイスエラーチェック
	if (g_is_error_sound == true)
	{
		m_pXAudio2->Release();
		return;
	}

	//サウンド破棄
	DeleteAudio();

	//サウンドメモリ破棄
	for(int i=0 ; i < m_aud_max ; i++ )
	{
		//サウンドインターフェース破棄
		delete [] m_AudioData[i]->m_pSourceVoice;

		//ミックスサウンド破棄
		m_AudioData[i]->m_pSFXSubmixVoice->DestroyVoice();
	}
	
	//オーディオベクター破棄
	m_AudioData.clear();
	m_AudioData.shrink_to_fit();


	//マスターボイス　・XAudio2破棄
	m_pMasteringVoice->DestroyVoice();
	
	m_pXAudio2->Release();
}

//各ボリューム変更
float CAudio::Volume(float t,int id)
{
	//マスターボイスエラーチェック
	if (g_is_error_sound == true)
	{
		return 0.0f;
	}

	if(id<0)		 return -1.0f;
	if(id>m_aud_max) return -1.0f;
	m_AudioData[id]->m_volume+=t;
	if(m_AudioData[id]->m_volume<0.0f)  m_AudioData[id]->m_volume= 0.0f; 
	if(m_AudioData[id]->m_volume>10.0f) m_AudioData[id]->m_volume=10.0f; 

	m_AudioData[id]->m_pSFXSubmixVoice->SetVolume(m_AudioData[id]->m_volume,0);
	return m_AudioData[id]->m_volume;
}

//マスターボリューム変更
float CAudio::VolumeMaster(float t)
{	
	//マスターボイスエラーチェック
	if (g_is_error_sound == true)
	{
		return 0.0f;
	}

	m_volume+=t;
	if(m_volume< 0.0f) m_volume= 0.0f; 
	if(m_volume>10.0f) m_volume=10.0f; 
	m_pMasteringVoice->SetVolume(m_volume,0);
	return m_volume;
}

//サウンド情報破棄
void CAudio::DeleteAudio()
{
	//マスターボイスエラーチェック
	if (g_is_error_sound == true)
	{
		return;
	}

	for(int i=0 ; i < m_aud_max ; i++ )
	{
		//インターフェース破棄
		for(int j=0 ; j < SCENE_AUDIO_EFFCT_MAX ; j++ )
		{
			if(m_AudioData[i]->m_pSourceVoice[j]!=nullptr)
			{
				m_AudioData[i]->m_pSourceVoice[j]->Stop();
				m_AudioData[i]->m_pSourceVoice[j]->FlushSourceBuffers();
				m_AudioData[i]->m_pSourceVoice[j]->DestroyVoice();
				m_AudioData[i]->m_pSourceVoice[j]=nullptr;
			}
		}

		//サウンドデータ破棄
		if(m_AudioData[i]->pWave != nullptr)
		{
			delete []m_AudioData[i]->pWave;
			m_AudioData[i]->pWave=nullptr;
		}
	}
}

//スタート
void CAudio::Start(int id)
{
	//マスターボイスエラーチェック
	if (g_is_error_sound == true)
	{
		return;
	}

	if(id<0)		 return ;
	if(id>m_aud_max) return ;

	if(m_AudioData[id]->m_type==BACK_MUSIC)
	{
		//ループサウンド
		//ループスタートの際、破棄する
		Stop(id);
		m_AudioData[id]->m_pSourceVoice[0]->SubmitSourceBuffer(&m_AudioData[id]->m_sound_buffer);
		m_AudioData[id]->m_pSourceVoice[0]->Start();
		return ;
	}
	else
	{
		//エフェクトサウンド
		for(int i=0 ; i<(SCENE_AUDIO_EFFCT_MAX<<1) ; i++ )
		{
			//サウンド配列二周の間で使用されていない場所確認する
			int count = i%SCENE_AUDIO_EFFCT_MAX;

			//サウンドの状態を取得
			XAUDIO2_VOICE_STATE stats;
			m_AudioData[id]->m_pSourceVoice[count]->GetState(&stats);

			//サウンドバッファが空かどうかチェック
			if( stats.BuffersQueued == 0 )
			{
				//サウンドインターフェースにサウンドを登録してサウンドを鳴らす
				m_AudioData[id]->m_pSourceVoice[count]->SubmitSourceBuffer(&m_AudioData[id]->m_sound_buffer);
				m_AudioData[id]->m_pSourceVoice[count]->Start();
				return ;
			}
		}
		//インターフェースが全て使われていた場合　最終インターフェースで流れてるサウンドを強制破棄して、サウンド登録して鳴らす
		m_AudioData[id]->m_pSourceVoice[SCENE_AUDIO_EFFCT_MAX-1]->Stop();
		m_AudioData[id]->m_pSourceVoice[SCENE_AUDIO_EFFCT_MAX-1]->FlushSourceBuffers();
		m_AudioData[id]->m_pSourceVoice[SCENE_AUDIO_EFFCT_MAX-1]->SubmitSourceBuffer(&m_AudioData[id]->m_sound_buffer);
		m_AudioData[id]->m_pSourceVoice[SCENE_AUDIO_EFFCT_MAX-1]->Start();
		return ;
	}
}
//ストップ
void CAudio::Stop(int id)
{
	//マスターボイスエラーチェック
	if (g_is_error_sound == true)
	{
		return;
	}

	if(id<0)		 return ;
	if(id>m_aud_max) return ;

	for(int i=0 ; i < SCENE_AUDIO_EFFCT_MAX ; i++ )
	{
		m_AudioData[id]->m_pSourceVoice[i]->Stop();
		m_AudioData[id]->m_pSourceVoice[i]->FlushSourceBuffers();
	}
}

//サウンドボイスデータ登録
void CAudio::LoadAudio(int id ,const wchar_t* name,SOUND_TYPE type)
{
	//マスターボイスエラーチェック
	if (g_is_error_sound == true)
	{
		return;
	}

	if(id<0)		 return ;
	if(id>m_aud_max) return ;

	//インターフェース破棄
	if(m_AudioData[id]->m_pSourceVoice[0]!=nullptr)
	{
		for(int j=0 ; j < SCENE_AUDIO_EFFCT_MAX ; j++ )
		{
			if(m_AudioData[id]->m_pSourceVoice[j]!=nullptr)
			{
				m_AudioData[id]->m_pSourceVoice[j]->Stop();
				m_AudioData[id]->m_pSourceVoice[j]->FlushSourceBuffers();
				m_AudioData[id]->m_pSourceVoice[j]->DestroyVoice();
				m_AudioData[id]->m_pSourceVoice[j]=nullptr;
			}
		}

		//サウンドデータ破棄
		if(m_AudioData[id]->pWave != nullptr)
			delete []m_AudioData[id]->pWave;
	}

	//サウンドタイプセット
	m_AudioData[id]->m_type=type;
	


	//waveファイルのメモリ内に展開
	ifstream ifs(name,ios::in | ios::binary);
	if(!ifs)	return;

	unsigned int Size = 0;
	//展開
	ifs.seekg(0,ios::end);
	Size = static_cast<unsigned>( ifs.tellg() );
	ifs.seekg(0,ios::beg);
	m_AudioData[id]->pWave = new unsigned char[Size];

	ifs.read(reinterpret_cast<char*>(m_AudioData[id]->pWave),Size);
	ifs.close();

	//RIFFファイル解析
	//wave情報
	WAVEFORMATEX WaveformatEx = {0};
	FindChunk(m_AudioData[id]->pWave,"fmt",&m_AudioData[id]->Size,&m_AudioData[id]->pData);
	
	//wave情報分アドレスをずらして波状データに移動
	unsigned char* p = m_AudioData[id]->pData;
	WaveformatEx.wFormatTag =      GetWord(p);  p += sizeof(WORD);
	WaveformatEx.nChannels =       GetWord(p);  p += sizeof(WORD);
	WaveformatEx.nSamplesPerSec  = GetDword(p); p += sizeof(DWORD);
	WaveformatEx.nAvgBytesPerSec = GetDword(p); p += sizeof(DWORD);
	WaveformatEx.nBlockAlign =     GetWord(p);  p += sizeof(WORD);
	WaveformatEx.wBitsPerSample =  GetWord(p);  p += sizeof(WORD);
	WaveformatEx.cbSize =          GetWord(p);  p += sizeof(WORD);
	
	//波本体のデータ
	FindChunk(m_AudioData[id]->pData,"data",&m_AudioData[id]->Size,&m_AudioData[id]->pData);

	//再生のためのインターフェース生成
	XAUDIO2_SEND_DESCRIPTOR SFXSend = {1, m_AudioData[id]->m_pSFXSubmixVoice};
	XAUDIO2_VOICE_SENDS SFXSendList = {1, &SFXSend};
	for (int i = 0; i < SCENE_AUDIO_EFFCT_MAX; i++)
	{
		//サブミクスボイスをセット
		XAUDIO2_SEND_DESCRIPTOR data;
		data.Flags = 0;
		data.pOutputVoice = m_AudioData[id]->m_pSFXSubmixVoice;
		XAUDIO2_VOICE_SENDS SFXSendList;
		memset(&SFXSendList, 0x00, sizeof(XAUDIO2_VOICE_SENDS));
		SFXSendList.SendCount = 1;
		SFXSendList.pSends = &data;
		//ソースボイス作成
		m_pXAudio2->CreateSourceVoice(&m_AudioData[id]->m_pSourceVoice[i],
			&WaveformatEx, 0U, 2.0F, 0, &SFXSendList, 0);
	}
	//サウンドバッファをソースボイスキューに作成
	memset(&m_AudioData[id]->m_sound_buffer,0x00,sizeof(m_AudioData[id]->m_sound_buffer));
	m_AudioData[id]->m_sound_buffer.AudioBytes		=  m_AudioData[id]->Size;
	m_AudioData[id]->m_sound_buffer.pAudioData		=  reinterpret_cast<BYTE*>(m_AudioData[id]->pData);
	m_AudioData[id]->m_sound_buffer.Flags			=  XAUDIO2_END_OF_STREAM;

	if(type==EFFECT)
		m_AudioData[id]->m_sound_buffer.LoopCount	=  0;
	else
		m_AudioData[id]->m_sound_buffer.LoopCount	=  XAUDIO2_LOOP_INFINITE;

	//ボリューム設定
	m_AudioData[id]->m_volume=1.0f;
	m_AudioData[id]->m_pSFXSubmixVoice->SetVolume(m_volume,0);
}

//waveファイル読み込み
WORD  CAudio::GetWord(const unsigned char* pData)
{
	WORD Value = pData[0] | pData[1] << 8;
	return Value;
}
DWORD CAudio::GetDword(const unsigned char* pData)
{
	DWORD Value = pData[0] | pData[1] << 8 | pData[2] << 16 | pData[3] << 24;
	return Value;
}

//かならずチャンクは見つかるとして簡略化
void CAudio:: FindChunk(const unsigned char* pData,const char* pChunckName,unsigned* Size,unsigned char** ppData)
{
	const unsigned CHUNKNAME_LENGTH = std::strlen(pChunckName);
	while(true)
	{
		bool IsFind = true;
		for(unsigned i = 0 ; i < CHUNKNAME_LENGTH ; ++i)
		{
			if(pData[i] != pChunckName[i])
			{
				IsFind = false;
				break;
			}
		}
		if(IsFind)
		{
			*Size = pData[4+0] | pData[4+1] << 8 | pData[4+2] << 16 | pData[4+3] << 24;
			*ppData = const_cast<unsigned char*>(pData+8 );
			return ;
		}

		pData++;
	}
	return;
}
