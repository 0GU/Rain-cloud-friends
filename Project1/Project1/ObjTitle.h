#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle : public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;
	float m_y1;//����ʗp(��)
private:
	int hoge;//��
	float m_scroll;
	bool  move_flag;
	bool scroll_flag;//�͂͂�
	bool key_flag;//�L�[�����m�F�p
	bool select_flag;//�㉺����p
	bool description_flag;//������ʕ\���p

};