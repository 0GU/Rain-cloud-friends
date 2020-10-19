//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRushEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjRushEnemy::CObjRushEnemy(float x, float y)
{
	m_px = x;			//�ʒu
	m_py = y;
}


//�C�j�V�����C�Y
void CObjRushEnemy::Init()
{
	m_vx = 0.0f;			//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;		//�E����0.0f  ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;		//�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	m_move = false;		 //true=�E false=��

	m_rush = false;//�ʏ��Ԃŏ�����
	m_rush_time = 0;

	sleep_flag=false;//�f�o�b�O�p��~�t���O

	pos_init = m_px;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	stay_flag = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 75, 60, ELEMENT_ENEMY, OBJ_RUSH_ENEMY, 1);

}

//�A�N�V����
void CObjRushEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		//�ʏ푬�x
		if (m_rush == false)
		{
			
			m_ani_max_time = 4;
		}

		//�u���b�N���������Ă���
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
		sl_x = block->GetScroll();
		sl_y = block->GetScrollY();

		//�ʒu�̍X�V�p�Ɏ�l���̈ʒu�������Ă���
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		
	
		
		//HITBOX���������Ă���
		CHitBox* hit = Hits::GetHitBox(this);
		
		//����
		if (m_py > 1000.0f)
		{
			;
		}

		//�u���b�N�Փ˂Ō����ύX
		if (m_hit_left == true)
			m_move = false;
		if (m_hit_right == true)
			m_move = true;

		//�f�o�b�O�p��~�t���O
		if (Input::GetVKey('P') == true)
		{
			if (sleep_flag == false)
				sleep_flag = true;
		}
		else if (Input::GetVKey('O') == true)
		{
			if (sleep_flag == true)
				sleep_flag = false;
		}

		if (sleep_flag == false)
		{


			//�ʏ�ړ�
			if (m_move == true && m_rush_time != 60)
			{
				m_vx += m_speed_power;
				m_posture = 1.0f;
				m_ani_time += 1;
			}
			else if (m_move == false && m_rush_time != 60)
			{
				m_vx -= m_speed_power;
				m_posture = 0.0f;
				m_ani_time += 1;
			}

			//�ːi��ԕω�
			CObjEnemy* enemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
			

			if (m_rush_time < 60 && hero->GetHitDown() != 5)
			{
				hx = hero->GetX();
				hy = hero->GetY();
				enemy->ModeChange(&m_px, &m_py, &hx, &hy, &pos_init, &m_rush, &m_move, false);
			
			}
				

			//�ːi��ԁ@1�b���ߍs���̂��Ɠːi����
			if (m_rush == true && m_rush_time < 60)
			{
				m_rush_time++;
				m_vx = 0.0f;
				if (m_rush_time == 60)
					m_rush_time++;
			}
			if (m_rush_time > 60)
			{

				//��l���̈ʒu��ʉ߂�����u���[�L������
				if ((m_px + sl_x +75 > hx && m_move == true) || (m_px + sl_x < hx && m_move == false))
				{
					if ((m_vx < 9.0f && m_move == true) || (m_vx > -9.0f && m_move == false))//��葬�x�ȉ��œːi�I��
					{
						m_rush_time = 0;
						m_rush = false;
						m_vx = 0.0f;
						//���]������
						if (m_move == true)
							m_move = false;
						else
							m_move = true;
					}
				}
				else if (hero->GetHitDown() != 5)
				{
					if (m_move == true)
						m_vx += m_speed_power * 3.0f;
					if (m_move == false)
						m_vx += -m_speed_power * 3.0f;//
				}
				if (m_rush == true)
				{
					if (m_vx > 9.0f)
						m_vx = 9.0f;
					if (m_vx < -9.0f)
						m_vx = -9.0f;
				}
			}
		}
		//�A�j���[�V�����i�߂�
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		if (m_ani_frame == 4)
		{
			m_ani_frame = 0;
		}

		//�����ʒu�����苗�����ꂽ������]��
		if (m_rush == false)
		{
			if (pos_init - m_px >= 400)
				m_move = true;//�E�����ɕύX

			if (pos_init - m_px <= -400)
				m_move = false;//�������ɕύX
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

		//if ((m_speed_power <= 5.0f && m_speed_power >= 0.0f && m_move == true) || (m_speed_power >= -5.0f && m_speed_power < 0.0f && m_move == false))
		//	m_rush_dist += m_speed_power;

		//HitBox�̈ʒu�̕ύX
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
void CObjRushEnemy::Draw()
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
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom =256.0f;

	//�u���b�N���������Ă���
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + block->GetScrollY();						//���`��ɑ΂��ăX�N���[���̉e����^����
	dst.m_left = (64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (64 - 64.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py + block->GetScrollY();

	//�`��
	Draw::Draw(14, &src, &dst, c, 0.0f);
}
