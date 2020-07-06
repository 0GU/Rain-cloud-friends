#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjCloud : public CObj
{
public:
	CObjCloud(int stage);
	~CObjCloud() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[

	float GetHP() { return m_hp; }
	float m_hp;			//�̗́i���j
	
private:
	int reset;

	float m_px;
	float m_py;
	float m_vx;
	float m_vy;



	bool stay_flag;
	bool rain_flag;
};