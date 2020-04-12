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
	m_py = y;

}

void CObjFire::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;		//�Î~�t���[���������ɂ���

	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_RED, OBJ_FIRE, 1);
}

//�A�N�V����
void CObjFire::Action()
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
	hit->SetPos(m_px + block->GetScroll(), m_py);
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
	dst.m_top = -64.0f + m_py;						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f  + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}