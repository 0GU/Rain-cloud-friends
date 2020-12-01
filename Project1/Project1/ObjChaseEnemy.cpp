// �g�p����w�b�_�[�t�@�C��
#include"GameL/DrawTexture.h"
#include"GameL/WinInputs.h"
#include"GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjChaseEnemy.h"

CObjChaseEnemy::CObjChaseEnemy(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}

void CObjChaseEnemy::Init()
{
	m_vx = 0.0f;			//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;		//�E����0.0f  ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;		//�Î~�t���[���������ɂ���

	m_speed_power = 0.2f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	m_move = true;		 //true=�E false=��

	m_transparent = 0.0;//�`��̓����x
	m_hp = 2;
	m_damege_flag = false;//��e�t���O
	m_escaoe_flag = false;//�����t���O

	m_chase = false;//�ʏ��Ԃŏ�����

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
void CObjChaseEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//�ʏ푬�x
		m_speed_power = 0.4f;
		m_ani_max_time = 4;

		//�u���b�N���������Ă���
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

		//�ʒu�̍X�V�p�Ɏ�l���̈ʒu�������Ă���
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float hx = hero->GetX();
		float hy = hero->GetY();

		//����
		if (m_py > 1200.0f)
		{
			;
		}

		//�ǐՏ�ԕω�
		CObjEnemy* enemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
		enemy->ModeChange(&m_px, &m_py, &hx, &hy, &pos_init, &m_chase, &m_move,false);

		//���Ԋu�ŃW�����v
		if (m_hit_down == true)
		{
			//m_vy -= 10.0f;
		}


		//�����ʒu�����苗�����ꂽ������]��
		if (m_chase == false)
		{
			if (pos_init - m_px >= 400)
				m_move = true;//�E�����ɕύX

			if (pos_init - m_px <= -400)
				m_move = false;//�������ɕύX
		}

		//�u���b�N�Փ˂Ō����ύX
		if (m_hit_right == true && m_chase == false)
		{
			m_move = true;
		}
		if (m_hit_left == true && m_chase == false)
		{
			m_move = false;
		}
		//�����@���X�ɓ�����
		if (m_damege_flag == true)
		{
			m_transparent += 0.01;
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

		//�����@�J�ɓ�����Ɠ����~
		if (hit->CheckObjNameHit(OBJ_RAIN) != nullptr)
		{
			enemy->RainHit(&m_hp, &m_move, &m_damege_flag);
			m_chase = false;
		}

		//�������������
		if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
		//�����I�����������
		if (m_escaoe_flag == true)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}

}

//�h���[
void CObjChaseEnemy::Draw()
{
	int AniData[4] =
	{
		1,0,2,0,
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f - m_transparent };
	if (c[3] <= 0.0f)
		m_escaoe_flag = true;

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