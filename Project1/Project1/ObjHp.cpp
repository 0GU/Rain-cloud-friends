// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"

#include"GameHead.h"
#include"ObjHp.h"


void CObjHp::Init()
{

}

//�A�N�V����
void CObjHp::Action()
{
	//��l������̗͂̏��������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	hp_len = hero->GetHP();

	if (hp_len <= 0.0f)
		hp_len = 0.0f;
}

//�h���[
void CObjHp::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//HP�Q�[�W
	//�؂���ʒu�̐ݒ�
	src.m_top = 17.0f;
	src.m_bottom = 27.0f;

	if (hp_len > 0.5)
	{
		src.m_left = 0.0f;
		src.m_right = src.m_left + 10.0f;
	}
	else if (hp_len > 0.2)
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
	dst.m_right = ((174.0f - dst.m_left) * hp_len) + dst.m_left;
	dst.m_bottom = 63.0f;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);


	//HP�o�[�O�g
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 127.0f;
	src.m_bottom = 16.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 50.0f;
	dst.m_left = 50.0f;
	dst.m_right = 177.0f;
	dst.m_bottom = 66.0f;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);


}