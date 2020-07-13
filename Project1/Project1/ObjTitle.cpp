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

	if (Input::GetConButtons(0,GAMEPAD_A)&& key_flag == true && scroll_flag==true)//Z�L�[��������
	{
		key_flag = false;//Key�̃t���O���~�߂�

		move_flag = true;//�������ɓ������t���O�N��
	}
	if (Input::GetVKey('Z') == true  && scroll_flag == true)//Z�L�[��������
	{
		key_flag = false;//Key�̃t���O���~�߂�

		move_flag = true;//�������ɓ������t���O�N��
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

	if (Input::GetVKey('Z') == false && key_flag == false)
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
	dst.m_right =1100.0f;
	dst.m_bottom = 400.0f;

	Draw::Draw(1, &src, &dst, c, 0.0f);

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