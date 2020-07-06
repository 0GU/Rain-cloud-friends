#include"GameL\DrawTexture.h"
#include"GameL\HitBoxManager.h"
#include"GameHead.h"
#include"ObjSinEnemy.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSinEnemy::CObjSinEnemy(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjSinEnemy::Init()
{
	m_r = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_ENEMY, OBJ_SINENEMY, 1);
}

//�A�N�V����
void CObjSinEnemy::Action()
{
	//�p�x���Z
	m_r += 1.0f;

	//360���ŏ����l�ɖ߂�
	if (m_r > 360.0f)
		m_r = 0.0f;

	//�ړ�����
	m_vx = -1.0f;
	m_vy = sin(3.14 / 180 * m_r);//sin�Ƃ����߂�m_vy�ɓ����

	

	//���x������
	m_vx *= 1.5f;
	m_vy *= 2.5f;

	//�ړ��x�N�g�������W�ɉ��Z����
	m_x += m_vx;
	m_y += m_vy;

	

	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;
	//�u���b�N�Ƃ̓����蔻����s
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	pb->BlockHit(&m_x, &m_y, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
		&m_vx, &m_vy, &d
	);

	

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x + pb->GetScroll(), m_y + pb->GetScrollY());

	//�������������
	if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}

	
}
//�h���[
void CObjSinEnemy::Draw()
{
	//�`��J���[���@R=RED G=Green�@B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y + block->GetScrollY();
	dst.m_left = 64.0f + m_x+block->GetScroll();
	dst.m_right = 0.0f + m_x + block->GetScroll();
	dst.m_bottom = 64.0f + m_y +block->GetScrollY();

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�̏������ɕ`��
	Draw::Draw(5, &src, &dst, c, 0.0f);
}