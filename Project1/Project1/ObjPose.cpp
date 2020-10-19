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
	select_num = 1;
	keyflag = true;

	m_ani_time = 0.0f;
	m_ani_max = 8.0f;
}

//�A�N�V����
void CObjPose::Action()
{
	//�R���g���[���[�p---------------------------------------
	if (Input::GetConButtons(0, GAMEPAD_START))
	{
		stay_flag = true;
	}
	if (stay_flag == true)
	{
		if (Input::GetVKey('Q') == true)
		{
			stay_flag = false;
		}
		if (Input::GetConButtons(0, GAMEPAD_DPAD_UP) && keyflag == true && select_num > 1 && select_num <= 3)
		{
			keyflag = false;
			select_num--;
		}
		if (Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) && keyflag == true && select_num >= 1 && select_num < 3)
		{
			keyflag = false;
			select_num++;
		}
		if (Input::GetConButtons(0, GAMEPAD_A) && keyflag == true == true)
		{
			keyflag = false;
			switch (select_num)
			{
			case 1:
				stay_flag = false;
				break;
			case 2:
				Scene::SetScene(new CSceneStageSelect);
				break;
			case 3:
				Scene::SetScene(new CSceneTitle);
				break;
			}

		}
	}

	//�L�[�{�[�h�p-------------------------------------------
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
		if (Input::GetVKey(VK_UP) == true &&keyflag==true && select_num>1 &&select_num<=3)
		{
			keyflag = false;
			select_num--;
		}
		if (Input::GetVKey(VK_DOWN) == true && keyflag == true &&select_num>=1 && select_num<3)
		{
			keyflag = false;
			select_num++;
		}
		if (Input::GetVKey(VK_RETURN) && keyflag == true == true)
		{
			switch (select_num)
			{
			case 1:
				stay_flag = false;
				break;
			case 2:
				Scene::SetScene(new CSceneStageSelect);
				break;
			case 3:
				Scene::SetScene(new CSceneTitle);
				break;
			}

		}
	}


	if (Input::GetVKey(VK_DOWN) == false && Input::GetVKey(VK_UP) == false &&
		Input::GetVKey('Z') == false && keyflag == false && Input::GetConButtons(0, GAMEPAD_A) == false &&
		Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) == false && Input::GetConButtons(0, GAMEPAD_DPAD_UP) == false)
	{
		keyflag = true;
	}

	m_ani_time += 0.2f;
	if (m_ani_time >= 8.0f)
	{
		m_ani_time = 0.0f;
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
		src.m_right = 505.0f;
		src.m_bottom = 305.0f;


		//�\���ʒu�̐ݒ�
		dst.m_top = 120.0f;
		dst.m_left = 320.0f;
		dst.m_right = 960.0f;
		dst.m_bottom = 580.0f;

		//�`��
		Draw::Draw(3, &src, &dst, c, 0.0f);

		//�`��J���[���
		float c2[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src2; //�`�挳�؂���ʒu
		RECT_F dst2; //�`���\���ʒu
		//�؂���ʒu�̐ݒ�
		src2.m_top = 0.0f;
		src2.m_left = 0.0f;
		src2.m_right = 64.0f;
		src2.m_bottom = 64.0f;

		if (select_num == 1)
		{
			//�\���ʒu�̐ݒ�
			dst2.m_top = 230.0f;
			dst2.m_left = 350.0f + m_ani_time;
			dst2.m_right = 414.0f + m_ani_time;
			dst2.m_bottom = 294.0f;
		}
		if (select_num == 2)
		{
			//�\���ʒu�̐ݒ�
			dst2.m_top = 360.0f;
			dst2.m_left = 350.0f + m_ani_time;
			dst2.m_right = 414.0f + m_ani_time;
			dst2.m_bottom = 426.0f;
		}
		
		if (select_num == 3)
		{
			//�\���ʒu�̐ݒ�
			dst2.m_top = 480.0f;
			dst2.m_left = 350.0f + m_ani_time;
			dst2.m_right = 414.0f + m_ani_time;
			dst2.m_bottom = 546.0f;
		}
		//�`��
		Draw::Draw(4, &src2, &dst2, c2, 0.0f);
	}
}