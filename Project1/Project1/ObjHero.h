#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjHero : public CObj
{
public:
	CObjHero(int stage) ;
	~CObjHero() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }
	int GetBT() { return m_block_type; }
	float GetHP() { return m_hp; }
	int GetHitDown();

	void SetX(float x) { m_px = x; }
	void SetY(float y) { m_py = y; }
	void SetVY(float vy) { m_vy = vy; }
	void SetVX(float vx) { m_vx = vx; }
	void SetBT(int t) { m_block_type = t; }

	void SetUp(bool b) { m_hit_up = b; }
	void SetDown(bool b) { m_hit_down = b; }
	void SetLeft(bool b) { m_hit_left = b; }
	void SetRight(bool b) { m_hit_right = b; }

	void SetSthit(bool b) { stone_hit = b; }
	void SetSthitW(bool b) { stone_wall_hit = b; }

	void EnemyHit(int enemynume);
	float m_hp;			//�̗́i���j
private:
	float m_px;			//�ʒu
	float m_py;
	float m_vx;			//�ړ��x�N�g��
	float m_vy;
	float m_posture;	//�p��

	int   m_ani_time;   //�A�j���[�V�����t���[������Ԋu
	int   m_ani_frame;  //�`��t���[��

	float m_speed_power;  //�X�s�[�h�p���[
	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//����ł���block�̎�ނ��m�F�p
	int  m_block_type;

	//test
	float px, py; //��_

	int reset;

	bool hit_flag;
	bool stay_flag;


	int   m_hit_time;	//�_���[�W�Ԋu

	bool damageSE_flag;//SE�Ȃ葱����̂�h���t���O

	bool climb_flag;	//���~�t���O

	bool falldamage_flag;	//�����_���[�W�t���O

	bool reset_falldamage_cacancel_flag;//���X�|�[�����X�|�[�����̍ŏ��̗����_���[�W�𖳌���

	bool landing_flag;//�n�ʂɒ��n�������p�t���O

	bool over_flag;//���S�t���O

	float m_py_h;

	int m_enemynum;	//�ڐG���̎�ޔ��ʗp

	bool keyflag;//�L�[�����������ʗp

	
	bool stone_hit;//��ɓ������Ă����Ԃ�Ԃ�
	bool stone_wall_hit;//�������Ă���₪�ǂɂԂ����Ă��邩��Ԃ�
	//�R���g���[���[�p���ϐ�

	float m_con_x;
	float m_con_y;
	int m_con_num;
	bool m_con_flag;

	float Audio_time;//���ʉ�����
	float Audio_time_max;//���ʉ��Ԋu
	bool Audio_f;

	//�_�ŏ���
	float hit_status;
	float hit_time_f;
	bool  hit_f;

	bool hero_stop_f;//��l���̑ҋ@���A�j���[�V�������ʗp
	bool jump_f;//�W�����v���A�j���[�V�������ʗp
	bool stone_push_f;//����������ʃt���O
};