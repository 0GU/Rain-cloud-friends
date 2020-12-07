//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjCloud.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjCloud::CObjCloud(int stage)
{
	reset = stage;
}

//�C�j�V�����C�Y
void CObjCloud::Init()
{
	m_px = 100.0f;
	m_py = 500.0f;
	m_vx = 5.0f;
	m_vy = 5.0f;
	m_hp = 1.0f;
	stay_flag = false;
	rain_flag = false;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	
	//�R���g���[���[�p
	
	m_con_x = 0.0f;
	m_con_y = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 1;		//�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 96, 96, ELEMENT_PLAYER, OBJ_CLOUD, 1);

	key_flag = false;

}

//�A�N�V����
void CObjCloud::Action()
{
	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	CObjStage* pbb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	
	m_con_num = Input::UpdateXControlerConnected();

	stay_flag = p->GetFlag();
	if (stay_flag == false)
	{
		if (m_con_num == 0)//1P�v���C��
		{
			m_con_x = Input::GetConVecStickRX(m_con_num) * 10;
			m_con_y = Input::GetConVecStickRY(m_con_num) * -10;
			if (m_con_x > 5.0f)
				m_con_x = 5.0f;
			if (m_con_x < -5.0f)
				m_con_x = -5.0f;
			if (m_con_y > 5.0f)
				m_con_y = 5.0f;
			if (m_con_y < -5.0f)
				m_con_y = -5.0f;

			if ((Input::GetConButtons(m_con_num, GAMEPAD_B) == true) && rain_flag == true && m_hp > 0.0f)
			{
				CObjRain* objr = new CObjRain(m_px, m_py + 64);
				Objs::InsertObj(objr, OBJ_RAIN, 10);
				rain_flag = false;
				Audio::Start(5);
				m_hp -= 0.01f;	//hp����
			}
			if ((Input::GetConButtons(m_con_num, GAMEPAD_B) == false) && rain_flag == false)
			{
				rain_flag = true;
			}
			if (Input::GetConButtons(m_con_num, GAMEPAD_Y) == true)
			{
				m_px = hero->GetX() - pbb->GetScroll();
				m_py = hero->GetY() - pbb->GetScrollY() - 100;//��l���̓���̏�ɉ_������
			}
			m_px += m_con_x;
			m_py += m_con_y;
		}
		else if (m_con_num == 1)//2P�v���C��
		{
			m_con_x = Input::GetConVecStickLX(1) * 10;
			m_con_y = Input::GetConVecStickLY(1) * -10;
			if (m_con_x > 5.0f)
				m_con_x = 5.0f;
			if (m_con_x < -5.0f)
				m_con_x = -5.0f;
			if (m_con_y > 5.0f)
				m_con_y = 5.0f;
			if (m_con_y < -5.0f)
				m_con_y = -5.0f;

			if (( Input::GetConButtons(m_con_num, GAMEPAD_B) == true) && rain_flag == true && m_hp > 0.0f)
			{
				CObjRain* objr = new CObjRain(m_px, m_py + 64);
				Objs::InsertObj(objr, OBJ_RAIN, 10);
				rain_flag = false;
				Audio::Start(5);
				m_hp -= 0.01f;	//hp����
			}
			if ((Input::GetConButtons(m_con_num, GAMEPAD_B) == false) && rain_flag == false)
			{
				rain_flag = true;
			}
			if (Input::GetConButtons(m_con_num, GAMEPAD_Y) == true)
			{
				m_px = hero->GetX() - pbb->GetScroll();
				m_py = hero->GetY() - pbb->GetScrollY() - 100;//��l���̓���̏�ɉ_������
			}
			m_px += m_con_x;
			m_py += m_con_y;
		}
		else
		{
			if (Input::GetVKey('C') == true  && rain_flag == true && m_hp > 0.0f)
			{
				CObjRain* objr = new CObjRain(m_px, m_py + 64);
				Objs::InsertObj(objr, OBJ_RAIN, 10);
				rain_flag = false;
				Audio::Start(5);
				m_hp -= 0.01f;	//hp����
			}
			if (Input::GetVKey('C') == false   && rain_flag == false)
			{
				rain_flag = true;
			}
			if (Input::GetVKey(VK_SPACE) == true &&key_flag==false)
			{
				Audio::Start(11);
				key_flag = true;
				m_px = hero->GetX() - pbb->GetScroll();
				m_py = hero->GetY() - pbb->GetScrollY() - 100;//��l���̓���̏�ɉ_������
			}
			if (Input::GetVKey('A') == true)
				m_px -= m_vx;
			if (Input::GetVKey('D') == true)
				m_px += m_vx;
			if (Input::GetVKey('W') == true)
				m_py -= m_vy;
			if (Input::GetVKey('S') == true)
				m_py += m_vy;
		}
		
		
		if (Input::GetVKey(VK_SPACE) == false && key_flag == true)
		{
			key_flag = false;
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
	}
	
	
	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;
	//�u���b�N�Ƃ̓����蔻����s
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
		&m_vx, &m_vy, &d,false,96.0f,96.0f
	);
	m_vx = 5.0f;
	m_vy = 5.0f;
	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + pbb->GetScroll(), m_py + pbb->GetScrollY());
	
	
}

//�h���[
void CObjCloud::Draw()
{
	int AniData[4] =
	{
		1,0,2,0
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 218.5;
	src.m_right = 217.5f + AniData[m_ani_frame] * 217.5;
	src.m_bottom = 132.5f;

	CObjStage* pbb = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//�\���ʒu�̐ݒ�
	dst.m_top = m_py + pbb->GetScrollY();
	dst.m_left = m_px + pbb->GetScroll();
	dst.m_right = m_px + 96.0f + pbb->GetScroll();
	dst.m_bottom = m_py + 96.0f + pbb->GetScrollY();

	//�`��
	Draw::Draw(8, &src, &dst, c, 0.0f);
}