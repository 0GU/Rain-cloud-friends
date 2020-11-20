//�g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjStageSelect.h"
#include<Windows.h>

//�C�j�V�����C�Y
void CObjStageSelect::Init()
{
	//������
	m_selectnum = 1;//�Z���N�g�ԍ�����
	m_key_f = false;//��񂾂��@�𔻕ʂ��邽�߂̃t���O

	m_fade = 0.0f; // �t�F�[�h�̒l������

	move_flag = false;//�Q��ڂ̃t�F�[�h�N���p
	m_fade_f = false;//�P��ڂ̃t�F�[�h�N���p

	title_flag = false;//�^�C�g����ʂɖ߂�p�t���O

	//�Z�[�u�f�[�^���Z�b�g�i�������j
	bool set_Stage[3] = { false, false ,false };
	bool set_Stage2[3] = { false, false ,false };
	bool set_Stage3[3] = { false, false ,false };
	Save::Open();
	//�Z�[�u�f�[�^���Z�b�g�i�Z�[�u����Ă���f�[�^���Q�Ƃ��Ĕ��f�j
	for (int i = 0;i < 3;i++)
	{
		//perfrct
		if (((UserData*)Save::GetData())->Stage_1[i] == true)
		{
			set_Stage[i] = true;
		}
		if (((UserData*)Save::GetData())->Stage_2[i] == true)
		{
			set_Stage2[i] = true;
		}
		if (((UserData*)Save::GetData())->Stage_3[i] == true)
		{
			set_Stage3[i] = true;
		}
	}

	//�Z�b�g����Ă���f�[�^���X�̔z��ɃR�s�[
	//�Ԃ����Ⴏ���K�v�����邩�͔���
	memcpy(Clear_flag, set_Stage, sizeof(bool) * (3));
	memcpy(Clear_flag2, set_Stage2, sizeof(bool) * (3));
	memcpy(Clear_flag3, set_Stage3, sizeof(bool) * (3));
}

