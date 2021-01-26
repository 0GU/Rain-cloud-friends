// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjStone.h"

CObjStone::CObjStone(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;

}



void CObjStone::Init()
{

	stay_flag = false;
	m_vx = 0;
	m_vy = 10;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	stay_flag = false;
	hit_flag = false;
	lock_flag_r = false;
	lock_flag_l = false;
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 128, 64, ELEMENT_RED, OBJ_STONE, 1);
}

//�A�N�V����
void CObjStone::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

		//�u���b�N���������Ă���
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{

		//���R���������@�I�u�W�F�N�g�̗h���h����
		if (m_vy<0.45)
		{
			m_vy += 0.15;
		}
		//��������ۂ͎��R�����^�����g�p����
		else
		{
			m_vy += 9.8 / (16.0f);
		}
			

		//��l���Ɠ������Ă���
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetX()-block->GetScroll() + 64 > m_px && 
			hero->GetX() - block->GetScroll() < m_px + 124 && hero->GetY()-block->GetScrollY() == m_py)
		{
			hero->SetSthit(true);
			m_vx = hero->GetVX() ;
			
		}
	

		//�u���b�N�Ƃ̓����蔻����s

		block->BlockHitStone(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &m_block_type
		);
	
		if (m_hit_left==true)
		{
			lock_flag_l= true;
		}
		else if (m_hit_right == true)
		{
			lock_flag_r = true;
		}
		
		if (m_hit_up==false)
		{
			lock_flag_l = false;
			lock_flag_r = false;
		}


		//HitBox�̈ʒu�̕ύX
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());


		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;
		m_vx = 0;

	}
}

//�h���[
void CObjStone::Draw()
{

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f ;
	src.m_right = 512.0f ;
	src.m_bottom = src.m_top + 512.0f;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//�\���ʒu�̐ݒ�
	dst.m_top = m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 128.0f + m_px + block->GetScroll();
	dst.m_right = -8.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//�`��
	Draw::Draw(13, &src, &dst, c, 0.0f);
}