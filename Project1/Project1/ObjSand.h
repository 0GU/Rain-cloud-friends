#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjSand : public CObj
{
public:
	CObjSand(float x, float y);
	~CObjSand() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float m_px, m_py;
	void RainHit(int* hp, bool* damege);
	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up = false;
	bool m_hit_down = false;
	bool m_hit_left = false;
	bool m_hit_right = false;
private:
	int hoge;//��
	bool m_hit_rain;//�J�ɓ����������������Ă��Ȃ���
	float m_fade_num;//���X�Ƀt�F�[�h�A�E�g����l������
};

