#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjClear : public CObj
{
public:
	CObjClear(float m_hp, float cl_hp,int stage) ;
	~CObjClear() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float hero_hp;
	float cloud_hp;
	float x, y;
private:
	int hoge;//��

	bool key_flag;//�L�[�����m�F�p
	float m_y1;//����ʈʒu(��)
	bool  move_flag;
	bool scroll_flag;
	bool Clear_flag[3];//1:Excerent 2:Great 3:Good
	int stageselect;
};