#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjSign : public CObj
{
public:
	CObjSign(float x, float y,int i) ;
	~CObjSign() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;
private:
	float m_px;			//�ʒu
	float m_py;
	int sign_num;//�Ŕ̎�ޔ��ʗp
	bool m_hit_f;//�������Ă��邩�ǂ���
};