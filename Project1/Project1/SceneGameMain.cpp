
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL/UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "SceneGameMain.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameMain::CSceneGameMain(int num)
{
	stageselect = num;
}

//�f�X�g���N�^
CSceneGameMain::~CSceneGameMain()
{

}

//�Q�[�����C�����������\�b�h
void CSceneGameMain::InitScene()
{
	//�O���f�[�^�̓ǂݍ���(�X�e�[�W���)
	unique_ptr<wchar_t> p;  //�X�e�[�W���|�C���^�[
	int size;				//�X�e�[�W���̑傫��
	if(stageselect==1)
	p = Save::ExternalDataOpen(L"�M�~�b�N�m�F.csv", &size);//�O���f�[�^�ǂݍ���
	else if(stageselect==2)
	p = Save::ExternalDataOpen(L"�X�e�[�W�f�[�^.csv", &size);//�O���f�[�^�ǂݍ���

	int map[10][100];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;
		}
	}


	//SE���̓o�^
	//Audio::LoadAudio(0, L"", SOUND_TYPE::BACK_MUSIC);
	//Audio::LoadAudio(1, L"", SOUND_TYPE::EFFECT);

	//�摜����o�^
	Draw::LoadImageW(L"�f��/��/image.png", 0, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/��/mapcip.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/Animation.png", 2, TEX_SIZE_64);
	//Audio::Start(0);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero(stageselect);
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//stage�I�u�W�F�N�g�쐬
	CObjStage* objb = new CObjStage(map);
	Objs::InsertObj(objb, OBJ_STAGE, 9);


}

//�Q�[�����C�����s���\�b�h
void CSceneGameMain::Scene()
{

}