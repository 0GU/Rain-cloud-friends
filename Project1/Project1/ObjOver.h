#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�Q�[���I�[�o�[
class CObjOver : public CObj
{
public:
	CObjOver(int stagenum);
	~CObjOver() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;
private:
	int restart;//���X�^�[�g�p
	int selectnum;//�I���ꏊ
	int selectnum_c;//�I���ꏊ�i�m�F��ʁj

	bool  move_flag;//�Q��ڂڃt�F�[�h�𓮂����p
	bool m_fade_f;//�t�F�[�h�C���A�E�g���ʗp�t���O
	bool key_flag;//�L�[�����m�F�p
	bool  move_flag2;//�Q��ڂڃt�F�[�h�𓮂����p
	bool scroll_flag;//�X�N���[���p�@true:��~�@false:���s��
	bool check_flag;//�m�F�p
	float m_fade;//����ʗp(��)
	int m_con_num;//��
	float m_ani_time;//�A�j���[�V��������
	float m_ani_max;//�A�j���[�V�����ő�l
};
