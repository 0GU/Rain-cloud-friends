#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjPose : public CObj
{
public:
	CObjPose(float x, float y,int stage);
	~CObjPose() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	bool GetFlag() { return stay_flag; }
	int stage_num;
private:

	float m_px;
	float m_py;
	bool delete_flag;
	bool stay_flag;
	bool keyflag;//
	int select_num;//�|�[�Y�̑I���J�E���g

	float m_ani_time;//�A�j���[�V��������
	float m_ani_max;//�A�j���[�V�����ő�l

};