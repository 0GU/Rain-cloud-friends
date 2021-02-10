// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include"GameL/DrawFont.h"
#include"GameL/Audio.h"
#include"GameL/UserData.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjSand.h"
CObjSand::CObjSand(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}

void CObjSand::Init()
{
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_BLUE, OBJ_SAND, 1);
	m_hit_rain = false;//�J�ɓ����Ă��Ȃ�
	m_fade_num = 1.0f;
}

//�A�N�V����
void CObjSand::Action()
{
	int d=0;
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CHitBox* hit = Hits::GetHitBox(this);

	//�ʒu�̍X�V�p�Ɏ�l���̈ʒu�������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());


	//�����@�J�ɓ�����Ɠ����~
	if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
	{
		Audio::Stop(31);
		Audio::Start(31);
		m_hit_rain = true;
	}
	//�����@���X�ɓ�����
	if (m_hit_rain == true)
	{
		m_fade_num -= 0.05;
	}
	if (m_fade_num <= 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		block->DeleteSand(m_py / 64.0f, m_px / 64.0f);//�v���C���[�̍��W���u���b�N��(64px)�Ŋ������u���b�N���폜
	}
}

//�h���[
void CObjSand::Draw()
{
	//�`��J���[���
	float	c[4] = { 1.0f,1.0f,1.0f,m_fade_num };//


	RECT_F src; //�`�挳�؂���ʒu�̐ݒ�
	RECT_F dst; //�`���\���ʒu

	//���u���b�N�̈ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;
	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//�\���ʒu�̐ݒ�
	dst.m_top = m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	Draw::Draw(35, &src, &dst, c, 0);
}

//�����@�J�ɓ�����Ɠ����~
void CObjSand::RainHit(int* hp, bool* damege)
{
	*hp -= 1;
	if (*hp <= 0)
		*damege = true;
}