//�A�N�V����
void CObjStageSelect::Action()
{
	Save::Open();

	//�t�F�[�h�C���p����N����
	if (m_fade_f == false)
	{
		m_fade += 0.03f;//�t�F�[�h�����������邭���Ă���
		if (m_fade >= 1.0f)//Max�܂ŗ����
		{
			m_fade = 1.0f;//�l��Max�ɌŒ肵
			m_fade_f = true;//�t�F�[�h�C�����~�߂�
			m_key_f = true;//�L�[����\�ɂ���
		}

	}

	/*
	����p�̕ϐ��̗���Ƃ��Ă�
	�{�^����������Ă���A�t�F�[�h����~���Ă���A�L�[���삪�\�ȏꍇ
	�N���A�f�[�^���Q�Ƃ��ē��e��؂�ւ��Ă���
	*/
	//��������X�e�[�W�R�}���h------------------(�R���g���[���[�p�j
	//�E�ɓ������ꍇ
	if (Input::GetConButtons(0, GAMEPAD_DPAD_RIGHT) && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//�L�[����s�\�ɂ���
		Audio::Start(1);
		if (m_selectnum == 3)//�Z���N�g��Stage3���璴����̂�h��
		{
			;//�������Ȃ�
		}
		//Stage1�N���A�t���O�݂̂��������Ă���ꍇ
		if (Clear_flag[2] == true && Clear_flag2[2] == false)
		{
			m_selectnum = 2;//Stage2�Ɉڍs�\
		}
		//Stage1,2�N���A�t���O���������Ă���ꍇ
		if (Clear_flag[2] == true && Clear_flag2[2] == true)
		{
			m_selectnum += 1;//1,2,3��I���ł���悤�ɂ���
			if (m_selectnum >= 3)
			{
				m_selectnum = 3;//�Z���N�g��Stage3���璴����̂�h��
			}
		}
	}
	//���ɓ������ꍇ
	if (Input::GetConButtons(0,GAMEPAD_DPAD_LEFT)&& m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//�L�[����s�\�ɂ���
		Audio::Start(1);//���ʉ��쓮
		if (m_selectnum == 1)//�Z���N�g
		{
			;//�������Ȃ�
		}
		//Stage1�N���A�t���O���������Ă���ꍇ
		if (Clear_flag[2] == true && Clear_flag2[2] == false)
		{
			m_selectnum = 1;
		}
		//Stage1,2�N���A�t���O���������Ă���ꍇ
		if (Clear_flag[2] == true && Clear_flag2[2] == true)
		{
			m_selectnum -= 1;//1,2,3��I���ł���悤�ɂ���
			if (m_selectnum == 0)
			{
				m_selectnum = 1;//�Z���N�g��Stage1����}�C�i�X�ɂȂ�̂��̂�h��
			}
		}
	}
	//B�{�^����������Ă���ꍇ
	if ( Input::GetConButtons(0, GAMEPAD_B) && m_key_f == true && m_fade_f == true)
	{

		m_key_f = false;//�L�[����s�\�ɂ���
		Audio::Start(2);//���ʉ��쓮
		title_flag = true;//�^�C�g���Ȉڍs�p�t���O���N����
		move_flag = true;//���ڂ̃t�F�[�h���N��
	}
	if (Input::GetConButtons(0, GAMEPAD_A) && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//�L�[����s�\�ɂ���
		Audio::Stop(0);//���C��BGM��~
		if (move_flag == false)//�������d�ɂȂ邽�ߍ������オ��O�Ɉ�񂾂�������
		{
			Audio::Start(2);
		}
		move_flag = true;//���ڂ̃t�F�[�h���N��
	}

	//��������L�[�{�[�h�p--------------------------------------------------------------
	if (Input::GetVKey(VK_RIGHT) && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//�L�[����s�\�ɂ���
		Audio::Start(1);
		if (m_selectnum == 3)//�Z���N�g��Stage3���璴����̂�h��
		{
			;//�������Ȃ�
		}
		//Stage1�N���A�t���O�݂̂��������Ă���ꍇ
		if (Clear_flag[2] == true && Clear_flag2[2] == false)
		{
			m_selectnum = 2;
		}
		//Stage1,2�N���A�t���O���������Ă���ꍇ
		if (Clear_flag[2] == true && Clear_flag2[2] == true)
		{
			m_selectnum += 1;//1,2,3��I���ł���悤�ɂ���
			if (m_selectnum >= 3)
			{
				m_selectnum = 3;
			}
		}
	}
	if (Input::GetVKey(VK_LEFT) == true && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//�L�[����s�\�ɂ���
		Audio::Start(1);//���ʉ��쓮
		if (m_selectnum == 1)//�Z���N�g
		{
			;//�������Ȃ�
		}
		//Stage1�N���A�t���O���������Ă���ꍇ
		if (Clear_flag[2] == true && Clear_flag2[2] == false)
		{
			m_selectnum = 1;
		}
		//Stage1,2�N���A�t���O���������Ă���ꍇ
		if (Clear_flag[2] == true && Clear_flag2[2] == true)
		{
			m_selectnum -= 1;//1,2,3��I���ł���悤�ɂ���
			if (m_selectnum == 0)
			{
				m_selectnum = 1;//�Z���N�g��Stage1����}�C�i�X�ɂȂ�̂��̂�h��
			}
		}
	}

	if (Input::GetVKey('X') == true && m_key_f == true && m_fade_f == true)
	{
		m_key_f = false;//�L�[����s�\�ɂ���
		Audio::Start(2);//���ʉ��쓮
		title_flag=true;
		move_flag = true;//���ڂ̃t�F�[�h���N��
	}

	if (Input::GetVKey('Z') == true  &&  m_key_f == true && m_fade_f == true)//Stage1
	{
		m_key_f = false;//�L�[����s�\�ɂ���
		Audio::Stop(0);
		if (move_flag == false)//�������d�ɂȂ邽�ߍ������オ��O�Ɉ�񂾂�������
		{
			Audio::Start(2);//���ʉ��쓮
		}
		move_flag = true;//���ڂ̃t�F�[�h���N��
	}

	//�����܂�------------------------
	//���ڂ̃t�F�[�h����
	if (move_flag == true)//�N�����Ă����
	{
		m_fade -= 0.03f;//�t�F�[�h�A�E�g���Ă���
	}

	if (m_fade <= 0.0f)//���S�ɐ^���ÂɂȂ�����
	{
		m_fade = 0.0f;//0�ɌŒ�
		if (title_flag == true)//�^�C�g���p�t���O���N�����Ă����
		{
			Scene::SetScene(new CSceneTitle);//title�V�[���Ɉڍs
		}
		else//�N�����Ă��Ȃ��ꍇ��
		{
			Scene::SetScene(new CSceneGameMain(m_selectnum));//���̃X�e�[�W�Ɉڍs
		}
		
	}
	//�S�ẴL�[�𗣂��Ă����
	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false &&
		Input::GetVKey('X') == false && Input::GetVKey('Z') == false && Input::GetVKey('B') == false &&
		Input::GetConButtons(0, GAMEPAD_DPAD_RIGHT)==false && Input::GetConButtons(0, GAMEPAD_DPAD_LEFT) == false&&
		m_key_f == false
		)
	{

		m_key_f = true;//�L�[���͉\�ɂ���

	}
}

