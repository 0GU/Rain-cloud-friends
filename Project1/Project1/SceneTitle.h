#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjTemp : public CObj
{
public:
	CObjTemp() {};
	~CObjTemp() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;
private:
	int hoge;//��
};