#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjMagic : public CObj
{
public:
	CObjMagic(float x, float y,bool posture);
	~CObjMagic() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;

private:
	float m_px;//�������̈ʒu
	float m_py;//�������̈ʒu
	float m_vx;//�x�N�g��X
	float m_vy;//�x�N�g��Y
	float m_r;//�p�x

	int   m_ani_time;   //�A�j���[�V�����t���[������Ԋu
	int   m_ani_frame;  //�`��t���[��
	bool m_del;
	bool m_posture;
	bool m_check;//�ʒu�`�F�b�N�p

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool stay_flag;


	bool light_flag;//���邳�ύX
	float m_light;
};