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

	float m_fade;//����ʗp(��)
private:
	bool  move_flag;//�Q��ڂڃt�F�[�h�𓮂����p
	bool m_fade_f;//�t�F�[�h�C���A�E�g���ʗp�t���O
	bool key_flag;//�L�[�����m�F�p
	bool select_flag;//�㉺����p
	bool description_flag;//������ʕ\���p

	//���L�[�`��p---------------------------
	float m_ani_time;//�A�j���[�V��������
	float m_ani_max;//�A�j���[�V�����ő�l
	int m_con_num;//�R���g���[���[���ʗp�ϐ�
};