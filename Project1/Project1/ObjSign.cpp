// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjSign.h"
#include "GameL/DrawFont.h"

CObjSign::CObjSign(float x, float y,int i)
{
	m_px = x;			//�ʒu
	m_py = y;
	sign_num = i;
}
void CObjSign::Init()
{
	m_hit_f = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ITEM, OBJ_SIGN, 1);

}

//�A�N�V����
void CObjSign::Action()
{
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());
	//�Ŕ�
	CObjHero* h = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_hit_f = true;
	}
	else
	{
		m_hit_f = false;
	}
	
}

//�h���[
void CObjSign::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//hoge1
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	dst.m_top = m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();
	//�`��
	Draw::Draw(34, &src, &dst, c, 0.0f);
	wchar_t str[256];
	if (m_hit_f == true)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 500.0f;
		src.m_bottom = 300.0f;
		dst.m_top =125.0f;						//���`��ɑ΂��ăX�N���[���̉e����^����
		dst.m_left =50.0f;
		dst.m_right = 550.0f;
		dst.m_bottom = 425.0f;
		Draw::Draw(35+sign_num, &src, &dst, c, 0.0f);
	}
}