#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�Q�[���I�[�o�[
class CObjOver : public CObj
{
public:
	CObjOver(int stagenum) ;
	~CObjOver() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;
private:
	int restart;//���X�^�[�g�p
	float m_y1;//����ʈʒu(��)
	int selectnum;//�I���ꏊ
	int selectnum_c;//�I���ꏊ�i�m�F��ʁj

	bool keyflag;//�L�[��ԁ@true:�����Ă���
	bool  move_flag;//��ʈڍs��
	bool scroll_flag;//�X�N���[���p�@true:��~�@false:���s��
	bool check_flag;//�m�F�p

	int m_con_num;//��
};