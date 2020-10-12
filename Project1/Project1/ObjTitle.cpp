// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjTitle.h"

void CObjTitle::Init()
{
	m_scroll = 0.0f;
	move_flag = false;
	scroll_flag = false;
	key_flag = false;
	m_y1 = 0.0f;

	select_flag = true;
	description_flag = true;
}

//�A�N�V����
void CObjTitle::Action()
{

	///����ʃX�N���[��
	if (scroll_flag == false)
	{
		
		m_y1 += 50.0f;//�ォ�牺�ɍ~�낷
		if (m_y1 > 800.0f)//800�𒴂�����
		{
			m_y1 = 800.0f;//800�ɌŒ�
			scroll_flag = true;//�X�N���[�����~�߂�
			key_flag = true;
		}
	}
	//�R���g���[���[�p------------------------------------------------------------------
	//�X�e�[�W�ɐi��
	if (Input::GetConButtons(0,GAMEPAD_A) && scroll_flag == true && select_flag == true && key_flag == true)//A�{�^����������
	{
		Audio::Start(2);
		key_flag = false;//Key�̃t���O���~�߂�

		move_flag = true;//�������ɓ������t���O�N��
	}
	//��������Ɉڍs
	//�J�[�\���ړ�
	if (Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) && select_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		select_flag = false;
	}

	if (Input::GetConButtons(0, GAMEPAD_DPAD_UP) && select_flag == false && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		select_flag = true;
	}
	//��������N��
	if (Input::GetConButtons(0, GAMEPAD_A) && select_flag == false && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		description_flag = false;
	}
	//��������I��
	if (Input::GetConButtons(0, GAMEPAD_A)  && select_flag == false && description_flag == false && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		description_flag = true;
	}
	//�L�[�{�[�h�p-----------------------------------------------------------------------------
	//�X�e�[�W�ɐi��
	if (Input::GetVKey('Z') == true  && scroll_flag == true && select_flag ==true && key_flag == true)//Z�L�[��������
	{
		Audio::Start(2);
		key_flag = false;//Key�̃t���O���~�߂�

		move_flag = true;//�������ɓ������t���O�N��
	}
	//��������Ɉڍs
	//�J�[�\���ړ�
	if (Input::GetVKey(VK_DOWN) == true && select_flag == true && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		select_flag = false;
	}

	if (Input::GetVKey(VK_UP) == true && select_flag == false && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		select_flag = true;
	}
	//��������N��
	if (Input::GetVKey('Z') == true && select_flag == false && description_flag == true && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		description_flag = false;
	}
	//��������I��
	if (Input::GetVKey('Z') == true && select_flag == false && description_flag == false && key_flag == true && scroll_flag == true)
	{
		Audio::Start(2);
		key_flag = false;
		description_flag = true;
	}

	if (move_flag == true)//�N�����Ă����
	{
		m_y1 -= 40.0f;//�������ɓ�����
	}

	if (m_y1 == 0.0f)//��������
	{
		m_y1 = 0.0f;//0�ɌŒ�
		scroll_flag = false;
		Scene::SetScene(new CSceneStageSelect);
	}

	if (Input::GetVKey('Z') == false && Input::GetConButtons(0, GAMEPAD_A)==false && key_flag == false)
	{

		key_flag = true;
	}
}

//�h���[
void CObjTitle::Draw()
{

	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	if (description_flag == true)
	{
		//�^�C�g���w�i
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 1024.0f;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 1280.0f;
		dst.m_bottom = 720.0f;

		Draw::Draw(0, &src, &dst, c, 0.0f);

		//�^�C�g���w�i
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 100.0f;
		dst.m_left = 180.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 400.0f;

		Draw::Draw(1, &src, &dst, c, 0.0f);

		

		//�������
		src.m_top = 1.0f;
		src.m_left = 1.0f;
		src.m_right = 275.0f;
		src.m_bottom = 70.0f;

		dst.m_top = 500.0f;
		dst.m_left = 490.0f;
		dst.m_right = 765.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);

		//Game Start
		src.m_top = 72.0f;
		src.m_left = 1.0f;
		src.m_right = 340.0f;
		src.m_bottom = 125.0f;

		dst.m_top = 401.0f;
		dst.m_left = 490.0f;
		dst.m_right = 830.0f;
		dst.m_bottom = 455.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);

		//�I���J�[�\��------------------------------------------
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

	}
	
	//�㔻��
	if (select_flag == true)
	{
		dst.m_top = 400.0f;
		dst.m_left = 420.0f;
		dst.m_right = 484.0f;
		dst.m_bottom = 464.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//������
	if(select_flag==false)
	{
		dst.m_top = 500.0f;
		dst.m_left = 420.0f;
		dst.m_right = 485.0f;
		dst.m_bottom = 564.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//�������
	if (description_flag == false)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1280.0f;
		src.m_bottom = 720.0f;

		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 1280.0f;
		dst.m_bottom = 720.0f;
		Draw::Draw(5, &src, &dst, c, 0.0f);
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
	Draw::Draw(2, &src, &dst, c, 0.0f);
}