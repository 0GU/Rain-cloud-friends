#pragma once
//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


//�I�u�W�F�N�g�F�X�e�[�W�Z���N�g
class CObjDoormanager : public CObj
{
public:
	CObjDoormanager() {};
	~CObjDoormanager() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetPos(int D_num, int binary, float x, float y);
	void MoveDoor(int D_num, int binary);
	
private:
	bool Key[10];
	 float pos[10][2][2];//[�h�A�ԍ�][�΂ɂȂ��Ă���h�A�̎���][�h�A�̍��W]
	
};