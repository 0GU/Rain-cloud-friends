// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/Audio.h"
#include "GameL/HitBoxManager.h"

#include"GameHead.h"
#include"ObjMagic.h"

CObjMagic::CObjMagic(float x, float y,bool posture)
{
	m_px = x;
	m_py = y;
	m_posture = posture;
}

void CObjMagic::Init()
{
	m_check = true;

	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;

	m_ani_frame = 0;
	m_ani_time = 0;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_ENEMY, OBJ_MAGIC, 1);


}

//�A�N�V����
void CObjMagic::Action()
{
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = hero->GetX()-(m_px+block->GetScroll());	//��l���@�̂����W
	float y = hero->GetY()-(m_py+block->GetScrollY());	//��l���@�̂����W

	m_r = atan2(-y, x) * 180.0f / 3.14f;
	if (m_r < 0)
	{
		m_r = 360 - abs(m_r);
	}


	//���˂����Ƃ�������l���Ƃ̍��W�̍��𒲂ׂ�
	if (m_check == true)
	{
		m_vx = cos(3.14/180*m_r);
		m_vy = sin(3.14 / 180 * m_r);

		m_check = false;
	}



	//���x
	m_px += m_vx * 2.0f;
	m_py -= m_vy * 2.0f;

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY(),32.0f,32.0f);

	//��l���ƐڐG���Ă��邩���ׂ�
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr )
	{
		this->SetStatus(false);	//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
	}

	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;
	//�u���b�N�Ƃ̓����蔻����s
	block->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
		&m_vx, &m_vy, &d,false,32.0f,32.0f
	);
	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);	//���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);//�ۗL����HitBox�ɍ폜����
	}

	////�̈�O�ɏo���e�ۂ�j������
	//bool check = CheckWindow(m_px, m_py, -32.0f, -32.0f, 800.0f, 600.0f);
	//if (check == false)
	//{
	//	this->SetStatus(false);     //���g�ɍ폜���߂��o���B
	//	Hits::DeleteHitBox(this);   //�e�ۂ����L����HitBox�ɍ폜����B

	//	return;
	//}

}

//�h���[
void CObjMagic::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,1.0f };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//�\���ʒu�̐ݒ�
	dst.m_top = m_py + block->GetScrollY();
	dst.m_left = m_px + block->GetScroll();
	dst.m_right = m_px + 32.0f + block->GetScroll();
	dst.m_bottom = m_py + 32.0f + block->GetScrollY();

	//�`��
	Draw::Draw(7, &src, &dst, c, 0.0f);
}