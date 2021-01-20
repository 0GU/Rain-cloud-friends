#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjStone : public CObj
{
public:
	CObjStone(float x, float y);
	~CObjStone() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	void SetVX(float vx) { m_vx = vx; };
	float GetPX_L() { return m_px; };
	float GetPX_R() { return m_px+128; };
	float GetPY() { return m_py; };
	bool Gethr() { return m_hit_right; };
	bool Getflag() { return hit_flag; };
	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//����ł���block�̎�ނ��m�F�p
	int  m_block_type;

	float m_px, m_py;
	float m_vx, m_vy;
private:
	bool stay_flag;
	bool hit_flag;
};