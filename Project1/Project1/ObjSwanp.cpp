// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"
#include"GameL/Audio.h"

#include"GameHead.h"
#include"ObjSwanp.h"

CObjSwanp::CObjSwanp(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;

}

void CObjSwanp::Init()
{
	m_swanp_time = 0;
	m_hp = 3;
	m_swanp_flag = false;
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GREEN, OBJ_SWANP, 1);
}

//�A�N�V����
void CObjSwanp::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CHitBox* hit = Hits::GetHitBox(this);

	if (stay_flag == false)
	{
		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
		{
			m_swanp_flag = true;
			m_swanp_time = 300;
			//HitBox�̑�����ύX
			Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
			Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_RED, OBJ_SWANP, 1);
		}
		if (m_swanp_flag == true)
		{
			if (m_swanp_time == 0)
			{
				m_swanp_flag = false;
				//HitBox�̑�����ύX
				Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
				Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GREEN, OBJ_SWANP, 1);
			}
			m_swanp_time--;
		}
		//HitBox�̈ʒu�̕ύX
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());
	}
}

//�h���[
void CObjSwanp::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float sc[4] = { 0.8f,0.8f,0.8f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	//�\���ʒu�̐ݒ�
	dst.m_top = m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//�`��
	if (m_swanp_flag == true)
		Draw::Draw(30, &src, &dst, sc, 0.0f);
	else
		Draw::Draw(30, &src, &dst, c, 0.0f);

}