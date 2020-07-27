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

	m_charge_time = 0.0f;
	m_atk_time = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 1;		//�Î~�t���[���������ɂ���

	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	stay_flag = false;
	m_move = false;

	m_atk_flag = false;
	m_charge_flag = false;


	pos_init = m_x;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_ENEMY, OBJ_SINENEMY, 1);
}

//�A�N�V����
void CObjSinEnemy::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
		//�e���ˊp�x�p�Ɏ�l���̈ʒu�������Ă���
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float hx = hero->GetX();
		float hy = hero->GetY();

		//��l������苗�����ɂ�����U���s���ֈڍs
		if (((m_x + block->GetScroll() - hx <=  400.0f && m_x + block->GetScroll() - hx > 0.0f && m_move == false) ||
			(m_x + block->GetScroll() - hx >= -400.0f && m_x + block->GetScroll() - hx < 0.0f && m_move == true)) && 
			m_atk_flag==false)
		{
			m_atk_flag = true;
			m_atk_time = 300;//����݂̂����`���[�W������
		}

		//�U���Ԋu�i�߂�
		if (m_atk_flag == true && m_charge_flag == false)
		{
			m_atk_time++;
		}
		//5�b�Ԋu�Ń`���[�W�ֈڍs
		if (m_atk_time >= 30)
		{
			m_atk_time = 0;
			m_charge_flag = true;
		}
		//�`���[�W�i�߂�
		if (m_charge_flag == true)
		{
			m_charge_time++;
		}
		//1�b�`���[�W�Ŕ���
		if (m_charge_time >= 60)
		{
			//�e����
			CObjMagic* objm = new CObjMagic(m_x + 16, m_y + 16, m_move);
			Objs::InsertObj(objm, OBJ_MAGIC, 11);
			m_charge_time = 0;
			m_charge_flag = false;
		}

		//&& �Ԃɏ�Q�����锻��


		//�U���s����
		if (m_atk_flag == true && m_move == true)//�E����
		{
			if (m_x + block->GetScroll() - hx <= -400)//�������ꂽ
			{
				m_atk_flag = false;
			}
			else if (m_x + block->GetScroll() - hx >= 0)//�E�ɉ�荞�܂ꂽ
			{
				m_atk_flag = false;
				m_move = false;
			}
		}
		else if (m_atk_flag == true&&m_move==false)//������
		{
			if (m_x + block->GetScroll() - hx >= 400)//�������ꂽ
			{
				m_atk_flag = false;
			}
			else if (m_x + block->GetScroll() - hx <= 0)//�E�ɉ�荞�܂ꂽ
			{
				m_atk_flag = false;
				m_move = true;
			}
		}
		


		//�����ʒu�����苗�����ꂽ������]��
		if (m_atk_flag == false)
		{
			if (pos_init - m_x >= 400)
				m_move = true;//�E�����ɕύX

			if (pos_init - m_x <= -400)
				m_move = false;//�������ɕύX
		}
	
		//�u���b�N�Փ˂Ō����ύX
		if (m_hit_right == true && m_atk_flag == false)
		{
			m_move = true;
		}
		if (m_hit_left == true && m_atk_flag == false)
		{
			m_move = false;
		}

		//����
		if (m_move == true)
		{
			m_vx = 2.0;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (m_move == false)
		{
			m_vx = -2.0f;
			m_posture = 0.0f;
			m_ani_time += 1;
		}


		//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
		int d;
		//�u���b�N�Ƃ̓����蔻����s
		block->BlockHit(&m_x, &m_y, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
			&m_vx, &m_vy, &d
		);

		//�ʏ펞
		if (m_atk_flag == false)
		{
			//�p�x���Z
			m_r += 1.0f;

			//360���ŏ����l�ɖ߂�
			if (m_r > 360.0f)
				m_r = 0.0f;

			//�ړ�����
			m_vy = sin(3.14 / 180 * m_r);//sin�Ƃ����߂�m_vy�ɓ����

			//���x������
			m_vy *= 2.0f;

			//���C
			m_vx += -(m_vx * 0.098);

			//�ړ��x�N�g�������W�ɉ��Z����
			m_x += m_vx;
			m_y += m_vy;
		}

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_x + block->GetScroll(), m_y + block->GetScrollY());

		//�������������
		if (hit->CheckObjNameHit(OBJ_RESTART) != nullptr)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}

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
	dst.m_left = (64.0f * m_posture) + m_x + block->GetScroll();
	dst.m_right = (64 - 64.0f * m_posture) + m_x + block->GetScroll();
	dst.m_bottom = 64.0f + m_y +block->GetScrollY();

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�̏������ɕ`��
	Draw::Draw(5, &src, &dst, c, 0.0f);
}