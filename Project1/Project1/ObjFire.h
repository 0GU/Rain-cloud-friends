#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjFire : public CObj
{
public:
	CObjFire(float x, float y);
	~CObjFire() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float m_px, m_py;
private:
	int   m_ani_time;   //�A�j���[�V�����t���[������Ԋu
	int   m_ani_frame;  //�`��t���[��

	float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l
};