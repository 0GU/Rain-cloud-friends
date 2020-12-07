//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL/DrawFont.h"
#include"GameL/Audio.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjHero::CObjHero(int stage)
{
	reset = stage;
}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 70.0f;			//�ʒu
	m_py = 900.0f;
	m_vx = 0.0f;			//�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;		//�E����0.0f  ������1.0f

	m_py_h = 0.0f;

	m_hp = 1.0f;			//�̗́i���j
	m_hit_time = 0;		//�_���[�W�Ԋu

	m_ani_time = 0;
	m_ani_frame = 1;		//�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 3;  //�A�j���[�V�����Ԋu��

	m_enemynum = 0;	//�ڐG���̎�ޔ��ʗp
	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	hit_flag = true;
	stay_flag = false;

	climb_flag = false;

	falldamage_flag = false;

	reset_falldamage_cacancel_flag = true;

	landing_flag = false;

	over_flag = false;

	m_block_type = 0;		//����ł���block�̎�ނ��m�F�p

	//�R���g���[���[�p���ϐ�
	m_con_x = 0.0f;
	m_con_y = 0.0f;

	m_con_flag = false;

	Audio_time = 0.0f;
	Audio_time_max = 1.0f;
	Audio_f = true;
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 40, 64, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	m_con_num = Input::UpdateXControlerConnected();
	if (m_hit_time > 0)
		m_hit_time--;

	CObjPose* p = (CObjPose*)Objs::GetObj(OBJ_POSE);
	stay_flag = p->GetFlag();

	//HP��0�Ń��X�^�[�g�i���j
	if (m_hp <= 0.0f&&over_flag==false)
	{
		over_flag = true;
		m_ani_frame = 0;
		m_ani_time = 0;
		//Scene::SetScene(new CSceneGameMain(reset));
	}

	//�u���b�N�Ƃ̓����蔻����s
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);


	//�����_���[�W����-----------------------------------------------------------------------------------------------------------------------------
	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);

	if (over_flag == false)
	{
		if (m_hit_down == true)
		{
			
			if (falldamage_flag == false)
			{
				falldamage_flag = true;
				if ((m_py - m_py_h - block->GetScrollY()) / 64 >= 5 && hit->CheckElementHit(ELEMENT_IVY) == false && reset_falldamage_cacancel_flag == false)
				{
					Audio::Stop(3);
					Audio::Start(4);
					m_hp -= 0.04 * (int)(m_py - m_py_h - block->GetScrollY()) / 64;
				}
			}
			reset_falldamage_cacancel_flag = false;
			m_py_h = m_py - block->GetScrollY();
		}

		if (m_hit_down == false)
		{
			falldamage_flag = false;
			landing_flag = false;
			if (m_py_h > m_py - block->GetScrollY())
			{
				m_py_h = m_py - block->GetScrollY();
			}
		}
		//----------------------------------------------------------------------------------------------------------------------------------------------
		if (m_hit_down == true)
		{
			if (landing_flag == false)
			{
				landing_flag = true;//���n���܂���
				if (landing_flag == true)
				{
					Audio::Start(3);
				}
			}

		}

		if (stay_flag == false)
		{
			//�R���g���[���[���쉼
			m_con_x = Input::GetConVecStickLX(0);
			if (m_con_num==0 || m_con_num==1)
			{
				if (m_con_x == 0.0f)
				{
					m_con_flag = false;
				}
				if (Input::GetConButtons(0, GAMEPAD_A) == true)
				{
					if (m_hit_down == true)
					{
						Audio::Start(2);
						m_vy = -8;
						m_hit_down == false;
					}

				}
				if (Input::GetConButtons(0, GAMEPAD_X) == true)
				{
					//�_�b�V�����̑��x
					if (m_con_x > 0.8f)
						m_con_x = 0.8f;
					if (m_con_x < -0.8f)
						m_con_x = -0.8f;
					m_ani_max_time = 1.5f;
				}
				else
				{
					//�ʏ푬�x
					if (m_con_x > 0.5f)
						m_con_x = 0.5f;
					if (m_con_x < -0.5f)
						m_con_x = -0.5f;
					m_ani_max_time = 4;
				}
				if (m_con_x > 0.0f)
				{
					m_vx += m_con_x;
					m_posture = 1.0f;
					m_ani_time += 1;
					m_con_flag = true;
				}
				if (m_con_x < 0.0f)
				{
					m_vx += m_con_x;
					m_posture = 0.0f;
					m_ani_time += 1;
					m_con_flag = true;
				}
				//���~����
				if (Input::GetConVecStickLY(0) > 0.0f && climb_flag == true && hit->CheckElementHit(ELEMENT_FLOWER) == true)
				{
					m_vy = 0.0f;
				}
				else if (Input::GetConVecStickLY(0) == 0.0f && climb_flag == true && hit->CheckElementHit(ELEMENT_FLOWER) == false)
				{
					//����Ȃ��̏ꍇ�͂��̏ꏊ�ɗ��܂�
					m_vy = 0.0f;
				}
				else if (Input::GetConVecStickLY(0) > 0.1f && climb_flag == true/* && hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{
					m_vy = -3.0f;
					m_ani_time += 1;
				}
				else if (Input::GetConVecStickLY(0) < -0.1f && climb_flag == true /*&& hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{
					m_vy = +3.0f;
					m_ani_time += 1;
				}
			}
			if(m_con_num==5)
			{
				//X�L�[���͂ŃW�����v
				if (Input::GetVKey('X') == true)
				{
					if (m_hit_down == true)
					{
						Audio::Start(2);
						m_vy = -9;
					}
				}

				//Z�L�[���͂ő��x�A�b�v
				if (Input::GetVKey('Z') == true)
				{
					//�_�b�V�����̑��x
					m_speed_power = 0.8f;
					m_ani_max_time = 4;
				}
				else
				{
					//�ʏ푬�x
					m_speed_power = 0.5f;
					m_ani_max_time = 4;
				}



				//�L�[�̓��͕���
				if (Input::GetVKey(VK_RIGHT) == true)
				{
					//Audio::Start(3);
					m_vx += m_speed_power;
					m_posture = 1.0f;
					m_ani_time += 1;
				}

				else if (Input::GetVKey(VK_LEFT) == true)
				{
					m_vx -= m_speed_power;
					m_posture = 0.0f;
					m_ani_time += 1;
				}




				//���~����
				if (Input::GetVKey(VK_UP) == true && climb_flag == true && hit->CheckElementHit(ELEMENT_FLOWER) == true)
				{
					//�A���̈�ԏ�ɓ������Ă���ꍇ�͏�Ɉړ��s��
					m_vy = 0.0f;
				}
				else if (Input::GetVKey(VK_UP) == false && Input::GetVKey(VK_DOWN) == false && climb_flag == true && hit->CheckElementHit(ELEMENT_FLOWER) == false)
				{
					//����Ȃ��̏ꍇ�͂��̏ꏊ�ɗ��܂�
					Audio::Stop(2);
					m_vy = 0.0f;
				}
				else if (Input::GetVKey(VK_UP) == true && climb_flag == true /*&& hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{
					if (Audio_time == 0.00f)
					{
						Audio::Start(12);
					}
					Audio_time += 0.04f;
					m_vy = -3.0f;
					m_ani_time += 1;

				}
				else if (Input::GetVKey(VK_DOWN) == true && climb_flag == true /*&& hit->CheckElementHit(ELEMENT_FLOWER) == false*/)
				{
					if (Audio_time == 0.00f)
					{
						Audio::Start(12);
					}
					Audio_time += 0.04f;
					m_vy = +3.0f;
					m_ani_time += 1;
					Audio::Stop(2);
				}

			}
			//1.
			//2.
			//3.
			if ((m_con_num != 5 && m_con_flag == false && Input::GetConVecStickLY(m_con_num) == 0.0f) ||
				(m_con_num == 5 && climb_flag == false && Input::GetVKey(VK_RIGHT) == false && Input::GetVKey(VK_LEFT) == false) ||
				(m_con_num == 5 && climb_flag == true  && Input::GetVKey(VK_UP)    == false && Input::GetVKey(VK_DOWN) == false))
			{
				m_ani_frame = 1;  //�L�[���͂������ꍇ�͐Î~�t���[���ɂ���
				m_ani_time = 0;
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
			m_vx += -(m_vx * 0.128);

			//���R���������@�I�u�W�F�N�g�̗h���h����
			if (climb_flag == false /*|| Input::GetVKey(VK_UP) == false*/)
			{
				if (m_vy < 0.45)
				{
					m_vy += 0.4;
				}
				else
				{
					//��������ۂ͎��R�����^�����g�p����
					m_vy += 6.8 / (16.0f);
				}
			}


			pb->BlockHit(&m_px, &m_py, true,
				&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right,
				&m_vx, &m_vy, &m_block_type, climb_flag, 64.0f, 64.0f
			);



			//�����ړ��ɂ��Block����
			bool b;
			float pxx, pyy, r;

			if (pb->GetScroll() > 0)
				pb->SetScroll(0);


			m_enemynum = 0;//�擾��������̂�h��

			//�G�Ɠ������Ă��邩�m�F
			if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
			{
				Audio::Start(4);
				m_enemynum = 1;
				EnemyHit(m_enemynum);
			}
			
			if (hit->CheckObjNameHit(OBJ_FIRE) != nullptr)
			{
				if (Audio_time == 0.00f)
				{
					Audio::Start(4);
				}
				Audio_time += 0.05f;
				m_enemynum = 2;
				EnemyHit(m_enemynum);
			}

			if (hit->CheckObjNameHit(OBJ_SINENEMY) != nullptr)
			{
				Audio::Start(4);
				m_enemynum = 3;
				EnemyHit(m_enemynum);
			}
			if (hit->CheckObjNameHit(OBJ_MAGIC) != nullptr)
			{
				Audio::Start(4);
				m_enemynum = 4;
				EnemyHit(m_enemynum);
			}
			if (hit->CheckObjNameHit(OBJ_RUSH_ENEMY) != nullptr)
			{
				Audio::Start(4);
				m_enemynum = 5;


				CObjRushEnemy* Re = (CObjRushEnemy*)Objs::GetObj(OBJ_RUSH_ENEMY);
				if (Re->GetY() + pb->GetScrollY() < m_py + 50)
				{
					if (Re->GetX() + pb->GetScroll() + 75 < m_px + 32)
					{
						if (m_hit_time == 0)
						{
							m_vx = 20.0f;
							m_vy -= 10.0f;
						}
					}
					if (Re->GetX() + pb->GetScroll() > m_px + 32)
					{
						if (m_hit_time == 0)
						{
							m_vx = -20.0f;
							m_vy -= 10.0f;
						}

					}
				}

				EnemyHit(m_enemynum);

			}
			if (hit->CheckObjNameHit(OBJ_SWANP) != nullptr)
			{
				m_enemynum = 6;
				EnemyHit(m_enemynum);
			}


			//���~����  ��UInput�n�̏����͂����ł͕K�v�Ȃ�
			if (hit->CheckElementHit(ELEMENT_IVY) == true&&( (Input::GetVKey(VK_UP) == true|| Input::GetVKey(VK_DOWN)==true|| Input::GetConVecStickLY(0) != 0.0f)))	//���ɂ������Ă��ā��L�[���́��L�[�������ꂽ�珸�~�t���O��ture
			{
				climb_flag = true;
			}
			else if (hit->CheckElementHit(ELEMENT_IVY) == false && hit->CheckElementHit(ELEMENT_FLOWER) == false && climb_flag == true)/* || Input::GetVKey(VK_UP) == false)*/	//���~�t���O��false�ɂ��鏈��
			{
				climb_flag = false;
			}

			//�����ɂ��Q�[���I�[�o�[�����X�^�[�g
			if (m_py - block->GetScrollY() > 1300)
			{
				//��O�ɏo���烊�X�^�[�g
				Scene::SetScene(new CSceneOver(reset));
			}

			//�S�[���u���b�N�ɐG����
			if (GetBT() == 3)
			{
				CObjCloud* cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
				CObjStageSelect* stage = (CObjStageSelect*)Objs::GetObj(OBJ_STAGE_SELECT);
				Scene::SetScene(new CSceneClear(m_hp, cloud->m_hp, reset));//Hero��HP�Ɖ_����m_hp(�_�̂g�o)��Stage���������Ă���
			}

		//�΂Ƃ̓����蔻��------------------------------------------------------------------------------------------------------------------------------------------
		CObjStone* Stone = (CObjStone*)Objs::GetObj(OBJ_STONE);
		if (m_vy < -1.0f)
		{
			//�W�����v���Ă�ꍇ�͉��L�̉e�����o�Ȃ��悤�ɂ���
		}
		else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr&&Stone->GetPY() <= m_py + 64 - block->GetScrollY() && Stone->GetPY() + 32 >= m_py + 64 - block->GetScrollY())
		{
			//��l�����G�̓��ɏ���Ă�̂ŁAVvec��0�ɂ��ė��������Ȃ�
			//�܂��A�n�ʂɓ������Ă锻��ɂ���
			m_py = Stone->GetPY() + pb->GetScrollY() - 63;
			m_vy = 0.0f;
			m_hit_down = true;
		}
		else if (hit->CheckObjNameHit(OBJ_STONE) != nullptr &&
			((m_posture == 1 && Stone->GetPX_L() < m_px + 64 - block->GetScroll() && Stone->GetPX_R() > m_px + 64 - block->GetScroll()) ||
				m_posture == 0 && Stone->GetPX_R() > m_px - block->GetScroll() && Stone->GetPX_L() < m_px - block->GetScroll()))
		{
			if (Stone->Gethr()==false)
			{
				m_vx /= 2;
				Stone->SetVX(m_vx);
			}
			else if (Stone->Gethr() ==true)
			{
				m_vx = 0;
			}

		}
		//-----------------------------------------------------------------------------------------------------------------------------------------------------------

		CObjTurtle* Turtle = (CObjTurtle*)Objs::GetObj(OBJ_TURTLE);
		if (m_vy < -1.0f)
		{
			//�W�����v���Ă�ꍇ�͉��L�̉e�����o�Ȃ��悤�ɂ���
		}
		else if (hit->CheckObjNameHit(OBJ_TURTLE) != nullptr && Turtle->GetPY() <= m_py + 64 - block->GetScrollY() && Turtle->GetPY() + 32 >= m_py + 64 - block->GetScrollY())
		{
			//��l�����G�̓��ɏ���Ă�̂ŁAVvec��0�ɂ��ė��������Ȃ�
			//�܂��A�n�ʂɓ������Ă锻��ɂ���
			m_px += Turtle->GetVx();
			m_py = Turtle->GetPY() + pb->GetScrollY() - 63;
			m_vy = 0.0f;
			m_hit_down = true;
		}


			//�ʒu�̍X�V
			m_px += m_vx;
			m_py += m_vy;

			//HitBox�̈ʒu�̕ύX
			hit->SetPos(m_px, m_py);
		}


	}
	else if (over_flag == true)//�����@���S���̃A�j���[�V����
	{
		m_ani_time++;

		if (m_ani_time > m_ani_max_time * 5)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}
		if (m_ani_frame == 3 && m_ani_time >= m_ani_max_time * 5)
		{
			Scene::SetScene(new CSceneOver(reset));
		}
	}
	if (Audio_time >= Audio_time_max)
	{
		Audio_time = 0.00f;
	}
	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px+24, m_py);
}

