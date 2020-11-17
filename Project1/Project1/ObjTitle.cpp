// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjTitle.h"

//�ϐ��̏�����
void CObjTitle::Init()
{
	move_flag = false;//�Q��ڂ̃t�F�[�h�N���p
	m_fade_f = false;//1��ڂ̃t�F�[�h�N���p
	key_flag = false;//��񂾂��@�𔻕ʂ��邽�߂̃t���O
	
	m_fade = 0.0f;//�t�F�[�h�̒l������

	select_flag = true;//�J�[�\�����ォ�����𔻕ʂ��邽�߂̃t���O
	description_flag = false;//���������ʂ��o�����߂̃t���O

	m_ani_time = 0.0f;//�A�j���[�V��������
	m_ani_max = 8.0f;//�A�j���[�V�����ő�l

	m_con_num = 5;//�O�̂��߃R���g���[���[�ԍ����R���g���[�����ڑ�����Ă��Ȃ��ԍ��ɏ�����
}

//�A�N�V����
void CObjTitle::Action()
{
	//�R���g���[���ԍ����蓖��
	m_con_num = Input::UpdateXControlerConnected();
	
	//�t�F�[�h�C���p����N����
	if (m_fade_f == false)
	{
		m_fade += 0.03f;//�t�F�[�h�����������邭���Ă���
		if (m_fade >= 1.0f)//Max�܂ŗ����
		{
			m_fade = 1.0f;//�l��Max�ɌŒ肵
			m_fade_f = true;//�t�F�[�h�C�����~�߂�
			key_flag = true;//�L�[����\�ɂ���
		}
		
	}

	/*
	����p�̕ϐ��̗���Ƃ��Ă�
	�{�^����������Ă���A�t�F�[�h����~���Ă���A�L�[���삪�\�ȏꍇ
	*/
	//�R���g���[���[�p------------------------------------------------------------------
	//�X�e�[�W�ɐi��
	if (Input::GetConButtons(0,GAMEPAD_A) && m_fade_f == true && select_flag == true && key_flag == true)//
	{
		Audio::Start(2);//���ʉ��쓮
		key_flag = false;//�L�[����s�\�ɂ���

		move_flag = true;//���ڂ̃t�F�[�h���N��
	}

	//�J�[�\���ړ�
	//�J�[�\�������ɓ������ꍇ
	if (Input::GetConButtons(0, GAMEPAD_DPAD_DOWN) && select_flag == true && key_flag == true && m_fade_f == true)
	{
		Audio::Start(2);//���ʉ��쓮
		key_flag = false;//�L�[����s�\�ɂ���
		select_flag = false;//�J�[�\��������
	}
	//�J�[�\������ɓ������ꍇ
	if (Input::GetConButtons(0, GAMEPAD_DPAD_UP) && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
	{
		Audio::Start(2);//���ʉ��쓮
		key_flag = false;//�L�[����s�\�ɂ���
		select_flag = true;//�J�[�\�������
	}

	//��������N��
	if (Input::GetConButtons(0, GAMEPAD_A) && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
	{
		Audio::Start(2);//���ʉ��쓮
		key_flag = false;//�L�[����s�\�ɂ���
		description_flag = true;//���������ʂ�\������
	}
	//��������I��
	if (Input::GetConButtons(0, GAMEPAD_A)  && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
	{
		Audio::Start(2);//���ʉ��쓮
		key_flag = false;//�L�[����s�\�ɂ���
		description_flag = false;//���������ʂ��\���ɂ���
	}
	//-----------------------------------------------------------------------------------------

	//�L�[�{�[�h�p-----------------------------------------------------------------------------
	if (m_con_num !=0 && m_con_num !=1)
	{
		if (Input::GetVKey('Z') == true && m_fade_f == true && select_flag == true && key_flag == true)//Z�L�[��������
		{
			Audio::Start(2);//���ʉ��쓮
			key_flag = false;//Key�̃t���O���~�߂�

			move_flag = true;//���ڂ̃t�F�[�h���N��
		}
		//�J�[�\�������ɓ������ꍇ
		if (Input::GetVKey(VK_DOWN) == true && select_flag == true && description_flag == false && key_flag == true && m_fade_f == true)
		{
			Audio::Start(2);//���ʉ��쓮
			key_flag = false;//�L�[����s�\�ɂ���
			select_flag = false;//�J�[�\��������
		}
		//�J�[�\������ɓ������ꍇ
		if (Input::GetVKey(VK_UP) == true && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
		{
			Audio::Start(2);//���ʉ��쓮
			key_flag = false;//�L�[����s�\�ɂ���
			select_flag = true;//�J�[�\�������
		}

		//��������N��
		if (Input::GetVKey('Z') == true && select_flag == false && description_flag == false && key_flag == true && m_fade_f == true)
		{
			Audio::Start(2);//���ʉ��쓮
			key_flag = false;//�L�[����s�\�ɂ���
			description_flag = true;//���������ʂ�\������
		}
		//��������I��
		if (Input::GetVKey('Z') == true && select_flag == false && description_flag == true && key_flag == true && m_fade_f == true)
		{
			Audio::Start(2);//���ʉ��쓮
			key_flag = false;//�L�[����s�\�ɂ���
			description_flag = false;//���������ʂ��\������
		}
	}
	
	//���ڂ̃t�F�[�h����
	if (move_flag == true)//�N�����Ă����
	{
		m_fade -=0.03f;//�t�F�[�h�A�E�g���Ă���
	}

	if (m_fade <= 0.0f)//���S�ɐ^���ÂɂȂ�����
	{
		m_fade = 0.0f;//0�ɌŒ�
		m_fade_f = false;//�O�̂���
		Scene::SetScene(new CSceneStageSelect);//�X�e�[�W�Z���N�g��ʂɓ]�ڂ���
	}

	//�S�ẴL�[�𗣂��Ă����
	if (Input::GetVKey('Z') == false && Input::GetConButtons(0, GAMEPAD_A)==false && key_flag == false)
	{
		key_flag = true;//�L�[���͉\�ɂ���
	}

	//�J�[�\���̃A�j���[�V����
	m_ani_time += 0.2f;
	if (m_ani_time >=8.0f)
	{
		m_ani_time = 0.0f;
	}
}

//�h���[
void CObjTitle::Draw()
{

	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade };//m_fade�̏ꏊ�͓����x��\��


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//
	if (description_flag == false)
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

		//�^�C�g������
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 256.0f;

		dst.m_top = 100.0f;
		dst.m_left = 180.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 400.0f;

		Draw::Draw(1, &src, &dst, c, 0.0f);

		

		//�����������
		src.m_top = 1.0f;
		src.m_left = 1.0f;
		src.m_right = 275.0f;
		src.m_bottom = 70.0f;

		dst.m_top = 500.0f;
		dst.m_left = 490.0f;
		dst.m_right = 765.0f;
		dst.m_bottom = 570.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);

		//Game Start����
		src.m_top = 72.0f;
		src.m_left = 1.0f;
		src.m_right = 340.0f;
		src.m_bottom = 125.0f;

		dst.m_top = 401.0f;
		dst.m_left = 490.0f;
		dst.m_right = 830.0f;
		dst.m_bottom = 455.0f;
		Draw::Draw(3, &src, &dst, c, 0.0f);



	}
	
	//�I���J�[�\��------------------------------------------
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;
	//�㔻��
	if (select_flag == true)
	{
		dst.m_top = 400.0f;
		dst.m_left = 420.0f + m_ani_time;
		dst.m_right = 484.0f + m_ani_time;
		dst.m_bottom = 464.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//������
	if(select_flag==false)
	{
		dst.m_top = 500.0f;
		dst.m_left = 420.0f + m_ani_time;
		dst.m_right = 485.0f + m_ani_time;
		dst.m_bottom = 564.0f;
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//---------------------------------------------------------
	//����������
	if (description_flag == true)
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
/*	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 800.0f + m_fade;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 0.0f + m_fade;
	Draw::Draw(2, &src, &dst, c, 0.0f);*/
}