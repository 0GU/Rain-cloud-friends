#pragma comment(lib,"xinput.lib ")

#include <Windows.h>
#include <XInput.h>

#include "WinInputs.h"


using namespace GameL;


int   CWinInputs::m_x,CWinInputs::m_y;		//�}�E�X���W
bool  CWinInputs::m_ButtonL;				//�}�E�X�N���b�N
bool  CWinInputs::m_ButtonR;
BYTE  CWinInputs::m_KeyBoard[256];			//�L�[�{�[�h�z��


constexpr auto MAX_CONTROLERS{ 4 };
constexpr auto THRESHOLD{ 32767.0f }; //�W���C�X�e�B�b�N�̂������l

	//XBOX360��p�R���g���[���[�X�e�[�^�X
struct CONTROLER_STATE
{
	XINPUT_STATE	m_state;		//�R���g���[���[�X�e�[�^�X
	bool			m_bConnected;	//�ڑ����
};								  
CONTROLER_STATE GAME_PAD[MAX_CONTROLERS];//XBOX360��p�R���g���[���[�p�b�g

void CWinInputs::Init()
{
	m_x=0;
	m_y=0;
	m_ButtonL=false;
	m_ButtonR=false;
	memset(m_KeyBoard,0x00,sizeof(m_KeyBoard));

}

bool CWinInputs::WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam)
{
	if(*uMsg== WM_MOUSEMOVE )
	{
		POINT point={ LOWORD(*lParam), HIWORD((*lParam))};
		
		m_x = point.x;   // �J�[�\���� x ���W
		m_y = point.y;   // �J�[�\���� y ���W
		return true;
	}
	else if(*uMsg==WM_LBUTTONDOWN)
	{
		m_ButtonL=true;
	}
	else if(*uMsg==WM_LBUTTONUP)
	{
		m_ButtonL=false;
	}
	else if(*uMsg==WM_RBUTTONDOWN)
	{
		m_ButtonR=true;
	}
	else if(*uMsg==WM_RBUTTONUP)
	{
		m_ButtonR=false;
	}
	return false;
}

bool CWinInputs:: GetVKey(int v_key)
{	
	if(GetAsyncKeyState(v_key)&0x8000)
		return true;
	else
		return false;
	return false;
}
bool CWinInputs::GetMouButtonL()
{
	return m_ButtonL;
}
bool CWinInputs::GetMouButtonR()
{
	return m_ButtonR;
}

int CWinInputs:: GetPosX()
{
	return m_x;
}

int CWinInputs::GetPosY()
{
	return m_y;
}
//�R���g���[���̐ڑ���Ԃ̊m�F
void CWinInputs::UpdateXControlerConnected()
{
	DWORD dwResult;
	for (DWORD i = 0; i < MAX_CONTROLERS; i++)
	{
		dwResult = XInputGetState(i, &GAME_PAD[i].m_state);
		if (dwResult == ERROR_SUCCESS)
			GAME_PAD[i].m_bConnected = true;
		else
			GAME_PAD[i].m_bConnected = false;
	}


}



//�A�i���O�����L�[���擾
float CWinInputs::GetConVecStickLX(int id)
{
	if (GAME_PAD[id].m_bConnected == true)
	{
		float w = ((float)GAME_PAD[id].m_state.Gamepad.sThumbLX) / THRESHOLD;
		if (w < -1.0f) w = -1.0f;
		if (w > +1.0f) w = +1.0f;
		return w;
	}
	return 0;
}

float CWinInputs::GetConVecStickLY(int id)
{
	if (GAME_PAD[id].m_bConnected == true)
	{
		float w = ((float)GAME_PAD[id].m_state.Gamepad.sThumbLY) / THRESHOLD;
		if (w < -1.0f) w = -1.0f;
		if (w > +1.0f) w = +1.0f;
		return w;
	}
	return 0;
}

float CWinInputs::GetConVecStickRX(int id)
{
	if (GAME_PAD[id].m_bConnected == true)
	{
		float w = ((float)GAME_PAD[id].m_state.Gamepad.sThumbRX) / THRESHOLD;
		if (w < -1.0f) w = -1.0f;
		if (w > +1.0f) w = +1.0f;
		return w;
	}
	return 0;
}

float CWinInputs::GetConVecStickRY(int id)
{
	if (GAME_PAD[id].m_bConnected == true)
	{
		float w = ((float)GAME_PAD[id].m_state.Gamepad.sThumbRY) / THRESHOLD;
		if (w < -1.0f) w = -1.0f;
		if (w > +1.0f) w = +1.0f;
		return w;
	}
	return 0;
}


//�R���g���[���̃{�^�����擾
bool CWinInputs::GetConButtons(int id, int button)
{
	if (GAME_PAD[id].m_bConnected == true)
	{
		if (GAME_PAD[id].m_state.Gamepad.wButtons & button)
		{
			return true;
		}
	}

	return false;
}

//�o�C�u���[�V�����ݒ�
void CWinInputs::SetVibration(int id, int wL, int wR)
{
	if (GAME_PAD[id].m_bConnected == true)
	{
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = wL; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = wR; // use any value between 0-65535 here
		XInputSetState(id, &vibration);
	}
}
