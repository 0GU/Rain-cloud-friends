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


	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 128, ELEMENT_RED, OBJ_STONE, 1);
}

//�A�N�V����
void CObjStone::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		

		//�u���b�N���������Ă���
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);


		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;


		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());
	}
}

//�h���[
void CObjStone::Draw()
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
	src.m_left = 0.0f ;
	src.m_right = 60.0f ;
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