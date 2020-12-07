//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjTurtle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjTurtle::CObjTurtle(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}


//�C�j�V�����C�Y
void CObjTurtle::Init()
{
	m_vx = 0.0f;			//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;		//�E����0.0f  ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;		//�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��
	m_transparent = 0.0;//�`��̓����x
	m_hp = 2;
	m_move = true;		 //true=�E false=��
	m_damege_flag = false;//��e�t���O
	m_escaoe_flag = false;//�����t���O
	m_block_type = 0;		//����ł���block�̎�ނ��m�F�p
	m_swanp = false;
	pos_init = m_px;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	stay_flag = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_RED, OBJ_TURTLE, 1);

}

//�A�N�V����
void CObjTurtle::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//�ʏ푬�x
		m_speed_power = 0.1f;
		m_ani_max_time = 4;

		//�u���b�N���������Ă���
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
		CHitBox* hit = Hits::GetHitBox(this);

		//����
		if (m_py > 1000.0f)
		{
			;
		}

		if (m_damege_flag == false)//�����@�J�ɓ�����Ƃ��̏�Œ�~
		{
			//�u���b�N�Փ˂Ō����ύX
			if (m_hit_left == true)
			{
				m_move = false;
			}
			if (m_hit_right == true)
			{
				m_move = true;
			}
		}
		//�����@���X�ɓ�����
		if (m_damege_flag == true)
		{
			m_transparent += 0.01;
		}



		//�����@�f�o�b�O�̂��߈ړ���~��
		//if (m_move == true)
		//{
		//	m_vx += m_speed_power;
		//	m_posture = 1.0f;
		//	m_ani_time += 1;
		//}
		//else if (m_move == false)
		//{
		//	m_vx -= m_speed_power;
		//	m_posture = 0.0f;
		//	m_ani_time += 1;
		//}

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

		//�u���b�N�Ƃ̓����蔻����s
		block->BlockHit(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &m_block_type
		);

		if (hit->CheckElementHit(ELEMENT_GREEN) == true && m_hit_down == false)
		{
			int py= (int)(m_py / 64) * 64;
			if (py == m_py)
				m_py = py - 64;
			else
				m_py = py;
			m_vy = 0.0f;
		}


		//�ʒu�X�V
		m_px += m_vx;
		m_py += m_vy;

		//HitBox�̈ʒu�̕ύX
		hit->SetPos(m_px + block->GetScroll(), m_py + block->GetScrollY());

		////�����@�J�ɓ�����Ɠ����~
		//if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
		//{
		//}

		//�������������
		if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}

	}

}

//�h���[
void CObjTurtle::Draw()
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
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = src.m_top + 64.0f;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = (64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (64 - 64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//�`��
	Draw::Draw(9, &src, &dst, c, 0.0f);
}