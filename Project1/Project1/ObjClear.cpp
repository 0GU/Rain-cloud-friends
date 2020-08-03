// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"

#include"GameHead.h"
#include"ObjClear.h"

CObjClear::CObjClear(float m_hp, float cl_hp,int stage)
{
	hero_hp = m_hp;//��l���̂g�o�擾�p
	cloud_hp = cl_hp;//�_�̂g�o�擾�p
	stageselect = stage;
}

void CObjClear::Init()
{
	key_flag = true;
	move_flag = false;
	scroll_flag = false;
	m_y1 = 0.0f;
	Clear_flag[0] = false;
	Clear_flag[1] = false;
	Clear_flag[2] = false;

	Save::Open();
}

//�A�N�V����
void CObjClear::Action()
{
	/*
	//��l������̗͂̏��������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�_����̗͂̏��������Ă���
	CObjCloud* cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
	*/

	//if(CObjStage)
	//�N���A��Ԃ̊Ǘ�

	if (hero_hp >= 0.75f && cloud_hp >= 0.75f)//��l���Ɖ_�̗̑͂����ȏ�̏ꍇ
	{
		Clear_flag[0] = true;
	}
    if (hero_hp >= 0.75f || cloud_hp >= 0.75f)//��l�����_�̗̑͂̂ǂ��炩�����̏ꍇ
	{
		
		Clear_flag[1] = true;
	}

	if(hero_hp <= 0.75f || cloud_hp <= 0.75f) //�ǂ�������ȉ��̏ꍇ
	{
		Clear_flag[2] = true;
	}
	

	if (Clear_flag[0] == true)//Perfect
	{
		switch(stageselect)
		{
		case 1:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_1[0] = true;
			break;
		case 2:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_2[0] = true;
			break;
		case 3:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_3[0] = true;
			break;
		}
	}
	if (Clear_flag[1] == true)//Great
	{
		switch (stageselect)
		{
		case 1:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_1[1] = true;
			break;
		case 2:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_2[1] = true;
			break;
		case 3:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_3[1] = true;
			break;
		}
	}
	if (Clear_flag[2] == true)//Good
	{
		switch (stageselect)
		{
		case 1:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_1[2] = true;
			break;
		case 2:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_2[2] = true;
			break;
		case 3:
			Save::Seve();
			((UserData*)Save::GetData())->Stage_3[2] = true;
			break;
		}
	}
	//����ʃX�N���[��
	if (scroll_flag == false)
	{
		m_y1 += 40.0f;
		if (m_y1 > 800.0f)
		{
			m_y1 = 800.0f;
			scroll_flag = true;
		}
	}

	if (Input::GetVKey('Z') == true ||Input::GetConButtons(0, GAMEPAD_A) && key_flag == true)
	{
		key_flag = false;
		scroll_flag = true;
		move_flag = true;
	}

	if (move_flag == true)
	{
		m_y1 -= 50.0f;
	}

	if (m_y1 == 0.0f)
	{
		Scene::SetScene(new CSceneStageSelect);
	}

	if (Input::GetVKey('Z') == false && Input::GetConButtons(0, GAMEPAD_A)==false&&key_flag == false)
	{
		key_flag = true;
	}
}

//�h���[
void CObjClear::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//���w�i(��)
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 16.0f;
	src.m_bottom = 16.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

	//StageClear
	src.m_top = 369.0f;
	src.m_left = 0.0f;
	src.m_right = 900.0f;
	src.m_bottom = 529.0f;

	dst.m_top = 50.0f;
	dst.m_left = 200.0f;
	dst.m_right = 1100.0f;
	dst.m_bottom = 211.0f;

	Draw::Draw(1, &src, &dst, c, 0.0f);

	//Excerent
	src.m_top = 147.0f;
	src.m_left = 0.0f;
	src.m_right = 815.0f;
	src.m_bottom = 300.0f;

	dst.m_top = 320.0f;
	dst.m_left = 650.0f;
	dst.m_right = 1200.0f;
	dst.m_bottom = 470.0f;

	Draw::Draw(5, &src, &dst, c, 30.0f);

	//���i���j��������----------------------------------------
	//1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right =512.0f;
	src.m_bottom = 512.0f;

	dst.m_top = 300.0f;
	dst.m_bottom = 500.0f;
	if (Clear_flag[0] == true)
	{
		dst.m_left = 20.0f;
		dst.m_right = 270.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	if (Clear_flag[1] == true)
	{
		//2
		dst.m_left = 200.0f;
		dst.m_right = 450.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	if (Clear_flag[2] == true)
	{
		//3
		dst.m_left = 380.0f;
		dst.m_right = 630.0f;

		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	//�����܂�------------------------------------------------
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