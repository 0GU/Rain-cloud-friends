// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/Audio.h"

#include"GameHead.h"
#include"ObjHp.h"


void CObjHp::Init()
{
	caution_flag = true;//�m��
	danger_flag = true;//�d��
	CObjCloud* cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
	cl_MAX_HP = cloud->GetHP();
}

//�A�N�V����
void CObjHp::Action()
{
	//��l������̗͂̏��������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	he_hp = hero->GetHP();

	//�_����̗͂̏��������Ă���
	CObjCloud* cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
	cl_hp = cloud->GetHP();
	//hp�����ȉ��̏ꍇ���ʉ���炷
	if (he_hp < 0.5f &&caution_flag==true)
	{
		Audio::Start(9);
		caution_flag = false;
	}
	if (he_hp < 0.2f && danger_flag == true)
	{
		Audio::Start(10);
		danger_flag = false;
	}
	//hp��0�ȉ��Ȃ�0�ɂ���
	if (he_hp <= 0.0f)
		he_hp = 0.0f;
	if (cl_hp <= 0.0f)
		cl_hp = 0.0f;
}

//�h���[
void CObjHp::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//��l���FHP�Q�[�W
	//�؂���ʒu�̐ݒ�
	src.m_top = 17.0f;
	src.m_bottom = 27.0f;

	if (he_hp > 0.5)
	{
		src.m_left = 0.0f;
		src.m_right = src.m_left + 10.0f;


	}
	else if (he_hp > 0.2)
	{
		src.m_left = 11.0f;
		src.m_right = src.m_left + 10.0f;
	}
	else
	{
		src.m_left = 22.0f;
		src.m_right = src.m_left + 10.0f;
	}

	//�\���ʒu�̐ݒ�
	dst.m_top = 53.0f;
	dst.m_left = 53.0f;
	dst.m_right = ((174.0f - dst.m_left) * he_hp) + dst.m_left;
	dst.m_bottom = dst.m_top+10.0f;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);

	//�_�FHP�Q�[�W
	//�؂���ʒu�̐ݒ�
	src.m_top = 17.0f;
	src.m_bottom = 27.0f;

	if ((cl_hp/cl_MAX_HP) > 0.5)
	{
		src.m_left = 33.0f;
		src.m_right = src.m_left + 10.0f;
	}
	else if ((cl_hp / cl_MAX_HP) > 0.2)
	{
		src.m_left = 11.0f;
		src.m_right = src.m_left + 10.0f;
	}
	else
	{
		src.m_left = 22.0f;
		src.m_right = src.m_left + 10.0f;
	}

	//�\���ʒu�̐ݒ�
	dst.m_top = 73.0f;
	dst.m_left = 53.0f;
	dst.m_right = ((174.0f - dst.m_left) * (cl_hp/cl_MAX_HP)) + dst.m_left;
	dst.m_bottom = dst.m_top + 10.0f;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);


	//HP�o�[�O�g
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 127.0f;
	src.m_bottom = 16.0f;

	//�\���ʒu�F��l��
	dst.m_top = 50.0f;
	dst.m_left = 50.0f;
	dst.m_right = 177.0f;
	dst.m_bottom = 66.0f;
	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);

	//�\���ʒu�F�_
	dst.m_top = 70.0f;
	dst.m_bottom = 86.0f;
	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 218.5f;
	src.m_bottom = 133.5f;


	//�\���ʒu�̐ݒ�
	dst.m_top = 64.0f;;
	dst.m_left = 16.0f;
	dst.m_right = 48.0f;
	dst.m_bottom = 96.0f;

	//�`��
	Draw::Draw(8, &src, &dst, c, 0.0f);

}