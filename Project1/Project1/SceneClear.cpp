
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include"GameL/WinInputs.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "GameHead.h"

//�R���X�g���N�^
CSceneClear::CSceneClear(float m_hp,float cl_hp,int stage)
{
	hero_hp = m_hp;//��l���̂g�o�擾�p
	cloud_hp = cl_hp;//�_�̂g�o�擾�p
	stageselect = stage;
}

//�f�X�g���N�^
CSceneClear::~CSceneClear()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneClear::InitScene()
{
	CObjClear* clear = new CObjClear(hero_hp, cloud_hp,stageselect);
	Objs::InsertObj(clear, OBJ_CLEAR, 1);
	//SE���̓o�^
	//Audio::LoadAudio(0, L"�f��/BGM/rain1.wav", SOUND_TYPE::BACK_MUSIC);

	//�摜����o�^
	Draw::LoadImageW(L"�f��/��/White.png", 0, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/StageClear.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/�摜/������(��).png", 2, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/Animation.png", 3, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/�摜/����.png", 5, TEX_SIZE_1024);


}

//�Q�[���^�C�g�����s���\�b�h
void CSceneClear::Scene()
{
	Input::UpdateXControlerConnected();
}