//�h���[
void CObjStageSelect::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade };//

	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//hoge�w�i1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = HD_RIGIT;
	src.m_bottom = HD_BUTTOM;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = HD_RIGIT;
	dst.m_bottom = HD_BUTTOM;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//Stage1�ԐF�I��
	if (m_selectnum == 1)
	{
		//stage1
		src.m_right = 300.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 350.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);


		//stage2
		if (Clear_flag[2] == true)
		{
			src.m_left = 301.0f;
			src.m_right = 601.0f;

			dst.m_left = 500.0f;
			dst.m_right = 800.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);
		}
		if (Clear_flag2[2] == true)
		{
			//stage3
			dst.m_left = 900.0f;
			dst.m_right = 1200.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);
		}
	}
	//Stage2�ԐF�I��
	if (Clear_flag[2] == true)
	{
		if (m_selectnum == 2)
		{
			//stage1
			src.m_top = 0.0f;
			src.m_left = 301.0f;
			src.m_right = 601.0f;
			src.m_bottom = 200.0f;

			dst.m_top = 350.0f;
			dst.m_left = 100.0f;
			dst.m_right = 400.0f;
			dst.m_bottom = 550.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);

			// stage2
			src.m_left = 0.0f;
			src.m_right = 300.0f;

			dst.m_top = 350.0f;
			dst.m_left = 500.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 550.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);

			if (Clear_flag2[2] == true)
			{
				//stage3
				src.m_left = 301.0f;
				src.m_right = 601.0f;

				dst.m_left = 900.0f;
				dst.m_right = 1200.0f;
				Draw::Draw(1, &src, &dst, c, 0.0f);
			}
		}
	}
	
	//Stage3�ԐF�I��
	if (Clear_flag2[2] == true)
	{
		if (m_selectnum == 3)
		{
			//stage1
			src.m_top = 0.0f;
			src.m_left = 301.0f;
			src.m_right = 601.0f;
			src.m_bottom = 200.0f;

			dst.m_top = 350.0f;
			dst.m_left = 100.0f;
			dst.m_right = 400.0f;
			dst.m_bottom = 550.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);

			//stage2
			dst.m_left = 500.0f;
			dst.m_right = 800.0f;
			Draw::Draw(1, &src, &dst, c, 0.0f);

			//stage3
			src.m_left = 0.0f;
			src.m_right = 300.0f;


			dst.m_left = 900.0f;
			dst.m_right = 1200.0f;

			Draw::Draw(1, &src, &dst, c, 0.0f);
		}
	}

	//Stage1
	src.m_top = 321.0f;
	src.m_left = 0.0f;
	src.m_right = 301.0f;
	src.m_bottom = 421.0f;

	dst.m_top = 201.0f;
	dst.m_left = 100.0f;
	dst.m_right = 401.0f;
	dst.m_bottom = 321.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//Stage2
	if (Clear_flag[2] == true)
	{
		src.m_top = 321.0f;
		src.m_left = 302.0f;
		src.m_right = 602.0f;
		src.m_bottom = 421.0f;

		dst.m_top = 201.0f;
		dst.m_left = 500.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 321.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	
	//Stage3
	if (Clear_flag2[2] == true)
	{
		src.m_top = 321.0f;
		src.m_left = 603.0f;
		src.m_right = 903.0f;
		src.m_bottom = 421.0f;

		dst.m_top = 201.0f;
		dst.m_left = 900.0f;
		dst.m_right = 1200.0f;
		dst.m_bottom = 321.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	

	//�X�e�[�W�I��
	src.m_top = 423.0f;
	src.m_left = 0.0f;
	src.m_right = 801.0f;
	src.m_bottom = 544.0f;

	dst.m_top = 50.0f;
	dst.m_left = 250.0f;
	dst.m_right = 1050.0f;
	dst.m_bottom = 171.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//���̐�����
	src.m_top = 200.0f;
	src.m_left = .0f;
	src.m_right = 800.0f;
	src.m_bottom = 320.0f;

	dst.m_top = 630.0f;
	dst.m_left = 200.0f;
	dst.m_right = 1100.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//--------------�������玴
	//���i����j
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//Stage1
	if (Clear_flag[2] == true || Clear_flag[1] == true || Clear_flag[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 120.0f;
		dst.m_right = 220.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag[1] == true || Clear_flag[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 200.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 280.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);

	}
	//Stage2
	if (Clear_flag2[2] == true || Clear_flag2[1] == true || Clear_flag2[0] == true)
	{

		dst.m_top = 560.0f;
		dst.m_left = 520.0f;
		dst.m_right = 620.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag2[1] == true || Clear_flag2[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 600.0f;
		dst.m_right = 700.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag2[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 680.0f;
		dst.m_right = 780.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	//Stage3
	if (Clear_flag3[2] == true  || Clear_flag3[1] == true || Clear_flag3[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 920.0f;
		dst.m_right = 1020.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}

	if (Clear_flag3[1] == true || Clear_flag3[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 1000.0f;
		dst.m_right = 1100.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	if (Clear_flag3[0] == true)
	{
		dst.m_top = 560.0f;
		dst.m_left = 1080.0f;
		dst.m_right = 1180.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(3, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------------------------------------

	//��(�Ȃ��j
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	//stage1
	if (Clear_flag[2] == false && Clear_flag[1] == false && Clear_flag[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 120.0f;
		dst.m_right = 220.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);

	}
	if (Clear_flag[1] == false && Clear_flag[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 200.0f;
		dst.m_right = 300.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	if (Clear_flag[0] == false)
	{
		dst.m_top = 560.0f;
		dst.m_left = 280.0f;
		dst.m_right = 380.0f;
		dst.m_bottom = 620.0f;

		Draw::Draw(4, &src, &dst, c, 0.0f);
	}

	//stage2
	if (Clear_flag[2] == true)
	{
		if (Clear_flag2[2] == false && Clear_flag2[1] == false && Clear_flag2[0] == false)
		{

			dst.m_top = 560.0f;
			dst.m_left = 520.0f;
			dst.m_right = 620.0f;
			dst.m_bottom = 620.0f;

			Draw::Draw(4, &src, &dst, c, 0.0f);
		}
		if (Clear_flag2[1] == false && Clear_flag2[0] == false)
		{
			dst.m_top = 560.0f;
			dst.m_left = 600.0f;
			dst.m_right = 700.0f;
			dst.m_bottom = 620.0f;

			Draw::Draw(4, &src, &dst, c, 0.0f);
		}
		if (Clear_flag2[0] == false)
		{
			dst.m_top = 560.0f;
			dst.m_left = 680.0f;
			dst.m_right = 780.0f;
			dst.m_bottom = 620.0f;

			Draw::Draw(4, &src, &dst, c, 0.0f);
		}
	}
	
	//stage3
	if (Clear_flag2[2] == true)
	{
		if (Clear_flag3[2] == false && Clear_flag3[1] == false && Clear_flag3[0] == false)
		{

			dst.m_top = 560.0f;
			dst.m_left = 920.0f;
			dst.m_right = 1020.0f;
			dst.m_bottom = 620.0f;

			Draw::Draw(4, &src, &dst, c, 0.0f);
		}
		if (Clear_flag3[1] == false && Clear_flag3[0] == false)
		{
			dst.m_top = 560.0f;
			dst.m_left = 1000.0f;
			dst.m_right = 1100.0f;
			dst.m_bottom = 620.0f;

			Draw::Draw(4, &src, &dst, c, 0.0f);
		}
		if (Clear_flag3[0] == false)
		{
			dst.m_top = 560.0f;
			dst.m_left = 1080.0f;
			dst.m_right = 1180.0f;
			dst.m_bottom = 620.0f;

			Draw::Draw(4, &src, &dst, c, 0.0f);
		}

	}
	//-------------------�����܂�
}