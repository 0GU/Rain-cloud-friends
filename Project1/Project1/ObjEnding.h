#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjEnding : public CObj
{
public:
	CObjEnding() {};
	~CObjEnding() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float x, y;
private:
	int hoge;//��
	bool key_flag;
	bool  move_flag;//�Q��ڂڃt�F�[�h�𓮂����p
	bool m_fade_f;//�t�F�[�h�C���A�E�g���ʗp�t���O
	float m_fade;//�t�F�[�h�l
};