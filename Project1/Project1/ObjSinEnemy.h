#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�FSin�G�@
class CObjSinEnemy :public CObj
{
public:
	CObjSinEnemy(float x, float y);//�R���X�g���N�^
	~CObjSinEnemy() {};
	void Init();//�C�j�V�����C�Y
	void Action();//�A�N�V����
	void Draw();//�h���[
private:
	float m_x;//�G�@�̂������̈ʒu
	float m_y;//�G�@�̂������̈ʒu
	float m_vx;//�G�@�ړ��x�N�g��X
	float m_vy;//�G�@�ړ��x�N�g��Y
	float m_r;//�T�C���J�[�u�p�̊p�x

	int   m_ani_time;   //�A�j���[�V�����t���[������Ԋu
	int   m_ani_frame;  //�`��t���[��

	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l

	float m_posture;	//�p��
	float pos_init;	//���������̈ʒu�L���p

	int m_charge_time;//�`���[�W����
	int m_atk_time;//�U���Ԋu

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool stay_flag;
	bool m_move;//�ړ��̌�������p true=�E false=��
	bool m_atk_flag;//�U�����[�h�p
	bool m_charge_flag;//�`���[�W�p

	bool sleep_flag;//�f�o�b�O�p��~�t���O

};