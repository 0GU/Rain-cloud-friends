#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjPose : public CObj
{
public:
	CObjPose(float x, float y);
	~CObjPose() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	
private:

	float m_px;
	float m_py;
	bool delete_flag;
	bool stay_flag;
};