//�h���[
void CObjHero::Draw()
{
	int AniData[4] =
	{
		1,0,2,0,
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�\���ʒu�̐ݒ�
	dst.m_top = -16.0f + m_py;
	dst.m_left = (84.0f * m_posture) + m_px;
	dst.m_right = (84 - 84.0f * m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;
	//�؂���ʒu�̐ݒ�
	if (over_flag == false&&(climb_flag==false||m_hit_down==true))
	{
		src.m_top = 0.0f;
		src.m_left = 32.0f + AniData[m_ani_frame] * 256;
		src.m_right = 224.0f + AniData[m_ani_frame] * 256;
		src.m_bottom = 256.0f;
		//�`��
		Draw::Draw(15, &src, &dst, c, 0.0f);

	}
	else if (over_flag == true)//�����@���S���̃A�j���[�V�����`��
	{
		src.m_top = 0.0f;
		src.m_left = 1.0f + m_ani_frame * 247;
		src.m_right = 244.0f + m_ani_frame * 247;
		src.m_bottom = 245.0f;
		//�`��
		Draw::Draw(17, &src, &dst, c, 0.0f);
	}
	else if (climb_flag == true)
	{
		src.m_top = 0.0f;
		src.m_left = 5.0f + m_ani_frame * 253;
		src.m_right = 257.0f + m_ani_frame * 253;
		src.m_bottom = 431.0f;
		if (m_posture == 1)
		{
			dst.m_left = m_px + 20.0f;
			dst.m_right = dst.m_left + 54.0f;
		}
		else
		{
			dst.m_left = m_px + 54.0f + 20.0f;
			dst.m_right = m_px + 20.0f;
		}
		//�`��
		Draw::Draw(18, &src, &dst, c, 0.0f);

	}
	//�����@��������Ă���Ƃ��̃A�j���[�V�����`��
	//src.m_top	= 1.0f;
	//src.m_left	= 1.0f + AniData[m_ani_frame] * 260;
	//src.m_right = 254.0f + AniData[m_ani_frame] * 255;
	//src.m_bottom= 438.0f;
	//dst.m_top	= 0.0f + m_py;
	//dst.m_left	= (64.0f * m_posture) + m_px;
	//dst.m_right = (64 - 64.0f * m_posture) + m_px;
	//dst.m_bottom= 64.0f + m_py;
	//Draw::Draw(19, &src, &dst, c, 0.0f);


	//��_
	float cc[4] = { 1.0f,0.0f,0.0f,1.0f };
	src.m_top = 0.0f;
	src.m_left = 320.0f;
	src.m_right = 320.0f + 64.0f;
	src.m_bottom = 64.0f;
	dst.m_top = py;
	dst.m_left = px;
	dst.m_right = dst.m_left + 10.0f;
	dst.m_bottom = dst.m_top + 10.0f;
	Draw::Draw(0, &src, &dst, cc, 0.0f);


	wchar_t str1[256];
	wchar_t str2[256];
	wchar_t str3[256];

	CObjStage* block = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	CObjStone* Stone = (CObjStone*)Objs::GetObj(OBJ_STONE);
	CObjCloud* Cloud = (CObjCloud*)Objs::GetObj(OBJ_CLOUD);
	swprintf_s(str1, L"X=%f", m_px - block->GetScroll());
	Font::StrDraw(str1, 20, 20, 20, c);
	swprintf_s(str2, L"X=%f", Stone->GetPX_L());
	Font::StrDraw(str2, 20, 400, 20, c);
	swprintf_s(str3, L"X=%f", Cloud->GetX());
	Font::StrDraw(str3, 20, 300, 20, c);



}

void CObjHero::EnemyHit(int m_enemynum)
{
	CHitBox* hit = Hits::GetHitBox(this);
	CObjStage* pb = (CObjStage*)Objs::GetObj(OBJ_STAGE);
	//��l�����G�Ƃǂ̊p�x�œ������Ă邩�m�F
	HIT_DATA** hit_data = NULL;

	if (hit_flag == true)
	{
		if (m_enemynum == 1)
			hit_data = hit->SearchObjNameHit(OBJ_ENEMY);
		else if (m_enemynum == 2)
			hit_data = hit->SearchObjNameHit(OBJ_FIRE);
		else if (m_enemynum == 3)
			hit_data = hit->SearchObjNameHit(OBJ_SINENEMY);
		else if (m_enemynum == 4)
			hit_data = hit->SearchObjNameHit(OBJ_MAGIC);
		else if (m_enemynum == 5)
			hit_data = hit->SearchObjNameHit(OBJ_RUSH_ENEMY);
		else if (m_enemynum == 6)
			hit_data = hit->SearchObjNameHit(OBJ_SWANP);

		hit_flag = false;

		for (int i = 0; i < hit->GetCount(); i++)
		{

			//�G�̍��E�ɓ���������
			if (hit_data[i] != NULL)
			{
				//�G�̍��E�ɓ���������
				float r = hit_data[i]->r;
				if (r < 45 &&( r >= 0 || r>315)&&m_enemynum!=6)
				{
					m_vx -= 5.0f;//���Ɉړ�������

					if (m_hit_time == 0)
					{
						m_hit_time = 60;
						m_hp -= 0.1f;//�_���[�W
					}
				}
				if (r > 135 && r < 225 && m_enemynum != 6)
				{
					m_vx += 5.0f;//�E�Ɉړ�������
					if (m_hit_time == 0)
					{
						m_hit_time = 60;
						m_hp -= 0.1f;//�_���[�W
					}
				}
				if (r > 45 && r < 135 && m_enemynum != 6)
				{
					if (m_enemynum == 4)
					{
						m_hp -= 0.1;
					}
				}
				if (r >= 225 && r < 315)
				{
					//�G�̈ړ���������l���̈ʒu�ɉ��Z
					if (m_enemynum == 1)
						m_px += ((CObjEnemy*)hit_data[i]->o)->GetVx();
					else if (m_enemynum == 5)
						m_px += ((CObjRushEnemy*)hit_data[i]->o)->GetVx();

					CObjStage* b = (CObjStage*)Objs::GetObj(OBJ_STAGE);
					//����X�N���[�����C��
					if (m_px < 200)
					{
						m_px = 200;
						b->SetScroll(b->GetScroll() + 2.0);
					}

					//�O���X�N���[�����C��
					if (m_px > 400)
					{
						m_px = 400;
						b->SetScroll(b->GetScroll() - 2.0);
					}

					//���ɏ悹�鏈��
					if (m_vy < -1.0f)
					{
						//�W�����v���Ă�ꍇ�͉��L�̉e�����o�Ȃ��悤�ɂ���
					}
					else
					{
						//��l�����G�̓��ɏ���Ă�̂ŁAVvec��0�ɂ��ė��������Ȃ�
						//�܂��A�n�ʂɓ������Ă锻��ɂ���
						m_vy = 0.0f;
						m_hit_down = true;
					}
				}
			}
		}

		if (hit_flag == false)
		{
			hit_flag = true;
		}

		////�ʒu�̍X�V
//		m_px += m_vx;
//		m_py += m_vy;

		////HitBox�̈ʒu�̕ύX
//		hit->SetPos(m_px, m_py);

	}

}

int CObjHero::GetHitDown()
{
	if (m_hit_down == true)
		return m_enemynum;
	else
		return 0;
}