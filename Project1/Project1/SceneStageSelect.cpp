
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
CSceneStageSelect::CSceneStageSelect()
{

}

//�f�X�g���N�^
CSceneStageSelect::~CSceneStageSelect()
{

}

//�Q�[���^�C�g�����������\�b�h
void CSceneStageSelect::InitScene()
{

	CObjStageSelect* p = new CObjStageSelect();
	Objs::InsertObj(p, OBJ_STAGE_SELECT, 1);

	//SE���̓o�^
	Audio::LoadAudio(0, L"�f��/BGM/Select.wav", SOUND_TYPE::BACK_MUSIC);
	Audio::LoadAudio(1, L"�f��/SE/button01.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(2, L"�f��/SE/button02.wav", SOUND_TYPE::EFFECT);


	//�摜����o�^
	Draw::LoadImageW(L"�f��/��/Stage�w�i��.png", 0, TEX_SIZE_2048);
	Draw::LoadImageW(L"�f��/��/TestStage.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"�f��/��/Animation.png", 2, TEX_SIZE_64);
	Draw::LoadImageW(L"�f��/�摜/������(��).png", 3, TEX_SIZE_1024);
	Audio::Start(0);
}

//�Q�[���^�C�g�����s���\�b�h
void CSceneStageSelect::Scene()
{

}