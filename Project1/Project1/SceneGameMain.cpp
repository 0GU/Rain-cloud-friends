
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
	p = Save::ExternalDataOpen(L"Stage1x.csv", &size);//�O���f�[�^�ǂݍ���
	else if(stageselect==2)
	p = Save::ExternalDataOpen(L"Stage2.csv", &size);//�O���f�[�^�ǂݍ���
	else if (stageselect == 3)
		p = Save::ExternalDataOpen(L"�M�~�b�N�m�F.csv", &size);//�O���f�[�^�ǂݍ���
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
	Audio::LoadAudio(6, L"�f��/SE/����.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(7, L"�f��/SE/����.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(8, L"�f��/SE/���ˉ�.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(9, L"�f��/SE/�x��.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(10, L"�f��/SE/�m��.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(11, L"�f��/SE/�u�Ԉړ�.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(12, L"�f��/SE/���.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(20, L"�f��/SE/�|�[�Y.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(21, L"�f��/SE/button01.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(22, L"�f��/SE/button02.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(23, L"�f��/BGM/�[��.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(24, L"�f��/BGM/��.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(25, L"�f��/SE/�ړ���.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(26, L"�f��/SE/�_�ړ���.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(27, L"�f��/SE/����.wav", SOUND_TYPE::EFFECT);
	//�摜����o�^
	Draw::LoadImageW(L"�f��/�摜/testtt.png", 0, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/��/mapcip.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/Animation.png", 2, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/�摜/�|�[�Y�摜.png", 3, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/�I��.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/�w�.png", 5, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/HP(����).png", 6, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/�摜/��.png", 7, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/�摜/�_�̂�.png", 8, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/��/�X���C��.png", 9, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/�摜/�A���~�j.png", 10, TEX_SIZE_128);
	Draw::LoadImageW(L"�f��/�摜/�ǔ��G0.png", 11, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/�摜/�d��2.png", 12, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/��.png", 13, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�C�m�V�V2.png", 14, TEX_SIZE_256);
	Draw::LoadImageW(L"�f��/��/test���̎q.png", 15, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�W�����v.png", 16, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/���S.png", 17, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�A������.png", 18, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�A���������.png", 20, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/����.png", 19, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�w�i.png", 22, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�[���w�i.png", 23, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/��w�i.png", 24, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/HP�g.png", 25, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/HP.png", 26, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/ito.png", 27, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�y�u���b�N.png", 30, TEX_SIZE_1024);//�����@�ʂ���ݏ��p
	Draw::LoadImageW(L"�f��/�摜/�ҋ@�C��.png", 31, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�W�����v.png", 32, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�����C����.png", 33, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�Ŕ�.png", 34, TEX_SIZE_256);
	Draw::LoadImageW(L"�f��/�摜/��.png", 35, TEX_SIZE_512);
	Draw::LoadImageW(L"�f��/�摜/�T2.png", 36, TEX_SIZE_512);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X.png", 45, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X2.png", 46, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X3.png", 47, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X4.png", 48, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X5.png", 49, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X6.png", 50, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X7.png", 51, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X8.png", 52, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/�e�L�X�g�{�b�N�X9.png", 53, TEX_SIZE_1024);


	if(stageselect==1)
	{
		Audio::Start(0);
		Audio::Start(1);
	}
	if (stageselect == 2)
	{
		Audio::Start(23);
		Audio::Start(1);
	}
	if (stageselect == 3)
	{
		Audio::Start(24);
		Audio::Start(1);
	}
	//Audio::Start(0);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero(stageselect);
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//stage�I�u�W�F�N�g�쐬
	CObjStage* objb = new CObjStage(map,stageselect);
	Objs::InsertObj(objb, OBJ_STAGE, 9);

	//Pose�I�u�W�F�N�g�쐬
	CObjPose* objp = new CObjPose(0,0,stageselect);
	Objs::InsertObj(objp, OBJ_POSE, 11);

	//��l���I�u�W�F�N�g�쐬
	CObjCloud* objc = new CObjCloud(stageselect);
	Objs::InsertObj(objc, OBJ_CLOUD, 10);

	//�̗̓o�[�I�u�W�F�N�g�쐬
	CObjHp* objh = new CObjHp();
	Objs::InsertObj(objh, OBJ_HP, 11);

	CObjDoormanager* objd = new CObjDoormanager();
	Objs::InsertObj(objd, OBJ_DOORMANAGER, 10);

	//�����@�T
/*	CObjTurtle* objt = new CObjTurtle(400,600);
	Objs::InsertObj(objt, OBJ_TURTLE, 12);

	//�����@�T
	CObjTurtle* objt2 = new CObjTurtle(480, 600);
	Objs::InsertObj(objt2, OBJ_TURTLE, 12);
	*/
}

//�Q�[�����C�����s���\�b�h
void CSceneGameMain::Scene()
{
	Input::UpdateXControlerConnected();
}