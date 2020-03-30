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

void CObjStageSelect::Init()
{
	stageflag = 1;
	keyflag = true;
}

//�A�N�V����
void CObjStageSelect::Action()
{
	if (Input::GetVKey(VK_RIGHT)==true&&keyflag==true)
	{
		keyflag = false;
		Audio::Start(1);
		if (stageflag == 3)
		{
			;//�������Ȃ�
		}
		else
		{
			stageflag+=1;
		}
	}
	 if (Input::GetVKey(VK_LEFT)==true&&keyflag==true)
	{
		keyflag = false;
		Audio::Start(1);
		if (stageflag == 1)
		{
			;//�������Ȃ�
		}
		else
		{
			stageflag-=1;
		}
		
		
	}
	

	if (Input::GetVKey('X') == true && keyflag == true)
	{
		keyflag = false;
		Audio::Start(2);
		;//title�V�[���Ɉڍs
	}
	if (Input::GetVKey('Z') == true && keyflag == true)
	{
		keyflag = false;
		Audio::Start(2);
		;
		for (int i = 1;i < stageflag;i++)
		{
			if (stageflag == 2)
			{
				Audio::Stop(0);
				Sleep(500);
				Scene::SetScene(new CSceneGameMain());//���̃X�e�[�W�Ɉڍs
			}
		}

	}
	if (Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false &&
		Input::GetVKey('X') == false && Input::GetVKey('Z') == false && keyflag == false)
	{
		keyflag = true;
	}
}

//�h���[
void CObjStageSelect::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu
	//hoge�w�i1
	src.m_top = ZERO_G;
	src.m_left = ZERO_G;
	src.m_right = HD_RIGIT;
	src.m_bottom = HD_BUTTOM;

	dst.m_top = ZERO_G;
	dst.m_left = ZERO_G;
	dst.m_right = HD_RIGIT;
	dst.m_bottom = HD_BUTTOM;
	Draw::Draw(0, &src, &dst, c, 0.0f);
	
	//Stage1�I��
	if (stageflag == 1)
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
		src.m_left = 301.0f;
		src.m_right = 601.0f;

		dst.m_left = 500.0f;
		dst.m_right = 800.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		//stage3
		dst.m_left = 900.0f;
		dst.m_right = 1200.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	//Stage2�I��
	if (stageflag == 2)
	{
		
		//stage1
		src.m_top = ZERO_G;
		src.m_left = 301.0f;
		src.m_right = 601.0f;
		src.m_bottom = 200.0f;

		dst.m_top = 350.0f;
		dst.m_left = 100.0f;
		dst.m_right = 400.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);

		// stage2
		
		src.m_left = ZERO_G;
		src.m_right = 300.0f;
	

		dst.m_top = 350.0f;
		dst.m_left = 500.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 550.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
		

		//stage3
		src.m_left = 301.0f;
		src.m_right = 601.0f;

		dst.m_left = 900.0f;
		dst.m_right = 1200.0f;
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	//Stage3�I��
	if (stageflag == 3)
	{
		//stage1
		src.m_top = ZERO_G;
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
		src.m_left = ZERO_G;
		src.m_right = 300.0f;


		dst.m_left = 900.0f;
		dst.m_right = 1200.0f;

		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	
	src.m_top = 200.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 320.0f;

	dst.m_top = 650.0f;
	dst.m_left = 200.0f;
	dst.m_right = 1100.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(1, &src, &dst, c, 0.0f);

	
}