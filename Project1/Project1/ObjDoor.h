#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjDoor : public CObj
{
public:
	CObjDoor(float x,float y,int d_num,int binary);
	~CObjDoor() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	

private:
	float m_x, m_y;
	int num;
	int bin;

	bool flag;
	bool stay_flag;

};