#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjCloud : public CObj
{
public:
	CObjCloud(int stage);
	~CObjCloud() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

	float GetHP() { return m_hp; }
	float m_hp;			//�̗́i���j
	
private:
	int reset;

	float m_px;
	float m_py;
	float m_vx;
	float m_vy;



	bool stay_flag;
	bool rain_flag;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;


	//�R���g���[���[�p
	int m_con_num;

	float m_con_x;
	float m_con_y;
};