#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjHp : public CObj
{
public:
	CObjHp() {};
	~CObjHp() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;
private:
	float he_hp;	//�̗͗ʁF��l��
	float cl_hp;	//�̗͗ʁF�_
};