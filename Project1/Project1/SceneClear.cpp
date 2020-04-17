
//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p����w�b�_�[
#include "GameHead.h"

//�R���X�g���N�^
CSceneClear::CSceneClear()
{

}

//�f�X�g���N�^
CSceneClear::~CSceneClear()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneClear::InitScene()
{
	CObjClear* p = new CObjClear();
	Objs::InsertObj(p, OBJ_CLEAR, 1);
	//SE���̓o�^
	Audio::LoadAudio(0, L"�f��/BGM/rain1.wav", SOUND_TYPE::BACK_MUSIC);

	//�摜����o�^
	Draw::LoadImageW(L"�f��/��/White.png", 0, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/��/StageClear.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/Shizuku.png", 2, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/Animation.png", 3, TEX_SIZE_64);
}

//�Q�[���^�C�g�����s���\�b�h
void CSceneClear::Scene()
{

}