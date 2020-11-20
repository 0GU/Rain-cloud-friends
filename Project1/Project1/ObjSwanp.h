#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjSwanp : public CObj
{
public:
	CObjSwanp(float x, float y);
	~CObjSwanp() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetFlag(bool b) { m_swanp_flag = b; m_swanp_time = 300; }//�����@���u���b�N
	bool GetFlag() { return m_swanp_flag; }

private:
	float m_px;			//�ʒu
	float m_py;
	int m_hp;
	bool m_swanp_flag;
	int m_swanp_time;
	bool stay_flag;
};