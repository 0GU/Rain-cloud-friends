//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRain.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjRain::CObjRain(float x,float y)
{
	m_px = x;
	m_py = y;

}

//�C�j�V�����C�Y
void CObjRain::Init()
{
	m_vy = 5.0f;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_RAIN, 1);
}

//�A�N�V����
void CObjRain::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	m_py += m_vy;

	if (m_py > 1000.0f)
	{
		this->SetStatus(false);//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
	}
	if (hit->CheckObjNameHit(OBJ_FIRE)!=nullptr|| hit->CheckObjNameHit(OBJ_PLANT) != nullptr)
	{
		this->SetStatus(false);//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
	}
	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px, m_py);
}

//�h���[
void CObjRain::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = m_py;
	dst.m_left = m_px;
	dst.m_right = m_px + 64.0f;
	dst.m_bottom = m_py + 64.0f;

	//�`��
	Draw::Draw(7, &src, &dst, c, 0.0f);
}