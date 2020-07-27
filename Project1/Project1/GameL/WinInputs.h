#pragma once
#include <Windows.h>

namespace GameL
{
	//�Q�[���p�b�g�{�^���萔
	static	constexpr auto GAMEPAD_DPAD_UP{ 0x0001 };
	static	constexpr auto GAMEPAD_DPAD_DOWN{ 0x0002 };
	static	constexpr auto GAMEPAD_DPAD_LEFT{ 0x0004 };
	static	constexpr auto GAMEPAD_DPAD_RIGHT{ 0x0008 };
	static	constexpr auto GAMEPAD_START{ 0x0010 };
	static	constexpr auto GAMEPAD_BACK{ 0x0020 };
	static	constexpr auto GAMEPAD_LEFT_THUMB{ 0x0040 };
	static	constexpr auto GAMEPAD_RIGHT_THUMB{ 0x0080 };
	static	constexpr auto GAMEPAD_LEFT_SHOULDER{ 0x0100 };
	static	constexpr auto GAMEPAD_RIGHT_SHOULDER{ 0x0200 };
	static	constexpr auto GAMEPAD_A{ 0x1000 };
	static	constexpr auto GAMEPAD_B{ 0x2000 };
	static	constexpr auto GAMEPAD_X{ 0x4000 };
	static	constexpr auto GAMEPAD_Y{ 0x8000 };
	typedef class CWinInputs
	{
		public :
			static bool WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam);//�E�B���h�E�v���W�[�V���[�R�[���o�b�N�֐��o�^�p
			static bool GetVKey(int v_key);
			static bool GetMouButtonL();
			static bool GetMouButtonR();
		
			static int GetPosX();
			static int GetPosY();

			static int UpdateXControlerConnected();

			static void Refresh();
			static void Init();
		
		static	float GetConVecStickLX(int id);				//�A�i���OL�����L�[���擾Y �߂�l(-1.0�`1.0)
		static	float GetConVecStickLY(int id);				//�A�i���OL�����L�[���擾X �߂�l(-1.0�`1.0)
		static	float GetConVecStickRX(int id);				//�A�i���OR�����L�[���擾Y �߂�l(-1.0�`1.0)
		static	float GetConVecStickRY(int id);				//�A�i���OR�����L�[���擾X �߂�l(-1.0�`1.0)
		static	bool  GetConButtons(int id, int button);	//�R���g���[���̃{�^�����擾
		static	void  SetVibration(int id, int wL, int wR);	//�o�C�u���[�V�����ݒ�

		private:
			static int   m_x,m_y;		//�}�E�X���W
			static bool  m_ButtonL;		//�}�E�X�N���b�N
			static bool  m_ButtonR;
			static BYTE m_KeyBoard[256];//�L�[�{�[�h�z��
	}Input;
};