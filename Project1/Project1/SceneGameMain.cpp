
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL/UserData.h"
#include"GameL/WinInputs.h"

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
	else if (stageselect == 3)
		p = Save::ExternalDataOpen(L"�Z�[�u�m�F�p3.csv", &size);//�O���f�[�^�ǂݍ���
	int map[20][100];
	int count = 1;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			
			if (w >= 10)
			{
				count += 3;
			}
			else
			{
				count += 2;
			}
		}
	}


	//SE���̓o�^
	Audio::LoadAudio(0, L"�f��/BGM/Stage1��.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"�f��/BGM/����.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(2, L"�f��/SE/�W�����v.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(3, L"�f��/SE/���n.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(4, L"�f��/SE/�_���[�W��.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(5, L"�f��/SE/�J.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(6, L"�f��/SE/��e.wav", SOUND_TYPE::EFFECT);

	//�摜����o�^
	Draw::LoadImageW(L"�f��/��/image.png", 0, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/��/mapcip.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/Animation.png", 2, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/Pose.png", 3, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/�I��.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/�w�.png", 5, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/HP(����).png", 6, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/��/ito.png", 7, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/�摜/�_�̂�.png", 8, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/��/�X���C��.png", 9, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/�摜/�A���~�j.png", 10, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/�摜/�ǔ��G0.png", 11, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/�摜/�d��.png", 12, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/��.png", 13, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/Game�w�i��.png", 22, TEX_SIZE_1024);
	if(stageselect==1)
	{
		Audio::Start(0);
		Audio::Start(1);
	}
	

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero(stageselect);
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//stage�I�u�W�F�N�g�쐬
	CObjStage* objb = new CObjStage(map);
	Objs::InsertObj(objb, OBJ_STAGE, 9);

	//Pose�I�u�W�F�N�g�쐬
	CObjPose* objp = new CObjPose(0,0);
	Objs::InsertObj(objp, OBJ_POSE, 11);

	//��l���I�u�W�F�N�g�쐬
	CObjCloud* objc = new CObjCloud(stageselect);
	Objs::InsertObj(objc, OBJ_CLOUD, 10);

	//�̗̓o�[�I�u�W�F�N�g�쐬
	CObjHp* objh = new CObjHp();
	Objs::InsertObj(objh, OBJ_HP, 11);

	//��l���I�u�W�F�N�g�쐬
	CObjSinEnemy* objs = new CObjSinEnemy(400,400);
	Objs::InsertObj(objs, OBJ_SINENEMY, 10);
}

//�Q�[�����C�����s���\�b�h
void CSceneGameMain::Scene()
{
	Input::UpdateXControlerConnected();
}