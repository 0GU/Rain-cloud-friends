#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjRain : public CObj
{
public:
	CObjRain(float x,float y);
	~CObjRain() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[


private:
	int reset;

	float m_px;
	float m_py;
	float m_vx;
	float m_vy;
};