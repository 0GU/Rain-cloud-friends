#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjStageSelect : public CObj
{
public:
	CObjStageSelect() {};
	~CObjStageSelect() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	int stageflag;//��
	bool keyflag;//��
	float m_y1;//����ʗp(��)
	float m_y2;
	float m_scroll;
	bool  move_flag;//����ʃX�C�b�`
	bool scroll_flag;//�͂͂�
	bool Clear_flag[3];//�N���A�t���O���i�{�Ԃ͔z��ŃN���A�̎�ނ𕪂���\��j
	bool Clear_flag2[3];//�N���A�t���O���i�{�Ԃ͔z��ŃN���A�̎�ނ𕪂���\��j
	bool Clear_flag3[3];//�N���A�t���O���i�{�Ԃ͔z��ŃN���A�̎�ނ𕪂���\��j
	bool title_flag;//�^�C�g���ڍs�p�t���O

	float m_ani_time;
	float m_ani_max;
};