//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}


//�C�j�V�����C�Y
void CObjEnemy::Init()
{
	m_vx = 0.0f;			//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;		//�E����0.0f  ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;		//�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	m_move = true;		 //true=�E false=��


	pos_init = m_px;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	stay_flag = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);

}

//�A�N�V����
void CObjEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//�ʏ푬�x
		m_speed_power = 0.5f;
		m_ani_max_time = 4;
		
		//�u���b�N���������Ă���
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

		//����
		if (m_py > 1000.0f)
		{
			;
		}

		//���Ԋu�ŃW�����v
		if (m_hit_down==true)
		{
			m_vy -= 10.0f;
		}

		//�u���b�N�Փ˂Ō����ύX
		if (m_hit_left == true)
		{
			m_move = false;
		}
		if (m_hit_right == true)
		{
			m_move = true;
		}

		//����
		if (m_move == true)
		{
			m_vx += m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (m_move == false)
		{
			m_vx -= m_speed_power;
			m_posture = 0.0f;
			m_ani_time += 1;
		}

		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		if (m_ani_frame == 4)
		{
			m_ani_frame = 0;
		}


		//���C
		m_vx += -(m_vx * 0.098);

		//���R�������x
		m_vy += 9.8 / (16.0f);

		//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
		int d;
		//�u���b�N�Ƃ̓����蔻����s
		block->BlockHit(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &d
		);

		//�ʒu�X�V
		m_px += m_vx;
		m_py += m_vy;

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

		//�������������
		if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}

	}
	
}

//�h���[
void CObjEnemy::Draw()
{
	int AniData[4] =
	{
		1,0,2,0,
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,0.5f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 255;
	src.m_right = 255.0f + AniData[m_ani_frame] * 255;
	src.m_bottom = src.m_top + 255.0f;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = (64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (64 - 64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//�`��
	Draw::Draw(11, &src, &dst, c, 0.0f);
}

//ModeChange�֐�
//����1 float* x		:�Gobj��X�ʒu
//����2 float* y		:�Gobj��Y�ʒu
//����3 float* hx		:��l��obj��X�ʒu
//����4 float* hy		:��l��obj��Y�ʒu
//����5 float* pos_init	:�Gobj�̏����ʒu
//����6 bool* mode		:�G�̃��[�h�̏�Ԃ�Ԃ�(true=������ false=�ʏ���)
//����7 bool* posture	:�G�̌�����Ԃ�(true=�E false=��)
//����8 bool  searchY	:�������G�p�@�㉺�̍��G�͈͂��L����
//��l���ƓG�̈ʒu�ɉ����ă��[�h�̐؂�ւ����s���֐�
void CObjEnemy::ModeChange(float* x, float* y, float* hx, float* hy, float* pos_init, bool* mode, bool* posture, bool searchY)
{
	int range = 1;

	if (searchY == true)
		range = 8;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//��l������苗�����ɂ�����
	//1�s��:���Ɉ�苗���@2�s��:�E�Ɉ�苗���@3�s��:�㉺�Ɉ�苗��
	if (((*x + block->GetScroll() - *hx <= 400.0f && *x + block->GetScroll() - *hx > 0.0f && *posture == false) ||
		(*x + block->GetScroll() - *hx >= -400.0f && *x + block->GetScroll() - *hx < 0.0f && *posture == true))
		&& *y + block->GetScrollY() - *hy <= 200 * range && *y + block->GetScrollY() - *hy >= -200 * range)
	{
		*mode = true;
	}

	//�����ύX�Ɖ���
	if (*mode == true && *posture == false)//�������ǐ�
	{
		if (*x + block->GetScroll() - *hx >= 400)//�������ꂽ
		{
			*mode = false;
		}
		else if (*x + block->GetScroll() - *hx <= 0)//�E�ɉ�荞�܂ꂽ
		{
			*posture = true;
		}
	}
	else if (*mode == true && *posture == true)//�E�����ǐ�
	{
		if (*x + block->GetScroll() - *hx <= -400)//�������ꂽ
		{
			*mode = false;
		}
		else if (*x + block->GetScroll() - *hx >= 0)//���ɉ�荞�܂ꂽ
		{
			*posture = false;
		}
	}
	if (*mode == true && (*y + block->GetScrollY() - *hy >= 200 * range || *y + block->GetScrollY() - *hy <= -200 * range))//�㉺�ŋ������ꂽ
	{
		*mode = false;
	}
}