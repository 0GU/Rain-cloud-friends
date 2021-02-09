// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"
#include"GameHead.h"


void CObjEnding::Init()
{
	key_flag = false;
	move_flag = false;//�Q��ڂ̃t�F�[�h�N���p
	m_fade_f = false;//1��ڂ̃t�F�[�h�N���p

	m_fade = 0.0f;
}

//�A�N�V����
void CObjEnding::Action()
{
	//�t�F�[�h�C���p����N����
	if (m_fade_f == false)
	{
		m_fade += 0.01f;//�t�F�[�h�����������邭���Ă���
		if (Input::GetConButtons(0, GAMEPAD_A) == true || Input::GetVKey('Z') == true)//�t�F�[�h�C�����ɃL�[�������Ă����
		{
			;//�������Ȃ�
		}
		if (m_fade >= 1.0f)//Max�܂ŗ����
		{
			m_fade = 1.0f;//�l��Max�ɌŒ肵
			m_fade_f = true;//�t�F�[�h�C�����~�߂�
			key_flag = true;//�L�[����\�ɂ���
			
		}
	}

	if (Input::GetVKey('Z') == true &&key_flag==true && move_flag == false)
	{
		key_flag = false;
		move_flag = true;
	}
	//���ڂ̃t�F�[�h����
	if (move_flag == true)//�N�����Ă����
	{
		m_fade -= 0.03f;//�t�F�[�h�A�E�g���Ă���
	}

	if (m_fade <= -0.01f)//���S�ɐ^���ÂɂȂ�����
	{
		Scene::SetScene(new CSceneStageSelect);//�X�e�[�W�Z���N�g��ʂɓ]�ڂ���

	}
}

//�h���[
void CObjEnding::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1280.0f;
	src.m_bottom = 720.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1280.0f;
	dst.m_bottom = 720.0f;

	Draw::Draw(1, &src, &dst, c, 0.0f);
	Draw::Draw(0, &src, &dst, c, 0.0f);
	
}
