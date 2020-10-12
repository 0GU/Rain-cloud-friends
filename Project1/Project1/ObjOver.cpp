// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjOver.h"

CObjOver::CObjOver(int stagenum)
{
	restart = stagenum;
}

//�C�j�V�����C�Y
void CObjOver::Init()
{
	//������
	selectnum = 1;
	selectnum_c = 1;
	keyflag = true;

	m_y1 = 0.0f;

	move_flag = false;
	scroll_flag = false;
	check_flag = false;
}

//�A�N�V����
void CObjOver::Action()
{
	//�R���g���[���[���쉼
	//m_con_num = Input::UpdateXControlerConnected();

	//����ʃX�N���[��
	if (scroll_flag == false)
	{
		m_y1 += 50.0f;
		if (m_y1 > 800.0f)
		{
			m_y1 = 800.0f;
			scroll_flag = true;
		}
	}

	//��������X�e�[�W�R�}���h------------------
	

	//�L�[�{�[�h�p------------------------------
	if (Input::GetVKey(VK_DOWN) == true && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);
		
		//�ʏ펞
		if (check_flag == false)
		{
			if (selectnum == 3)
			{
				;//�������Ȃ�
			}
			else
			{
				selectnum += 1;
			}
		}
		//�m�F���
		else
		{
			if (selectnum_c == 1)
			{
				selectnum_c++;
			}
		}
	}
	else if (Input::GetVKey(VK_UP) == true && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);

		//�ʏ펞
		if (check_flag == false)
		{
			if (selectnum == 1)
			{
				;//�������Ȃ�
			}
			else
			{
				selectnum -= 1;
			}
		}
		//�m�F���
		else
		{
			if (selectnum_c == 2)
			{
				selectnum_c--;
			}
		}

	}

	//��ʈڍs
	if (Input::GetVKey('Z') == true && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(2);
		//�ʏ펞
		if (check_flag == false)
		{
			//�R���e�B�j���[�ȊO�͊m�F������
			if (selectnum == 1)
			{

				move_flag = true;
			}
			else
			{
				//Audio::Start(2);
				check_flag = true;
			}
		}
		//�m�F���
		else
		{
			if (selectnum_c == 1)
				move_flag = true;
			else
				check_flag = false;
		}
	}
	//�R���g���[���[�p------------------------
	if (Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) == true && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);

		//�ʏ펞
		if (check_flag == false)
		{
			if (selectnum == 3)
			{
				;//�������Ȃ�
			}
			else
			{
				selectnum += 1;
			}
		}
		//�m�F���
		else
		{
			if (selectnum_c == 1)
			{
				selectnum_c++;
			}
		}
	}
	if (Input::GetConButtons(0, GAMEPAD_DPAD_UP) && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(1);

		//�ʏ펞
		if (check_flag == false)
		{
			if (selectnum == 1)
			{
				;//�������Ȃ�
			}
			else
			{
				selectnum -= 1;
			}
		}
		//�m�F���
		else
		{
			if (selectnum_c == 2)
			{
				selectnum_c--;
			}
		}

	}

	//��ʈڍs
	if (Input::GetConButtons(0, GAMEPAD_A) && keyflag == true && scroll_flag == true)
	{
		keyflag = false;
		Audio::Start(2);
		//�ʏ펞
		if (check_flag == false)
		{
			//�R���e�B�j���[�ȊO�͊m�F������
			if (selectnum == 1)
			{

				move_flag = true;
			}
			else
			{
				//Audio::Start(2);
				check_flag = true;
			}
		}
		//�m�F���
		else
		{
			if (selectnum_c == 1)
				move_flag = true;
			else
				check_flag = false;
		}
	}

	//��ʈڍs�����@�X�N���[���I��������ڍs
	if (move_flag == true)
	{
		m_y1 -= 50.0f;
	}
	if (m_y1 == 0.0f)
	{
		switch (selectnum)
		{
			case 1:
				Scene::SetScene(new CSceneGameMain(restart));
				break;
			case 2:
				Scene::SetScene(new CSceneStageSelect);
				break;
			case 3:
				Scene::SetScene(new CSceneTitle);
				break;
		}
	}

	//�L�[���
	if (Input::GetVKey(VK_DOWN) == false && Input::GetVKey(VK_UP) == false &&
		Input::GetVKey('Z') == false && keyflag == false && Input::GetConButtons(0, GAMEPAD_A) == false&&
		Input::GetConButtons(0, GAMEPAD_DPAD_DOWN)==false && Input::GetConButtons(0, GAMEPAD_DPAD_UP)==false)
	{
		keyflag = true;
	}

}

