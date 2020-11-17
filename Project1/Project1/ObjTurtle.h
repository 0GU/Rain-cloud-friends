#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�T
class CObjTurtle : public CObj
{
public:
	CObjTurtle(float x, float y);
	~CObjTurtle() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

	float GetVx() { return m_vx; };
	float GetPY() { return m_py; };
	//�T�����̏�ɋ��邩�̔���@�����ŌĂяo��
	void HitCheck(float* x, float* y, bool* swanp);
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

	//�ǉ��������
	float pos_init;	//���������̈ʒu�L���p
	bool m_move;	//�ړ��̌�������p
	bool stay_flag;
	int m_hp;
	//��e�֌W
	bool m_damege_flag;//��e�t���O�@��������true�Œ�~
	float m_transparent;//���������X�ɓ����ɕω�������ϐ�
	bool m_escaoe_flag;//�����I���t���O�@true�ŃI�u�W�F�N�g�j��
	//����ł���block�̎�ނ��m�F�p
	int  m_block_type;
	bool m_swanp;
};