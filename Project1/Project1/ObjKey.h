#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjKey : public CObj
{
public:
	CObjKey(float x, float y, int k_num);
	~CObjKey() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	int GetKnum();


private:
	float m_x, m_y;
	int Key_num;

	bool delete_flag;
};