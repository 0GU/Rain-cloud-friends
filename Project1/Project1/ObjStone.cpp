// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjFire.h"

CObjFire::CObjFire(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y - 64.0;

}


void CObjFire::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;		//�Î~�t���[���������ɂ���

	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��
	stay_flag = false;

	HP = 3;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 128, ELEMENT_RED, OBJ_FIRE, 1);
}

//�A�N�V����
void CObjFire::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		m_ani_time++;
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		if (m_ani_frame == 6)
		{
			m_ani_frame = 0;
		}

		//�u���b�N���������Ă���
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
		{
			HP -= 1;
		}
		if (HP <= 0)
		{
			this->SetStatus(false);//���g�ɍ폜���߂��o��
			Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
		}
	}
}

//�h���[
void CObjFire::Draw()
{
	int AniData[6] =
	{
		0,1,2,1,0,3
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 60.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = src.m_top + 128.0f;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//�\���ʒu�̐ݒ�
	dst.m_top = m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 128.0f + m_py + block->GetScrollY();

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}