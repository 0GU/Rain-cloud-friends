// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjPlant.h"

CObjPlant::CObjPlant(float x, float y,int count)
{
	m_px = x;			//�ʒu
	m_py = y;
	grow = count;		//����������傫��

}


void CObjPlant::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;		//�Î~�t���[���������ɂ���

	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��
	stay_flag = false;
	grow_flag = true;
	HP = 3;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_RED, OBJ_PLANT, 1);
}

//�A�N�V����
void CObjPlant::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		

		//�u���b�N���������Ă���
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)	//�J���������HP����
		{
			HP -= 1;
		}
		if (HP <= 0&&grow_flag==true)					//HP0�Ő���
		{
				
					CObjGrowPlant* obj = new CObjGrowPlant(m_px,m_py-grow*64,grow,true);	//�Ԃ̕����̃I�u�W�F�N�g�쐬
					Objs::InsertObj(obj, OBJ_PLANT, 10);
			
					CObjGrowPlant* objs = new CObjGrowPlant(m_px, m_py - (grow-1) * 64,grow, false);	//�c�^�̕����̃I�u�W�F�N�g�쐬
					Objs::InsertObj(objs, OBJ_PLANT, 10);

			grow_flag = false;
			this->SetStatus(false);//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
		}
	}
}

//�h���[
void CObjPlant::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f  ;
	src.m_right = 128.0f;
	src.m_bottom = src.m_top + 128.0f;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//�\���ʒu�̐ݒ�
	dst.m_top = m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//�`��
	Draw::Draw(10, &src, &dst, c, 0.0f);
}