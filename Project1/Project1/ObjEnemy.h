#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�G
class CObjEnemy : public CObj
{
public:
	CObjEnemy(float x, float y);
	~CObjEnemy() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

	float GetVx() { return m_vx; }
	void ModeChange(float* x, float* y, float* hx, float* hy, float* pos_init, bool* mode, bool* posture,bool searchY);
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

	//��e�֌W
	bool m_damege_flag;//��e�t���O�@��������true�Œ�~
	float m_transparent;//���������X�ɓ����ɕω�������ϐ�
	bool m_escaoe_flag;//�����I���t���O�@true�ŃI�u�W�F�N�g�j��
};