//�h���[
void CObjOver::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//�w�i
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1023.0f;
	src.m_bottom = 63.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//�摜�\��i��
	//��ʃT�C�Y�� 1280*720 �����Ă񂾂낭�����I�I�I�I(����)
	if (check_flag == false)
	{
		//GAMEOVER
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1007.0f;
		src.m_bottom = 128.0f;

		dst.m_top = 100.0f;
		dst.m_left = 136.0f;
		dst.m_right = 1043.0f;
		dst.m_bottom = 228.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//�R���e�B�j���[
		src.m_top = 132.0f;
		src.m_left = 0.0f;
		src.m_right = 848.0f;
		src.m_bottom = 259.0f;

		dst.m_top = 350.0f;
		dst.m_left = 428.0f;
		dst.m_right = 852.0f;
		dst.m_bottom = 414.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//�Z���N�g�߂�
		//src.m_top = 261.0f;
		//src.m_left = 0.0f;
		//src.m_right = 546.0f;
		//src.m_bottom = 390.0f;

		//dst.m_top = 450.0f;
		//dst.m_left = .0f;
		//dst.m_right = .0f;
		//dst.m_bottom = 579.0f;
		//Draw::Draw(1, &src, &dst, c, 0.0f);

		src.m_top = 392.0f;
		src.m_left = 0.0f;
		src.m_right = 631.0f;
		src.m_bottom = 521.0f;

		dst.m_top = 444.0f;
		dst.m_left = 482.0f;
		dst.m_right = 797.0f;
		dst.m_bottom = 509.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);


		//�^�C�g���߂�
		src.m_top = 523.0f;
		src.m_left = 0.0f;
		src.m_right = 1002.0f;
		src.m_bottom = 657.0f;

		dst.m_top = 539.0f;
		dst.m_left = 389.0f;
		dst.m_right = 890.0f;
		dst.m_bottom = 606.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//�J�[�\��
		src.m_top = 64.0f;
		src.m_left = 512.0f;
		src.m_right = 575.0f;
		src.m_bottom = 128.0f;

		dst.m_top = 350.0f + (selectnum - 1) * 90.0f;
		dst.m_left = 306.0f;
		dst.m_right = 370.0f;
		dst.m_bottom = 414.0f + (selectnum - 1) * 90.0f;
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	else if (check_flag == true)
	{
		//�m�F
		src.m_top = 659.0f;
		src.m_left = 0.0f;
		src.m_right = 997.0f;
		src.m_bottom = 766.0f;

		dst.m_top = 150.0f;
		dst.m_left = 391.0f;
		dst.m_right = 889.0f;
		dst.m_bottom = 203.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//�͂�
		src.m_top = 768.0f;
		src.m_left = 0.0f;
		src.m_right = 273.0f;
		src.m_bottom = 898.0f;

		dst.m_top = 300.0f;
		dst.m_left = 572.0f;
		dst.m_right = 708.0f;
		dst.m_bottom = 365.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//������
		//src.m_top = 0.0f;
		src.m_left = 275.0f;
		src.m_right = 691.0f;
		//src.m_bottom = 0.0f;

		dst.m_top = 400.0f;
		dst.m_left = 534.0f;
		dst.m_right = 746.0f;
		dst.m_bottom = 465.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//�J�[�\��
		src.m_top = 64.0f;
		src.m_left = 512.0f;
		src.m_right = 575.0f;
		src.m_bottom = 128.0f;

		dst.m_top = 300.0f + (selectnum_c - 1) * 100.0f;
		dst.m_left = 448.0f;
		dst.m_right = 512.0f;
		dst.m_bottom = 364.0f + (selectnum_c - 1) * 100.0f;
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	//�����
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 800.0f + m_y1;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_y1;
	Draw::Draw(3, &src, &dst, c, 0.0f);

}