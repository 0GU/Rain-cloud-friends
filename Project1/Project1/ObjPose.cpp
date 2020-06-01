// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjPose.h"

CObjPose::CObjPose(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjPose::Init()
{
	delete_flag = false;
	stay_flag = false;
}

//�A�N�V����
void CObjPose::Action()
{
	if (Input::GetVKey('M') == true)
	{
		stay_flag = true;
	}
	if (stay_flag == true)
	{
		if (Input::GetVKey('Q') == true)
		{
			stay_flag = false;
		}
	}
}

//�h���[
void CObjPose::Draw()
{
	if (stay_flag == true)
	{
		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src; //�`�挳�؂���ʒu
		RECT_F dst; //�`���\���ʒu

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 40.0f;


		//�\���ʒu�̐ݒ�
		dst.m_top = 180.0f;
		dst.m_left = 320.0f;
		dst.m_right = 960.0f;
		dst.m_bottom = 640.0f;

		//�`��
		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
}