#pragma once
#pragma once
#pragma once
#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�N���A
class CSceneClear :public CScene
{
public:
	CSceneClear(float m_hp, float cl_hp,int stage);//��l���̂g�o�Ɖ_�̂g�o
	~CSceneClear() ;
	void InitScene();//�Q�[���^�C�g���̏��������\�b�h
	void Scene();	 //�Q�[���^�C�g���̎��s�����\�b�h
private:
	float hero_hp;
	float cloud_hp;
	int stageselect;
};