//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL/DrawFont.h"
#include"GameL/Audio.h"

#include "GameHead.h"
#include "ObjKey.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;



CObjKey::CObjKey(float x, float y, int k_num)
{
	m_x = x;
	m_y = y;
	Key_num = k_num;
}

void CObjKey::Init()
{

	delete_flag = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_RED, OBJ_KEY, 1);
}

void CObjKey::Action()
{
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + block->GetScroll(), m_y + block->GetScrollY());

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hero->SetKey(Key_num);

		this->SetStatus(false);//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
	}
		
	


}

void CObjKey::Draw()
{

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = src.m_top + 512.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 0.0f + m_x + block->GetScroll();
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = 64.0f + m_y + block->GetScrollY();

	//�`��
	Draw::Draw(13, &src, &dst, c, 0.0f);
}

