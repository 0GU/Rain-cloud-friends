#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjClear : public CObj
{
public:
	CObjClear() {};
	~CObjClear() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;
private:
	int hoge;//��
	bool key_flag;//�L�[�����m�F�p

	float m_y1;//����ʈʒu(��)
	bool  move_flag;
	bool scroll_flag;

	bool Clear_flag[3];//1:Excerent
};