#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjPlant : public CObj
{
public:
	CObjPlant(float x, float y,int count);
	~CObjPlant() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float m_px, m_py;
	int grow;
private:
	int   m_ani_time;   //�A�j���[�V�����t���[������Ԋu
	int   m_ani_frame;  //�`��t���[��

	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l
	bool stay_flag;
	int HP;
	bool grow_flag;
};